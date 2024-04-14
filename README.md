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




