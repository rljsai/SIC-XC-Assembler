# SIC-XC-Assembler
The assembler for the SIC/XE machine is implemented in C++ language and operates
on a two-pass logic. This report details the functionality and processes involved
in both passes.
The following features are implemented in this assembler:
1. Expressions
2. Literals
3. Symbol Defining Statements
4. Control section<br>
<P>This project implements an assembler that supports SIC/XE instructions. The
assembler includes all the instructions. It supports Control Sections.<br>
The instruction formats supported by SIC/XE :

![Screenshot from 2024-04-11 21-01-40](https://github.com/rljsai/SIC-XC-Assembler/assets/146453283/0a11e27f-d509-4ebe-a1ec-4fea88f1d6a0)

The Addressing modes supported by the Assembler are:

![Screenshot from 2024-04-11 21-01-54](https://github.com/rljsai/SIC-XC-Assembler/assets/146453283/37c39ce6-7b55-4d5d-adb2-a9f66d17bca0)

## Working of Assembler
### PASS1:
* In the initial pass, the assembler assigns addresses to symbols and instructions.
* Symbols, literals, and external references are stored in their respective tables.
* Processing for expressions and EQU statements is conducted.
* Errors are flagged for forward references in EQU expressions and for invalid opcodes or assembler directives.

### PASS2:
* The second pass focuses on the assembly of instructions.
* It reads input from the intermediate file and corresponding tables.
* Error messages are generated if discrepancies are found.
* The assembler creates a listing file and object program based on the assembled instructions.


## Instructions to Use the Assembler:
### clone the repository
```
  git clone https://github.com/rljsai/SIC-XC-Assembler.git
```
### contains several files each descriptions are given below
* sic-assemblermain.cpp --> To run Assembler
* sic-assembler-passes.cpp --> contains the code for PASS 1 & 2 and data structures and functions used
* input.txt --> The code for assembly is to be written into this file
* organising.txt --> contains assembly program in an organising way
* Intermediatefile.txt --> contains instructions and it’s address assigned after PASS 1
* errors.txt --> contains errors in PASS 1 &2 if any
* tables.txt --> contains symbol tables and literal tables
* listingfile.txt --> contains assembled instructions
* objectcode.txt --> contains object program

### Input example (input.txt):
![Screenshot from 2024-05-06 10-48-42](https://github.com/rljsai/SIC-XC-Assembler/assets/146453283/95b9224e-5c58-4c44-9563-f89a75ff3d54)

### Organizing.txt:
![Screenshot from 2024-05-06 10-50-12](https://github.com/rljsai/SIC-XC-Assembler/assets/146453283/cd999051-13bb-46c2-9bce-4d60fe536631)

### intermediatefile.txt:
![image](https://github.com/rljsai/SIC-XC-Assembler/assets/146453283/be91ca82-8bb2-43b9-b6d8-7a532e931df9)

### Listingfile.txt:
![image](https://github.com/rljsai/SIC-XC-Assembler/assets/146453283/06767521-b6e5-4675-9be7-813566f86f7c)

### errors.txt:
![Screenshot from 2024-05-06 10-53-59](https://github.com/rljsai/SIC-XC-Assembler/assets/146453283/534f85ff-be19-4bf2-8e08-f02d1476b09c)

### tables.txt:
![image](https://github.com/rljsai/SIC-XC-Assembler/assets/146453283/f6d0e171-9538-4b1a-b2b7-7680365b2ce9)

### objectcode.txt:
![image](https://github.com/rljsai/SIC-XC-Assembler/assets/146453283/ca19a013-3ed6-4442-ace3-cacb039c0b58)








