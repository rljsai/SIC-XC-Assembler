#include <bits/stdc++.h>
using namespace std;

struct OPTAB_struct
{
    bool exists;
    string opcode;
    int format;
    OPTAB_struct()
    {
        exists = false;
        format = -1;
        opcode = "";
    }
};

struct REGTAB_struct
{

    bool exists;
    int number;
    REGTAB_struct()
    {
        exists = false;
        number = -1;
    }
};

struct SYMTAB_struct
{
    bool exists;
    int address;
    int isrelative;
    SYMTAB_struct()
    {
        exists = false;
        address = -1;
        isrelative = 0;
    }
};
struct LITAB_struct
{
    bool exists;
    int address;
    bool written;
    string value;
    LITAB_struct()
    {
        exists = false;
        address = 0;
        written = false;
        value = "";
    }
};

struct EXTREF_struct
{
    bool exists;
    string value;
    EXTREF_struct()
    {
        exists = false;
        value = "";
    }
};

struct EXTDEF_struct
{
    bool exists;
    string value;
    string address;
    EXTDEF_struct()
    {
        exists = false;
        value = "";
        address = "0";
    }
};

struct CSECT_struct
{
    string name;
    int LOCCTR;
    int length;
    int start;
    string base;
    stack<int> org_stack;
    map<string, EXTDEF_struct> EXTDEF_TAB;
    map<string, EXTREF_struct> EXTREF_TAB;
    map<string, SYMTAB_struct> SYM_TAB;
    map<string, LITAB_struct> LIT_TAB;
    CSECT_struct()
    {
        start = 0;
        LOCCTR = 0;
        length = 0;
        name = "DEFAULT";
    }
};

map<string, OPTAB_struct> OPTABLE;
map<string, bool> ASSDIR;
map<string, REGTAB_struct> REG_TAB;
map<string, CSECT_struct> CSECT;

void REGTAB_intit()
{
    REG_TAB["A"].number = '0';
    REG_TAB["A"].exists = true;

    REG_TAB["X"].number = '1';
    REG_TAB["X"].exists = true;

    REG_TAB["L"].number = '2';
    REG_TAB["L"].exists = true;

    REG_TAB["B"].number = '3';
    REG_TAB["B"].exists = true;

    REG_TAB["S"].number = '4';
    REG_TAB["S"].exists = true;

    REG_TAB["T"].number = '5';
    REG_TAB["T"].exists = true;

    REG_TAB["F"].number = '6';
    REG_TAB["F"].exists = true;

    REG_TAB["PC"].number = '8';
    REG_TAB["PC"].exists = true;

    REG_TAB["SW"].number = '9';
    REG_TAB["SW"].exists = true;
}

void ASSDIR_init()
{
    ASSDIR["BASE"] = true;
    ASSDIR["EQU"] = true;
    ASSDIR["END"] = true;
    ASSDIR["LTORG"] = true;
    ASSDIR["RESB"] = true;
    ASSDIR["RESW"] = true;
    ASSDIR["WORD"] = true;
    ASSDIR["BYTE"] = true;
    ASSDIR["ORG"] = true;
    ASSDIR["NOBASE"] = true;
    ASSDIR["EXTREF"] = true;
    ASSDIR["EXTDEF"] = true;
}

void OPTAB_init()
{
    OPTABLE["FIX"].exists = true;
    OPTABLE["FIX"].opcode = "C4";
    OPTABLE["FIX"].format = 1;

    OPTABLE["FLOAT"].exists = true;
    OPTABLE["FLOAT"].opcode = "C0";
    OPTABLE["FLOAT"].format = 1;

    OPTABLE["HIO"].exists = true;
    OPTABLE["HIO"].opcode = "F4";
    OPTABLE["HIO"].format = 1;

    OPTABLE["NORM"].exists = true;
    OPTABLE["NORM"].opcode = "C8";
    OPTABLE["NORM"].format = 1;

    OPTABLE["SIO"].exists = true;
    OPTABLE["SIO"].opcode = "F0";
    OPTABLE["SIO"].format = 1;

    OPTABLE["TIO"].exists = true;
    OPTABLE["TIO"].opcode = "F8";
    OPTABLE["TIO"].format = 1;

    OPTABLE["ADDR"].exists = true;
    OPTABLE["ADDR"].opcode = "90";
    OPTABLE["ADDR"].format = 2;

    OPTABLE["CLEAR"].exists = true;
    OPTABLE["CLEAR"].opcode = "B4";
    OPTABLE["CLEAR"].format = 2;

    OPTABLE["COMPR"].exists = true;
    OPTABLE["COMPR"].opcode = "A0";
    OPTABLE["COMPR"].format = 2;

    OPTABLE["DIVR"].exists = true;
    OPTABLE["DIVR"].opcode = "9C";
    OPTABLE["DIVR"].format = 2;

    OPTABLE["MULR"].exists = true;
    OPTABLE["MULR"].opcode = "98";
    OPTABLE["MULR"].format = 2;

    OPTABLE["RMO"].exists = true;
    OPTABLE["RMO"].opcode = "AC";
    OPTABLE["RMO"].format = 2;

    OPTABLE["SHIFTL"].exists = true;
    OPTABLE["SHIFTL"].opcode = "A4";
    OPTABLE["SHIFTL"].format = 2;

    OPTABLE["SHIFTR"].exists = true;
    OPTABLE["SHIFTR"].opcode = "A8";
    OPTABLE["SHIFTR"].format = 2;

    OPTABLE["SUBR"].exists = true;
    OPTABLE["SUBR"].opcode = "94";
    OPTABLE["SUBR"].format = 2;

    OPTABLE["SVC"].exists = true;
    OPTABLE["SVC"].opcode = "B0";
    OPTABLE["SVC"].format = 2;

    OPTABLE["TIXR"].exists = true;
    OPTABLE["TIXR"].opcode = "B8";
    OPTABLE["TIXR"].format = 2;

    OPTABLE["ADD"].exists = true;
    OPTABLE["ADD"].opcode = "18";
    OPTABLE["ADD"].format = 3;

    OPTABLE["ADD"].exists = true;
    OPTABLE["ADD"].opcode = "18";
    OPTABLE["ADD"].format = 3;

    OPTABLE["AND"].exists = true;
    OPTABLE["AND"].opcode = "40";
    OPTABLE["AND"].format = 3;

    OPTABLE["COMP"].exists = true;
    OPTABLE["COMP"].opcode = "28";
    OPTABLE["COMP"].format = 3;

    OPTABLE["COMPF"].exists = true;
    OPTABLE["COMPF"].opcode = "88";
    OPTABLE["COMPF"].format = 3;

    OPTABLE["DIV"].exists = true;
    OPTABLE["DIV"].opcode = "24";
    OPTABLE["DIV"].format = 3;

    OPTABLE["DIVF"].exists = true;
    OPTABLE["DIVF"].opcode = "64";
    OPTABLE["DIVF"].format = 3;

    OPTABLE["J"].exists = true;
    OPTABLE["J"].opcode = "3C";
    OPTABLE["J"].format = 3;

    OPTABLE["JEQ"].exists = true;
    OPTABLE["JEQ"].opcode = "30";
    OPTABLE["JEQ"].format = 3;

    OPTABLE["JGT"].exists = true;
    OPTABLE["JGT"].opcode = "34";
    OPTABLE["JGT"].format = 3;

    OPTABLE["JLT"].exists = true;
    OPTABLE["JLT"].opcode = "38";
    OPTABLE["JLT"].format = 3;

    OPTABLE["JSUB"].exists = true;
    OPTABLE["JSUB"].opcode = "48";
    OPTABLE["JSUB"].format = 3;

    OPTABLE["LDA"].exists = true;
    OPTABLE["LDA"].opcode = "00";
    OPTABLE["LDA"].format = 3;

    OPTABLE["LDB"].exists = true;
    OPTABLE["LDB"].opcode = "68";
    OPTABLE["LDB"].format = 3;

    OPTABLE["LDCH"].exists = true;
    OPTABLE["LDCH"].opcode = "50";
    OPTABLE["LDCH"].format = 3;

    OPTABLE["LDF"].exists = true;
    OPTABLE["LDF"].opcode = "70";
    OPTABLE["LDF"].format = 3;

    OPTABLE["LDL"].exists = true;
    OPTABLE["LDL"].opcode = "08";
    OPTABLE["LDL"].format = 3;

    OPTABLE["LDS"].exists = true;
    OPTABLE["LDS"].opcode = "6C";
    OPTABLE["LDS"].format = 3;

    OPTABLE["LDT"].exists = true;
    OPTABLE["LDT"].opcode = "74";
    OPTABLE["LDT"].format = 3;

    OPTABLE["LDX"].exists = true;
    OPTABLE["LDX"].opcode = "04";
    OPTABLE["LDX"].format = 3;

    OPTABLE["LPS"].exists = true;
    OPTABLE["LPS"].opcode = "D0";
    OPTABLE["LPS"].format = 3;

    OPTABLE["MUL"].exists = true;
    OPTABLE["MUL"].opcode = "20";
    OPTABLE["MUL"].format = 3;

    OPTABLE["MULF"].exists = true;
    OPTABLE["MULF"].opcode = "60";
    OPTABLE["MULF"].format = 3;

    OPTABLE["OR"].exists = true;
    OPTABLE["OR"].opcode = "44";
    OPTABLE["OR"].format = 3;

    OPTABLE["RD"].exists = true;
    OPTABLE["RD"].opcode = "D8";
    OPTABLE["RD"].format = 3;

    OPTABLE["RSUB"].exists = true;
    OPTABLE["RSUB"].opcode = "4C";
    OPTABLE["RSUB"].format = 3;

    OPTABLE["SSK"].exists = true;
    OPTABLE["SSK"].opcode = "EC";
    OPTABLE["SSK"].format = 3;

    OPTABLE["STA"].exists = true;
    OPTABLE["STA"].opcode = "0C";
    OPTABLE["STA"].format = 3;

    OPTABLE["STB"].exists = true;
    OPTABLE["STB"].opcode = "78";
    OPTABLE["STB"].format = 3;

    OPTABLE["STCH"].exists = true;
    OPTABLE["STCH"].opcode = "54";
    OPTABLE["STCH"].format = 3;

    OPTABLE["STF"].exists = true;
    OPTABLE["STF"].opcode = "80";
    OPTABLE["STF"].format = 3;

    OPTABLE["STI"].exists = true;
    OPTABLE["STI"].opcode = "D4";
    OPTABLE["STI"].format = 3;

    OPTABLE["STL"].exists = true;
    OPTABLE["STL"].opcode = "14";
    OPTABLE["STL"].format = 3;

    OPTABLE["STS"].exists = true;
    OPTABLE["STS"].opcode = "7C";
    OPTABLE["STS"].format = 3;

    OPTABLE["STSW"].exists = true;
    OPTABLE["STSW"].opcode = "E8";
    OPTABLE["STSW"].format = 3;

    OPTABLE["STT"].exists = true;
    OPTABLE["STT"].opcode = "84";
    OPTABLE["STT"].format = 3;

    OPTABLE["STX"].exists = true;
    OPTABLE["STX"].opcode = "10";
    OPTABLE["STX"].format = 3;

    OPTABLE["STB"].exists = true;
    OPTABLE["STB"].opcode = "1C";
    OPTABLE["STB"].format = 3;

    OPTABLE["SUBF"].exists = true;
    OPTABLE["SUBF"].opcode = "5C";
    OPTABLE["SUBF"].format = 3;

    OPTABLE["TD"].exists = true;
    OPTABLE["TD"].opcode = "E0";
    OPTABLE["TD"].format = 3;

    OPTABLE["TIX"].exists = true;
    OPTABLE["TIX"].opcode = "2C";
    OPTABLE["TIX"].format = 3;

    OPTABLE["WD"].exists = true;
    OPTABLE["WD"].opcode = "DC";
    OPTABLE["WD"].format = 3;
}

int stringToDecimal(std::string str)
{
    int result = 0;

    for (char c : str)
    {
        if (isdigit(c))
        {
            result = result * 10 + (c - '0');
        }
        else
        {
            break;
        }
    }

    return result;
}
void changeString(string &s, int size)
{
    if (s.length() > size)
    {
        s = s.substr(s.length() - size, size);
    }
    else
    {
        string temp = "";
        for (int i = 1; i <= (size - s.length()); i++)
        {
            temp += "0";
        }
        temp += s;
        s = temp;
    }
}
string convertDecToHex(int decimal)
{
    stringstream stream2;
    stream2 << hex << decimal;
    string result(stream2.str());
    char resultUpper[10];
    strcpy(resultUpper, result.c_str());
    for (int i = 0; i < strlen(resultUpper); i++)
    {
        resultUpper[i] = toupper(resultUpper[i]);
    }
    return resultUpper;
}
string convertQuote(string s, int line, bool &error, ofstream &ferror)
{
    string str = "";
    if (s[0] == 'C')
    {
        int index = 2;
        string val = "", val637 = "";
        int ch637;
        while (index < s.length() && s[index] != '\'' && s[index] != ' ')
        {
            val637 += s[index];
            ch637 = (int)s[index];
            string te640 = convertDecToHex(ch637);
            changeString(te640, 2);
            val += te640;
            index++;
        }
        str = val;
    }
    else if (s[0] == 'X')
    {
        int index = 2;
        while (index < s.length() && s[index] != '\'' && s[index] != ' ')
            str += s[index++];
    }
    else
    {
        error = true;
        ferror << "ERROR LINE:" << line << " undefined literal type\n";
        // cout<<"ERROR LINE:"<<line<<" undefined literal type\n";
    }
    return str;
}
string string_to_ascii_hex(const std::string &input)
{
    string result;
    for (char c : input)
    {
        // Convert each character to its ASCII hexadecimal equivalent
        char hex[3];
        sprintf(hex, "%02X", c);
        result += hex;
    }
    return result;
}
string dec_to_hexa(int decimal)
{
    std::stringstream stream;
    stream << std::hex << std::uppercase << decimal;
    std::string hex = stream.str();
    // Convert to uppercase
    std::transform(hex.begin(), hex.end(), hex.begin(), ::toupper);
    // Ensure the output is at most 4 characters long
    if (hex.length() > 4)
    {
        hex = hex.substr(0, 4);
    }
    // Pad with zeros if the length is less than 4
    if (hex.length() < 4)
    {
        hex = std::string(4 - hex.length(), '0') + hex;
    }
    return hex;
}

bool all_num(string x)
{
    bool iall_num = true;
    int i = 0;
    while (all_num && (i < x.length()))
    {
        iall_num &= isdigit(x[i++]);
    }
    return iall_num;
}

void eval_operand(string s, int &abs, bool &error, int &temp_value, string csect_name, int line, ofstream &errorsfile)
{
    string str = "", operand;
    temp_value = 0;
    if (s[0] == 'X')
    { // If value is given in hexadecimal
        int ind = 1;
        while (s[ind] != '\'')
            ind++;
        ind++;
        while (s[ind] != ' ')
            str += s[ind++];
        temp_value = stringToDecimal(str);
    }
    else
    {
        stringstream ss(s);
        ss >> operand;
        if (all_num(operand))
        {
            temp_value += stoi(operand);
        }
        else if (CSECT[csect_name].SYM_TAB[operand].exists)
        {
            temp_value += CSECT[csect_name].SYM_TAB[operand].address;
            abs++;
        }
        else
        {
            error = true;
            abs += 1000;
            errorsfile << "ERROR: LINE-1" << line << " " << operand << " is not defined in symbol table\n";
        }
        while (ss >> operand)
        {
            char oprtr = operand[0];
            operand = operand.substr(1, operand.length() - 1);
            switch (oprtr)
            {
            case '+':
                if (all_num(operand))
                {
                    temp_value += stoi(operand);
                }
                else if (CSECT[csect_name].SYM_TAB[operand].exists)
                {
                    temp_value += CSECT[csect_name].SYM_TAB[operand].address;
                    abs++;
                }
                else
                {
                    error = true;
                    errorsfile << "ERROR: LINE-2" << line << " " << operand << " is not defined in symbol table\n";
                }
                break;
            case '-':
                if (all_num(operand))
                {
                    temp_value -= stoi(operand);
                }
                else if (CSECT[csect_name].SYM_TAB[operand].exists)
                {
                    temp_value -= CSECT[csect_name].SYM_TAB[operand].address;
                    abs--;
                }
                else
                {
                    error = true;
                    errorsfile << "ERROR: LINE-3" << line << " " << operand << " is not defined in symbol table\n";
                }
                break;
            case '*':
            case '/':
                error = true;
                errorsfile << "ERROR: LINE-4" << line << " " << oprtr << " is not usable in expression\n";

                // cout<<"ERROR: LINE"<<line<<" "<<oprtr<<" is not usable in expression\n";
                break;
            default:
                error = true;
                errorsfile << "ERROR: LINE-5" << line << " " << oprtr << " is not defined\n";

                break;
            }
        }
    }
}
int convertHexToDec(string hexString)
{
    stringstream stream;
    int dec;
    stream << hexString;
    stream >> hex >> dec;
    return dec;
}
string eval_expression(string str, bool &indexed, bool &error, ofstream &ferror, string csect_name, int line, int LOC, vector<string> &M, string tm, int &rel, int &tempval)
{
    string res = "";
    rel = 0;
    tempval = 0;
    string operand;
    bool ext = false;
    indexed = false;
    string operand1;
    stringstream ss(str);
    string tempM = "M";
    string t88 = "";
    if (tm == "06")
        t88 = convertDecToHex(LOC);
    else if (tm == "05" || tm == "03")
        t88 = convertDecToHex(LOC + 1);
    else
        t88 = convertDecToHex(LOC);
    changeString(t88, 6);
    tempM += t88;
    tempM += tm;
    ss >> operand;
    operand1 = operand;
    if (operand[0] == '#' || operand[0] == '@')
        operand = operand.substr(1, operand.length() - 1);
    if (all_num(operand))
    {
        tempval += stoi(operand);
    }
    else if (CSECT[csect_name].SYM_TAB[operand].exists)
    {
        tempval += CSECT[csect_name].SYM_TAB[operand].address;
        if (CSECT[csect_name].SYM_TAB[operand].isrelative)
            rel++;
    }
    else if (CSECT[csect_name].EXTREF_TAB[operand].exists)
    {
        // add modification record
        ext = true;
        string sir = operand;
        for (int i = 1; i <= 6 - operand.length(); i++)
            sir += " ";
        string str = tempM + "+" + sir;
        M.push_back(str);
    }
    else if (operand[0] == '*' && tm == "06")
    {
        // locctr
        res = t88;
    }
    else
    {
        error = true;
        rel += 1000;
        ferror << "ERROR: LINE" << line << " " << operand << " is not defined \n";
    }

    while (ss >> operand)
    {
        char oprtr = operand[0];
        operand = operand.substr(1, operand.length() - 1);
        switch (oprtr)
        {
        case '+':
            if (all_num(operand))
            {
                tempval += stoi(operand);
            }
            else if (CSECT[csect_name].SYM_TAB[operand].exists)
            {
                tempval += CSECT[csect_name].SYM_TAB[operand].address;
                if (CSECT[csect_name].SYM_TAB[operand].isrelative)
                    rel++;
            }
            else if (CSECT[csect_name].EXTREF_TAB[operand].exists)
            {
                // add modification record
                ext = true;
                string sir = operand;
                for (int i = 1; i <= 6 - operand.length(); i++)
                    sir += " ";
                string str = tempM + "+" + sir;
                M.push_back(str);
            }
            else
            {
                error = true;
                rel += 1000;
                ferror << "ERROR: LINE" << line << " " << operand << " is not defined \n";
            }
            break;
        case '-':
            if (all_num(operand))
            {
                tempval -= stoi(operand);
            }
            else if (CSECT[csect_name].SYM_TAB[operand].exists)
            {
                tempval -= CSECT[csect_name].SYM_TAB[operand].address;
                if (CSECT[csect_name].SYM_TAB[operand].isrelative)
                    rel--;
            }
            else if (CSECT[csect_name].EXTREF_TAB[operand].exists)
            {
                // add modification record
                ext = true;
                string sir = operand;
                for (int i = 1; i <= 6 - operand.length(); i++)
                    sir += " ";
                string str = tempM + "-" + sir;
                M.push_back(str);
            }
            else
            {
                error = true;
                rel += 1000;
                ferror << "ERROR: LINE" << line << " " << operand << " is not defined \n";
            }
            break;
        case ',':
            if (operand[0] == 'X')
                indexed = true;
            // did not expect ,
            break;
        case '*':
        case '/':
            error = true;
            ferror << "ERROR LINE:" << line << " " << oprtr << "is not usable in the expression\n";
            break;
        default:
            error = true;
            ferror << "ERROR: LINE" << line << " " << oprtr << " is not defined\n";
            break;
        }
    }

    if (!ext && rel == 1)
    {
        string sir = CSECT[csect_name].name;
        for (int i = 1; i <= 6 - operand.length(); i++)
            sir += " ";
        string str = tempM + "+" + sir;
        if (tm == "05")
            M.push_back(str);
    }
    else if (!ext && rel == -1)
    {
        string sir = CSECT[csect_name].name;
        for (int i = 1; i <= 6 - operand.length(); i++)
            sir += " ";
        string str = tempM + "-" + sir;
        if (tm == "05")
            M.push_back(str);
    }
    else if (!ext && abs(rel) > 1)
    {
        error = true;
        ferror << "ERROR LINE:" << line << " Invalid expression \n";
    }
    res = convertDecToHex(tempval);
    return res;
}

void pass1(ifstream &OPO, ofstream &intermediatefile, ofstream &errorsfile, bool &error)
{

    string instruct, operand, label, s, CsectName = "DEFAULT";
    int line = 0;

    while (getline(OPO, s))
    {

        int curr = CSECT[CsectName].LOCCTR;
        line++;
        stringstream str(s);

        bool p = false;
        str >> label;
        if (label[0] == '+' && OPTABLE[label.substr(1, label.length() - 1)].exists)
        {
            label = label.substr(1, label.length() - 1);
            p = true;
        }

        if (ASSDIR[label] || OPTABLE[label].exists)
        {
            instruct = label;
            label = "";
            getline(str, operand);
        }
        else
        {
            str >> instruct;
            getline(str, operand);
        }

        if (instruct[0] == '+')
        {
            p = true;
            instruct = instruct.substr(1, instruct.length() - 1);
        }

        if (operand[0] == ' ')
        {
            int k = 0;
            while (operand[k] == ' ')
            {
                k++;
            }

            operand = operand.substr(k, operand.length() - k);
        }

        if (label.length() != 0)
        {
            if (CSECT[CsectName].SYM_TAB[label].exists)
            {
                error = true;
                errorsfile << "ERROR LINE:" << line << " duplicate symbol " << label << "\n";
            }
        }

        if (instruct == "START")
        {
            CSECT[CsectName].start = stringToDecimal(operand);
            CSECT[CsectName].LOCCTR = stringToDecimal(operand);
            CSECT[CsectName].name = label;

            intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR);
            intermediatefile << " " << s << endl;
        }
        else if (instruct == "CSECT")
        {
            intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;
            for (auto &i : CSECT[CsectName].LIT_TAB)
            {

                if (i.second.written)
                {
                    CSECT[CsectName].LIT_TAB[i.first].address = CSECT[CsectName].LOCCTR;
                    CSECT[CsectName].LIT_TAB[i.first].written = false;
                    intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " * =X" << CSECT[CsectName].LIT_TAB[i.first].value << "\'" << endl;
                    CSECT[CsectName].LOCCTR += CSECT[CsectName].LIT_TAB[i.first].value.length() / 2;
                }
            }

            CSECT[CsectName].length = CSECT[CsectName].LOCCTR - CSECT[CsectName].start;
            CsectName = label;
            CSECT[CsectName].name = label;
        }
        else
        {

            if (label.length() != 0)
            {
                if (!error)
                {
                    CSECT[CsectName].SYM_TAB[label].exists = true;
                    CSECT[CsectName].SYM_TAB[label].address = CSECT[CsectName].LOCCTR;
                    CSECT[CsectName].SYM_TAB[label].isrelative = 1;
                }
            }

            if (instruct == "END")
            {
                intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;
                ;
                for (auto &i : CSECT[CsectName].LIT_TAB)
                {
                    if (i.second.written)
                    {
                        CSECT[CsectName].LIT_TAB[i.first].address = CSECT[CsectName].LOCCTR;
                        CSECT[CsectName].LIT_TAB[i.first].written = false;
                        intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " * =X'" << CSECT[CsectName].LIT_TAB[i.first].value << "\'" << endl;
                        CSECT[CsectName].LOCCTR += CSECT[CsectName].LIT_TAB[i.first].value.length() / 2;
                    }
                }
                CSECT[CsectName].length = CSECT[CsectName].LOCCTR - CSECT[CsectName].start;
            }
            else if (OPTABLE[instruct].exists)
            {
                bool h = false;
                if (operand.length() != 0)
                {

                    string A;
                    stringstream B(operand);
                    B >> A;
                    if (A[0] == '=')
                    {
                        if (A[1] == 'X')
                        {
                            int index = 3;
                            string val = "";

                            while (index < A.length() && (A[index] != '\'' && A[index] != ' '))
                            {
                                val += A[index];
                                index++;
                            }
                            if (!CSECT[CsectName].LIT_TAB[A].exists)
                            {
                                CSECT[CsectName].LIT_TAB[val].value = val;
                                CSECT[CsectName].LIT_TAB[val].exists = true;
                                CSECT[CsectName].LIT_TAB[val].written = true;
                            }
                        }
                        else if (A[1] == 'C')
                        {
                            int index = 3;
                            string val = "";
                            while (index < A.length() && (A[index] != '\'' && A[index] != ' '))
                            {
                                val += A[index];
                                index++;
                            }
                            val = string_to_ascii_hex(val);
                            if (!CSECT[CsectName].LIT_TAB[A].exists)
                            {
                                CSECT[CsectName].LIT_TAB[val].value = val;
                                CSECT[CsectName].LIT_TAB[val].exists = true;
                                CSECT[CsectName].LIT_TAB[val].written = true;
                            }
                        }
                        else
                        {
                            error = true;
                            errorsfile << "ERROR LINE:" << line << " undefined literal type\n";
                        }

                        intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;

                        h = true;
                    }
                }

                if (!h)
                {
                    intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;
                }
                CSECT[CsectName].LOCCTR += OPTABLE[instruct].format;
                if (p)
                {
                    CSECT[CsectName].LOCCTR++;
                }
            }
            else if (instruct == "LTORG")
            {

                intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;
                for (auto &i : CSECT[CsectName].LIT_TAB)
                {
                    if (i.second.written)
                    {
                        CSECT[CsectName].LIT_TAB[i.first].address = CSECT[CsectName].LOCCTR;
                        CSECT[CsectName].LIT_TAB[i.first].written = false;
                        intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " * =X'" << CSECT[CsectName].LIT_TAB[i.first].value << "'" << endl;
                        CSECT[CsectName].LOCCTR += CSECT[CsectName].LIT_TAB[i.first].value.length() / 2;
                    }
                }
            }

            else if (instruct == "EQU")
            {
                if (label.length() != 0)
                {
                    CSECT[CsectName].SYM_TAB[label].exists = true;

                    CSECT[CsectName].SYM_TAB[label].isrelative = 0;
                    if (operand[0] == '*')
                    {
                        CSECT[CsectName].SYM_TAB[label].address = curr;
                    }
                    else
                    {
                        int tval = 0, ab = 0;
                        eval_operand(operand, ab, error, tval, CsectName, line, errorsfile);
                        CSECT[CsectName].SYM_TAB[label].address = tval;
                    }
                }
                else
                {
                    error = true;
                    errorsfile << "ERROR LINE:" << line << " Label Expeted for EQU directive \n";
                }

                intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;
            }
            else if (instruct == "ORG")
            {
                if (operand.length() != 0)
                {
                    int tval = 0, ab = 0;
                    eval_operand(operand, ab, error, tval, CsectName, line, errorsfile);
                    CSECT[CsectName].org_stack.push(curr);
                    CSECT[CsectName].LOCCTR = tval;
                }
                else
                {
                    if (CSECT[CsectName].org_stack.size() != 0)
                    {
                        CSECT[CsectName].LOCCTR = CSECT[CsectName].org_stack.top();
                        CSECT[CsectName].org_stack.pop();
                    }
                    else
                    {
                        error = true;
                        errorsfile << "ERROR: The ORG stack is empty\n";
                    }
                }
            }
            else if (instruct == "WORD")
            {
                intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;
                CSECT[CsectName].LOCCTR += 3;
            }
            else if (instruct == "BYTE")
            {
                intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;
                string A;
                stringstream B(operand);
                B >> A;
                string val = "";
                int index = 2;
                if (A[0] == 'X')
                {

                    while (index < A.length() && (A[index] != '\'' && A[index] != ' '))
                    {
                        val += A[index];
                        index++;
                    }
                }
                else if (A[0] == 'C')
                {

                    while (index < A.length() && (A[index] != '\'' && A[index] != ' '))
                    {
                        val += A[index];
                        index++;
                    }
                    val = string_to_ascii_hex(val);
                }
                CSECT[CsectName].LOCCTR += val.length() / 2;
            }
            else if (instruct == "RESW")
            {
                intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;
                int t = 0;
                int a = 0;
                eval_operand(operand, a, error, t, CsectName, line, errorsfile);
                CSECT[CsectName].LOCCTR += 3 * t;
                if (a != 0)
                {
                    error = true;
                    errorsfile << "ERROR: LINE" << line << " expression is not absolute value\n";
                }
            }
            else if (instruct == "RESB")
            {
                intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;
                int t = 0;
                int a = 0;
                eval_operand(operand, a, error, t, CsectName, line, errorsfile);
                CSECT[CsectName].LOCCTR += t;
                if (a != 0)
                {
                    error = true;
                    errorsfile << "ERROR: LINE" << line << " expression is not absolute value\n";
                }
            }
            else if (instruct == "EXTDEF" || instruct == "BASE" || instruct == "NOBASE")
            {
                intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;
            }
            else if (instruct == "EXTREF")
            {
                stringstream A(operand);
                string B;
                while (A >> B)
                {
                    if (B[0] == ',')
                    {
                        B = B.substr(1, B.length() - 1);
                    }
                    CSECT[CsectName].EXTREF_TAB[B].exists = true;
                    CSECT[CsectName].EXTREF_TAB[B].value = B;
                }
                intermediatefile << dec_to_hexa(CSECT[CsectName].LOCCTR) << " " << s << endl;
            }
            else
            {
                error = true;
                errorsfile << "ERROR LINE:" << line << " INVALID OPERATION CODE\n";
            }
        }
        if (label.length() > 6)
        {
            error = true;
            errorsfile << "ERROR LINE:" << line << " used " << label << " with length more than 6\n";
        }
    }
}

void pass2(ifstream &in, ofstream &errorsfile, bool &error, ofstream &ou, ofstream &LFile)
{
    LFile << "LINE"
          << "  LOCCTR  INSTRUCTION           OBJECT CODE\n";
    string H;
    vector<string> T;
    string tempT = "";
    vector<string> D;
    string tempD = "";
    vector<string> R;
    string tempR = "";
    vector<string> M;
    string tempM = "";
    string E;
    string label, opcode, operand, tempstr, csect_name = "DEFAULT", obj_code;
    int curr = 0;
    int operand_val = 0, line = 0;
    int locctr = 0;
    int LEN = 0, ni = 0, xbpe = 0;
    while (getline(in, tempstr))
    {
        obj_code = "";
        ni = 0;
        xbpe = 0;
        curr = locctr;
        label = opcode = operand = "";
        bool bn4 = false;
        line++;
        obj_code += to_string(line) + "  ";
        obj_code += convertDecToHex(locctr) + "  ";
        obj_code += tempstr;
        stringstream ss1(tempstr);
        ss1 >> label;
        if (label[0] == '+' && OPTABLE[label.substr(1, label.length() - 1)].exists)
        {
            bn4 = true;
            label = label.substr(1, label.length() - 1);
        }
        if (OPTABLE[label].exists || ASSDIR[label])
        {
            opcode = label;
            label = "";
            getline(ss1, operand);
        }
        else
        {
            ss1 >> opcode;
            getline(ss1, operand);
        }
        if (opcode[0] == '+')
        {
            bn4 = true;
            opcode = opcode.substr(1, opcode.length() - 1);
        }
        if (operand[0] == ' ')
        {
            int index646 = 0;
            while (operand[index646] == ' ')
                index646++;
            operand = operand.substr(index646, operand.length() - index646);
        }
        if (opcode == "START")
        {
            ss1.clear();
            ss1 << operand;
            ss1 >> operand;
            locctr = convertHexToDec(operand);
            H += "H";
            if (label.length() > 6)
            {
                error = true;
                errorsfile << "ERROR LINE:" << line << " expecting 6 character program name\n";
            }
            string tem43 = CSECT[csect_name].name;
            for (int i = 1; i <= 6 - CSECT[csect_name].name.length(); i++)
            {
                tem43 += " ";
            }
            H = H + tem43;
            string t88 = convertDecToHex(locctr);
            changeString(t88, 6);
            H += t88;
            LEN = 0;
        }
        else if (opcode == "CSECT")
        {

            for (auto ele : CSECT[csect_name].LIT_TAB)
            {
                if (ele.second.written)
                {
                    if (tempT.length() == 0)
                    {
                        tempT = "T";
                        string te88 = convertDecToHex(curr);
                        changeString(te88, 6);
                        tempT += te88;
                    }
                    CSECT[csect_name].LIT_TAB[ele.first].address = locctr;
                    LFile << line << "  " << convertDecToHex(locctr) << " * =X\'" << ele.second.value << "\'"
                          << "    " << ele.second.value << endl;
                    curr = locctr;
                    locctr += (ele.second.value.length() / 2);
                    LEN += ele.second.value.length() / 2;
                    CSECT[csect_name].LIT_TAB[ele.first].written = false;

                    if (tempT.length() + ele.second.value.length() <= 67)
                    {
                        tempT += ele.second.value;
                    }
                    else
                    {
                        int va901 = tempT.length() - 7;
                        string h902 = convertDecToHex(va901 / 2);
                        changeString(h902, 2);
                        tempT.insert(7, 1, h902[0]);
                        tempT.insert(8, 1, h902[1]);
                        T.push_back(tempT);
                        tempT.clear();
                        tempT = "T";
                        string te88 = convertDecToHex(curr);
                        changeString(te88, 6);
                        tempT += te88;
                        tempT += ele.second.value;
                    }
                }
            }

            string len87 = convertDecToHex(LEN);
            changeString(len87, 6);
            H = H + len87;
            E += "E";
            if (csect_name == "DEFAULT")
            {
                string tem86 = "", temp836 = convertDecToHex(CSECT[csect_name].start);
                for (int i = 1; i <= (6 - temp836.length()); i++)
                {
                    tem86 += "0";
                }
                E = E + tem86 + temp836;
            }

            ou << H << "\n";
            for (auto i : D)
                ou << i << "\n";
            if (tempD.length() != 0)
                ou << tempD << "\n";
            for (auto i : R)
                ou << i << "\n";
            if (tempR.length() != 0)
                ou << tempR << "\n";
            for (auto i : T)
                ou << i << "\n";
            if (tempT.length() != 0)
            {
                int va901 = tempT.length() - 7;
                va901 /= 2;
                string h902 = convertDecToHex(va901);
                changeString(h902, 2);
                tempT.insert(7, 1, h902[0]);
                tempT.insert(8, 1, h902[1]);
                ou << tempT << "\n";
            }
            for (auto i : M)
                ou << i << "\n";
            ou << E << "\n";
            H.clear();
            T.clear();
            D.clear();
            R.clear();
            M.clear();
            E.clear();
            tempD.clear();
            tempT.clear();
            tempM.clear();
            tempR.clear();
            locctr = 0;
            csect_name = label;
            if (operand.length() != 0)
                errorsfile << "ERROR LINE:" << line << " expected no operand for CSECT \n";
            LEN = 0;
            H += "H";
            if (label.length() > 6)
            {
                error = true;
                errorsfile << "ERROR LINE:" << line << " expecting 6 character program name\n";
            }
            string tem43 = CSECT[csect_name].name;
            for (int i = 1; i <= 6 - CSECT[csect_name].name.length(); i++)
            {
                tem43 += " ";
            }
            H = H + tem43;
            H += "000000";
        }
        else
        {
            if (opcode == "END")
            {

                for (auto ele : CSECT[csect_name].LIT_TAB)
                {
                    if (ele.second.written)
                    {
                        if (tempT.length() == 0)
                        {
                            tempT = "T";
                            string te88 = convertDecToHex(curr);
                            changeString(te88, 6);
                            tempT += te88;
                        }
                        CSECT[csect_name].LIT_TAB[ele.first].address = locctr;
                        LFile << line << "  " << convertDecToHex(locctr) << " * =X\'" << ele.second.value << "\'"
                              << "    " << ele.second.value << endl;
                        curr = locctr;
                        locctr += (ele.second.value.length() / 2);
                        LEN += ele.second.value.length() / 2;
                        CSECT[csect_name].LIT_TAB[ele.first].written = false;

                        if (tempT.length() + ele.second.value.length() <= 67)
                        {
                            tempT += ele.second.value;
                        }
                        else
                        {
                            int va901 = tempT.length() - 7;
                            va901 /= 2;
                            string h902 = convertDecToHex(va901);
                            changeString(h902, 2);
                            tempT.insert(7, 1, h902[0]);
                            tempT.insert(8, 1, h902[1]);
                            T.push_back(tempT);
                            tempT.clear();
                            tempT = "T";
                            string te88 = convertDecToHex(curr);
                            changeString(te88, 6);
                            tempT += te88;
                            tempT += ele.second.value;
                        }
                    }
                }
                string len87 = convertDecToHex(LEN);
                changeString(len87, 6);
                H = H + len87;
                E += "E";
                if (csect_name == "DEFAULT")
                {
                    string tem86 = "", temp836 = convertDecToHex(CSECT[csect_name].start);
                    for (int i = 1; i <= (6 - temp836.length()); i++)
                    {
                        tem86 += "0";
                    }
                    E = E + tem86 + temp836;
                }
                ou << H << "\n";
                for (auto i : D)
                    ou << i << "\n";
                if (tempD.length() != 0)
                    ou << tempD << "\n";
                for (auto i : R)
                    ou << i << "\n";
                if (tempR.length() != 0)
                    ou << tempR << "\n";
                for (auto i : T)
                    ou << i << "\n";
                if (tempT.length() != 0)
                {
                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    ou << tempT << "\n";
                }
                for (auto i : M)
                    ou << i << "\n";
                ou << E << "\n";
                LFile << obj_code << "\n";
                H.clear();
                T.clear();
                D.clear();
                R.clear();
                M.clear();
                E.clear();
                tempD.clear();
                tempT.clear();
                tempM.clear();
                tempR.clear();
                return;
            }
            else if (OPTABLE[opcode].exists)
            {
                curr = locctr;
                string tObj = "";
                locctr += OPTABLE[opcode].format;
                LEN += OPTABLE[opcode].format;
                if (bn4)
                {
                    locctr++;
                    LEN++;
                }
                if (OPTABLE[opcode].format == 1)
                { // format 1
                    tObj = OPTABLE[opcode].opcode;
                }
                else if (OPTABLE[opcode].format == 2)
                { // format 2
                    tObj = OPTABLE[opcode].opcode;
                    stringstream ss106(operand);
                    string s106;
                    while (ss106 >> s106)
                    {
                        if (s106[0] == ',')
                            s106 = s106.substr(1, s106.length() - 1);
                        if (REG_TAB[s106].exists)
                        {
                            tObj += (char)REG_TAB[s106].number;
                        }
                        else
                        {
                            error = true;
                            errorsfile << "ERROR LINE:" << line << " The register \'" << s106 << "\' is not valid\n";
                        }
                    }
                    int x = tObj.length();
                    for (int i = 1; i <= 4 - x; i++)
                    {
                        tObj += "0";
                    }
                }
                else if (opcode == "RSUB")
                {
                    tObj = "4F0000";
                    if (bn4)
                        tObj += "00";
                }
                else if (OPTABLE[opcode].format == 3)
                {
                    stringstream ss108(operand);
                    string opr;
                    ss108 >> opr;
                    int opc = convertHexToDec(OPTABLE[opcode].opcode), expr = 0;
                    if (bn4)
                    {             // format 4
                        xbpe = 1; // e=1;
                        if (opr[0] == '@')
                        {
                            ni = 2; // n=1
                            opr = opr.substr(1, opr.length() - 1);
                            string tm = "05";
                            bool indexed = 0;
                            int rel = 0, tempval = 0;
                            string val10 = eval_expression(operand, indexed, error, errorsfile, csect_name, line, curr, M, tm, rel, tempval);
                            changeString(val10, 5);
                            opc += ni;
                            string st1 = convertDecToHex(opc);
                            changeString(st1, 2);
                            tObj += st1;
                            st1 = convertDecToHex(xbpe);
                            changeString(st1, 1);
                            tObj += st1;
                            tObj += val10;
                            ss108 >> opr;
                            if (opr[1] == 'X')
                            {
                                error = true;
                                errorsfile << "ERROR LINE:" << line << " cannot use indexed with indirect addressing mode\n";
                            }
                        }
                        else if (operand[0] == '#')
                        {
                            ni = 1;   // i=1
                            xbpe = 1; // e=1
                            opr = opr.substr(1, opr.length() - 1);
                            string tm = "05";
                            bool indexed = 0;
                            int rel = 0, tempval;
                            string val10 = eval_expression(operand, indexed, error, errorsfile, csect_name, line, curr, M, tm, rel, tempval);
                            changeString(val10, 5);
                            opc += ni;
                            string st1 = convertDecToHex(opc);
                            changeString(st1, 2);
                            tObj += st1;
                            st1 = convertDecToHex(xbpe);
                            changeString(st1, 1);
                            tObj += st1;
                            st1 = convertDecToHex(tempval);
                            changeString(st1, 5);
                            tObj += st1;
                            ss108 >> opr;
                            if (opr[1] == 'X')
                            {
                                error = true;
                                errorsfile << "ERROR LINE:" << line << " cannot use inedxed with immediate addressing mode\n";
                            }
                        }
                        else
                        {
                            tempM = "M";
                            string t88 = convertDecToHex(curr + 1);
                            changeString(t88, 6);
                            tempM += t88;
                            tempM += "05";
                            ni = 3;   // ni=3
                            xbpe = 1; // e=1;
                            int val10 = 0;
                            if (CSECT[csect_name].SYM_TAB[opr].exists)
                            {
                                val10 = CSECT[csect_name].SYM_TAB[opr].address;
                                tempM += '+' + CSECT[csect_name].name;
                                M.push_back(tempM);
                                tempM.clear();
                            }
                            else if (CSECT[csect_name].EXTREF_TAB[opr].exists)
                            {
                                val10 = 0;
                                tempM += '+' + opr;
                                M.push_back(tempM);
                                tempM.clear();
                            }
                            else
                            {
                                error = true;
                                errorsfile << "ERROR LINE:" << line << " Invalid operand \n";
                            }
                            ss108 >> opr;
                            if (opr[1] == 'X')
                            {
                                xbpe += 8;
                            }
                            opc += ni;
                            string st1 = convertDecToHex(opc);
                            changeString(st1, 2);
                            tObj += st1;
                            st1 = convertDecToHex(xbpe);
                            changeString(st1, 1);
                            tObj += st1;
                            st1 = convertDecToHex(val10);
                            changeString(st1, 5);
                            tObj += st1;
                        }
                    }
                    else
                    { // format 3
                        string tm = "03";
                        int val = 0, opc;
                        opc = convertHexToDec(OPTABLE[opcode].opcode);
                        stringstream ss117(operand);
                        string opr;
                        ss117 >> opr;
                        if (opr[0] == '@')
                        {
                            ni = 2; // indirect
                            int tval = 0;
                            opr = opr.substr(1, opr.length() - 1);
                            if (CSECT[csect_name].SYM_TAB[opr].exists)
                            {
                                val = CSECT[csect_name].SYM_TAB[opr].address;
                                val = val - locctr;
                                if (val >= 2048 || val < -2048)
                                {
                                    if (CSECT[csect_name].base.length() != 0)
                                    {
                                        tval = CSECT[csect_name].SYM_TAB[CSECT[csect_name].base].address;
                                        val = val + locctr - tval;
                                        if (val < 0 || val > 4095)
                                        {
                                            error = true;
                                            errorsfile << "ERROR LINE:" << line << " disp out of bounds for BASE relative\n";
                                        }
                                        else
                                        {
                                            xbpe += 4;
                                        }
                                    }
                                    else
                                    {
                                        error = true;
                                        errorsfile << "ERROR LINE:" << line << " disp out of bounds for PC relative"
                                                   << "\n";
                                    }
                                }
                                else
                                {
                                    xbpe += 2;
                                }
                            }
                            else if (CSECT[csect_name].EXTREF_TAB[opr].exists)
                            {
                                tempM = "M";
                                string t88 = convertDecToHex(curr + 1);
                                changeString(t88, 6);
                                tempM += t88;
                                tempM += tm;
                                tempM += '+';
                                tempM += opr;
                                if (opr.length() > 6)
                                {
                                    error = true;
                                    errorsfile << "ERROR LINE:" << line << " length of operand more than 6\n";
                                }
                                M.push_back(tempM);
                                tempM.clear();
                            }
                            else
                            {
                                error = true;
                                errorsfile << "ERROR LINE:" << line << " operand " << opr << " not defined\n";
                            }
                            ss117 >> opr;
                        }
                        else if (opr[0] == '#')
                        {
                            ni = 1; // immediate
                            opr = opr.substr(1, opr.length() - 1);
                            bool indexed = false;
                            int rel = 0, tempval = 0;
                            string val12 = eval_expression(operand, indexed, error, errorsfile, csect_name, line, curr, M, tm, rel, tempval);
                            if (rel == 0)
                            { // absolute value
                                if (tempval > 2047 || tempval < -2048)
                                {
                                    error = true;
                                    errorsfile << "ERROR LINE:" << line << " The value exceeds 3 half bytes\n";
                                }
                                val = tempval;
                            }
                            else
                            {
                                int tval = 0;
                                val = tempval - locctr;
                                if (val > 2047 || val < -2048)
                                {
                                    if (CSECT[csect_name].base.length() != 0)
                                    {
                                        tval = CSECT[csect_name].SYM_TAB[CSECT[csect_name].base].address;
                                        val = val + locctr - tval;
                                        if (val < 0 || val > 4095)
                                        {
                                            error = true;
                                            errorsfile << "ERROR LINE:" << line << " disp out of bounds for BASE relative\n";
                                        }
                                        else
                                        {
                                            xbpe += 4;
                                        }
                                    }
                                    else
                                    {
                                        error = true;
                                        errorsfile << "ERROR LINE:" << line << " disp out of bounds for PC relative"
                                                   << "\n";
                                    }
                                }
                                else
                                {
                                    xbpe += 2; // p=1
                                }
                            }
                            if (indexed)
                            {
                                error = true;
                                errorsfile << "ERROR LINE:" << line << " indexed with immediate not allowed\n";
                            }
                        }
                        else
                        {
                            ni = 3; // simple
                            if (opr[0] == '=')
                            { // liteerals
                                if (opr[1] == 'C')
                                {
                                    int index = 3;
                                    string val12 = "";
                                    int ch637;
                                    while (index < opr.length() && (opr[index] != '\'' && opr[index] != ' '))
                                    {
                                        ch637 = (int)opr[index];
                                        string te640 = convertDecToHex(ch637);
                                        changeString(te640, 2);
                                        val12 += te640;
                                        index++;
                                    }
                                    if (!CSECT[csect_name].LIT_TAB[val12].written)
                                    {
                                        CSECT[csect_name].LIT_TAB[val12].written = true;
                                    }
                                    val = CSECT[csect_name].LIT_TAB[val12].address;
                                }
                                else if (opr[1] == 'X')
                                {
                                    int index = 3;
                                    string val12 = "";
                                    while (index < opr.length() && (opr[index] != '\'' && opr[index] != ' '))
                                    {
                                        val12 += opr[index];
                                        index++;
                                    }
                                    if (!CSECT[csect_name].LIT_TAB[val12].written)
                                    {
                                        CSECT[csect_name].LIT_TAB[val12].written = true;
                                    }
                                    val = CSECT[csect_name].LIT_TAB[val12].address;
                                }
                                int tval = 0;
                                val = val - locctr;
                                if (val > 2047 || val < -2048)
                                {
                                    if (CSECT[csect_name].base.length() != 0)
                                    {
                                        tval = CSECT[csect_name].SYM_TAB[CSECT[csect_name].base].address;
                                        val = val + locctr - tval;
                                        if (val < 0 || val > 4095)
                                        {
                                            error = true;
                                            errorsfile << "ERROR LINE:" << line << " disp out of bounds for BASE relative\n";
                                        }
                                        else
                                        {
                                            xbpe += 4;
                                        }
                                    }
                                    else
                                    {
                                        error = true;
                                        errorsfile << "ERROR LINE:" << line << " disp out of bounds for PC relative"
                                                   << "\n";
                                    }
                                }
                                else
                                {
                                    xbpe += 2; // 1;
                                }
                            }
                            else
                            { // normal
                                bool indexed = false;
                                int rel = 0, tempval = 0;
                                string val1 = eval_expression(operand, indexed, error, errorsfile, csect_name, line, curr, M, tm, rel, tempval);
                                if (rel == 0)
                                {
                                    if (tempval > 2047 || tempval < -2048)
                                    {
                                        error = true;
                                        errorsfile << "ERROR LINE:" << line << " disp value out of bounds\n";
                                    }
                                    else
                                    {
                                        val = tempval;
                                    }
                                }
                                else
                                {
                                    int tval = 0;
                                    val = tempval - locctr;
                                    if (val > 2047 || val < -2048)
                                    {
                                        if (CSECT[csect_name].base.length() != 0)
                                        {
                                            tval = CSECT[csect_name].SYM_TAB[CSECT[csect_name].base].address;
                                            val = val + locctr - tval;
                                            if (val < 0 || val > 4095)
                                            {
                                                error = true;
                                                errorsfile << "ERROR LINE:" << line << " disp out of bounds for BASE relative\n";
                                            }
                                            else
                                            {
                                                xbpe += 4;
                                            }
                                        }
                                        else
                                        {
                                            error = true;
                                            errorsfile << "ERROR LINE:" << line << " disp out of bounds for PC relative"
                                                       << "\n";
                                        }
                                    }
                                    else
                                    {
                                        xbpe += 2; // p=1
                                    }
                                }
                                if (indexed)
                                    xbpe += 8;
                            }
                        }
                        opc += ni;
                        string sti = convertDecToHex(opc);
                        changeString(sti, 2);
                        tObj += sti;
                        sti = convertDecToHex(xbpe);
                        changeString(sti, 1);
                        tObj += sti;
                        sti = convertDecToHex(val);
                        changeString(sti, 3);
                        tObj += sti;
                    }
                }
                // add tempT obj_code here
                obj_code += "  " + tObj;
                if (tempT.length() == 0)
                {
                    tempT = "T";
                    string t88 = convertDecToHex(curr);
                    changeString(t88, 6);
                    tempT += t88;
                }
                if (tempT.length() + tObj.length() <= 67)
                {
                    tempT += tObj;
                }
                else
                {
                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    T.push_back(tempT);
                    tempT.clear();
                    tempT = "T";
                    string te88 = convertDecToHex(curr);
                    changeString(te88, 6);
                    tempT += te88;
                    tempT += tObj;
                }
            }
            else if (opcode == "LTORG")
            {
                // handle LTORG here
                for (auto ele : CSECT[csect_name].LIT_TAB)
                { // HANDLING LTORG
                    if (ele.second.written)
                    {
                        if (tempT.length() == 0)
                        {
                            tempT = "T";
                            string te88 = convertDecToHex(curr);
                            changeString(te88, 6);
                            tempT += te88;
                        }
                        CSECT[csect_name].LIT_TAB[ele.first].address = locctr;
                        LFile << line << "  " << convertDecToHex(locctr) << " * =X\'" << ele.second.value << "\'"
                              << "    " << ele.second.value << endl;
                        curr = locctr;
                        locctr += (ele.second.value.length() / 2);
                        LEN += ele.second.value.length() / 2;
                        CSECT[csect_name].LIT_TAB[ele.first].written = false;
                        // text record entry
                        if (tempT.length() + ele.second.value.length() <= 67)
                        {
                            tempT += ele.second.value;
                        }
                        else
                        {
                            int va901 = tempT.length() - 7;
                            string h902 = convertDecToHex(va901 / 2);
                            changeString(h902, 2);
                            tempT.insert(7, 1, h902[0]);
                            tempT.insert(8, 1, h902[1]);
                            T.push_back(tempT);
                            tempT.clear();
                            tempT = "T";
                            string te88 = convertDecToHex(curr);
                            changeString(te88, 6);
                            tempT += te88;
                            tempT += ele.second.value;
                        }
                    }
                }
            }
            else if (opcode == "EQU")
            {

                // do nothing
            }
            else if (opcode == "ORG")
            {
                if (operand.length() != 0)
                {
                    int abs = 0, temp12 = 0;
                    eval_operand(operand, abs, error, temp12, csect_name, line, errorsfile);
                    CSECT[csect_name].org_stack.push(curr);
                    locctr = temp12;
                }
                else
                {
                    if (!CSECT[csect_name].org_stack.empty())
                    {
                        int temp12 = CSECT[csect_name].org_stack.top();
                        CSECT[csect_name].org_stack.pop();
                        locctr = temp12;
                    }
                    else
                    {
                        error = true;
                        errorsfile << "ERROR: The ORG stack is empty\n";
                    }
                }
            }
            else if (opcode == "WORD")
            {
                // add word to text record
                string tm = "06";
                bool indexed = 0;
                int rel = 0, tempval;
                string val1157 = eval_expression(operand, indexed, error, errorsfile, csect_name, line, locctr, M, tm, rel, tempval);
                changeString(val1157, 6);
                obj_code += " " + val1157;
                if (tempT.length() == 0)
                {
                    tempT = "T";
                    string te88 = convertDecToHex(curr);
                    changeString(te88, 6);
                    tempT += te88;
                }
                if (tempT.length() + 6 <= 67)
                {
                    tempT += val1157;
                }
                else
                {
                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    T.push_back(tempT);
                    tempT.clear();
                    tempT = "T";
                    string te88 = convertDecToHex(curr);
                    changeString(te88, 6);
                    tempT += te88;
                    tempT += val1157;
                }
                locctr += 3;
                LEN += 3;
            }
            else if (opcode == "BYTE")
            {
                string s731 = convertQuote(operand, line, error, errorsfile);
                locctr += (s731.length() / 2);
                LEN += (s731.length() / 2);
                if (tempT.length() == 0)
                {
                    tempT = "T";
                    string te88 = convertDecToHex(curr);
                    changeString(te88, 6);
                    tempT += te88;
                }
                if (tempT.length() + s731.length() <= 67)
                {
                    tempT += s731;
                }
                else
                {
                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    T.push_back(tempT);
                    tempT.clear();
                    tempT = "T";
                    string te88 = convertDecToHex(curr);
                    changeString(te88, 6);
                    tempT += te88;
                    tempT += s731;
                }
                obj_code += " " + s731;
            }
            else if (opcode == "RESW")
            {
                if (tempT.length() != 0)
                {

                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    T.push_back(tempT);
                    tempT.clear();
                }
                // stop text record
                int temp733 = 0;
                int abs738 = 0;
                eval_operand(operand, abs738, error, temp733, csect_name, line, errorsfile);
                locctr += 3 * temp733;
                LEN += 3 * temp733;
                if (abs738 != 0)
                {
                    error = true;
                    errorsfile << "ERROR: LINE" << line << " expression is not absolute value\n";
                    // cout<<"ERROR: LINE"<<line<<" expression is not absolute value\n";
                }
            }
            else if (opcode == "RESB")
            {
                if (tempT.length() != 0)
                {
                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    T.push_back(tempT);
                    tempT.clear();
                }
                // stop text record
                int temp736 = 0;
                int abs742 = 0;
                eval_operand(operand, abs742, error, temp736, csect_name, line, errorsfile);
                cout << temp736 << endl;
                locctr += temp736;
                LEN += temp736;
                if (abs742 != 0)
                {
                    error = true;
                    errorsfile << "ERROR: LINE" << line << " expression is not absolute value\n";
                    // cout<<"ERROR: LINE"<<line<<" expression is not absolute value\n";
                }
            }
            else if (opcode == "EXTDEF")
            {
                // add to D record
                string sd27;
                if (tempD.length() == 0)
                    tempD = "D";
                stringstream ss102(operand);
                while (ss102 >> sd27)
                {
                    if (sd27[0] == ',')
                        sd27 = sd27.substr(1, sd27.length() - 1);
                    string strd103 = sd27;
                    if (CSECT[csect_name].SYM_TAB[sd27].exists)
                    {
                        string valu103 = convertDecToHex(CSECT[csect_name].SYM_TAB[sd27].address);
                        changeString(valu103, 6);
                        for (int i = 1; i <= 6 - sd27.length(); i++)
                            strd103 += " ";
                        strd103 += valu103;
                        if (tempD.length() + 12 <= 73)
                        {
                            tempD += strd103;
                        }
                        else
                        {
                            D.push_back(tempD);
                            tempD.clear();
                            tempD = "D";
                            tempD += strd103;
                        }
                    }
                    else
                    {
                        error = true;
                        errorsfile << "ERROR LINE:" << line << " Undefined symbol" << sd27 << "\n";
                    }
                }
            }
            else if (opcode == "EXTREF")
            {
                // add to R record
                string sd27;
                if (tempR.length() == 0)
                    tempR = "R";
                stringstream ss102(operand);
                while (ss102 >> sd27)
                {
                    if (sd27[0] == ',')
                        sd27 = sd27.substr(1, sd27.length() - 1);
                    string strr10 = sd27;
                    for (int i = 1; i <= 6 - sd27.length(); i++)
                        strr10 += " ";
                    if (tempR.length() + 6 <= 73)
                    {
                        tempR += strr10;
                    }
                    else
                    {
                        R.push_back(tempR);
                        tempR.clear();
                        tempR = "R";
                        tempR += strr10;
                    }
                }
            }
            else if (opcode == "BASE")
            {
                stringstream ss102(operand);
                ss102 >> operand;
                if (CSECT[csect_name].SYM_TAB[operand].exists)
                    CSECT[csect_name].base = operand;
                else
                {
                    error = true;
                    errorsfile << "ERROR LINE:" << line << " undefined symbol " << operand << endl;
                }
            }
            else if (opcode == "NOBASE")
            {
                // stop base usage
                CSECT[csect_name].base = "";
            }
            else
            {
                error = true;
                errorsfile << "ERROR LINE:" << line << " INVALID OPERATION CODE\n";
            }
        }
        if (label.length() > 6)
        {
            error = true;
            errorsfile << "ERROR LINE:" << line << " used " << label << " with length more than 6\n";
        }
        cout << obj_code << "\n";
        LFile << obj_code << "\n";
    }
}
