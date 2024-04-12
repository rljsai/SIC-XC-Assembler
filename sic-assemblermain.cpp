#include <bits/stdc++.h>
using namespace std;
#include "sic-assembler-passes.cpp"
void print_tables(ofstream& tables){
     for (auto cs : CSECT)
    { 
        tables << "---------------------------------------------------------------\n";
        tables << cs.second.name << " START:" << cs.second.start << " LENGTH:" << cs.second.length << " LOCCTR:" << cs.second.LOCCTR << "\n";
        tables << "SYMBOL TABLE\n";
        for (auto st : cs.second.SYM_TAB)
        {
            if (st.second.exists)
                tables << "NAME: " << st.first << " Address: " << st.second.address << " IsRelative: " << st.second.isrelative << "\n";
        }
        tables << "\nLITERAL TABLE\n";
        for (auto lt : cs.second.LIT_TAB)
        {
            tables << "NAME:" << lt.first << "  VALUE: " << lt.second.value << "    ADDRESS: " << lt.second.address << "    WRITE: " << lt.second.written << "\n";
        }
    }
}
void organize(ifstream &in, ofstream &fout)
{
    set<char> oprtr;
    oprtr.insert('+');
    oprtr.insert('-');
    oprtr.insert('*');
    oprtr.insert('@');
    oprtr.insert('/');
    oprtr.insert('#');
    oprtr.insert(',');
    oprtr.insert('\'');
    oprtr.insert('=');

    string s1, s2, temp;
    while (getline(in, s1))
    {
        stringstream sfg(s1);
        sfg >> temp;
        if (temp[0] != '.')
        {
            int len = s1.length();
            for (int i = 0; i < len - 1; i++)
            {
                if (s1[i + 1] == '+' || s1[i + 1] == '-' || s1[i + 1] == '*' || s1[i + 1] == '/')
                {
                    len++;
                    s1.insert(i + 1, 1, ' ');
                    i++;
                }
            }
            bool fk = false;
            len = s1.length();
            for (int i = 0; i < len - 1; i++)
            {
                if (s1[i] == ',' && s1[i + 1] != ' ')
                {
                    len++;
                    s1.insert(i + 1, 1, ' ');
                    i++;
                }
            }
            s2 = s1;
            for (int i = 0; i < s1.length(); i++)
            {
                fk = (s1[i] == '\'') ? !fk : fk;
                if (!fk)
                {
                    s2[i] = (char)toupper(s1[i]);
                }
            }
            stringstream ss(s2);
            while (ss >> s1)
            {
                if (oprtr.find(s1[0]) == oprtr.end())
                {
                    if (oprtr.find(s1[s1.length() - 1]) == oprtr.end())
                    {
                        fout << s1 << " ";
                    }
                    else
                    {
                        fout << s1.substr(0, s1.length() - 1) << " " << s1[s1.length() - 1];
                    }
                }
                else
                {
                    if (s1.length() == 1)
                        fout << s1;
                    else
                        fout << s1 << " ";
                }
            }
            fout << "\n";
        }
    }
}

int main()
{
    ifstream in1("input.txt");
    ofstream prefile("organising.txt");
    cout << "Organizing...." << endl;
    organize(in1, prefile);
    in1.close();
    prefile.close();
    ASSDIR_init();
    REGTAB_intit();
    OPTAB_init();
    ifstream in2("organising.txt");
    ofstream errorsfile("errors.txt");
    ofstream listfile("listingfile.txt");
    ofstream intermediatefile("intermediatefile.txt");
    ofstream objectcode("objectcode.txt");
    ofstream tables("tables.txt");
    errorsfile << "ERRORS IN PASS1:" << endl;
    cout << "processing PASS1..." << endl;
    bool k = false;
    pass1(in2, intermediatefile, errorsfile, k);
    cout << k << " End of pass1 \n";
    in2.close();
    ifstream in3("organising.txt");
    cout << "processing PASS2.... " << endl;
    errorsfile << "ERRORS IN PASS2:" << endl;
    pass2(in3, errorsfile, k, objectcode, listfile);
    print_tables(tables);
    tables.close();
    in3.close();
    listfile.close();
    errorsfile.close();
    objectcode.close();
    intermediatefile.close();


}
