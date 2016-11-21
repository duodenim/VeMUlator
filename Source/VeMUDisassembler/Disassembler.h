//Copyright 2016 Joseph Schulte
//Licensed under GPLv3
//See included LICENSE file for details

#include <string>
#include <vector>
const std::vector<std::string> OPCODE_LIST =
{
  "NOP", "BRANCH r8", "LOAD d9", "LOAD d9", "LOAD Indirect", "LOAD Indirect", "LOAD Indirect", "LOAD Indirect",
  "CALL a12", "CALL a12", "CALL a12", "CALL a12", "CALL a12", "CALL a12", "CALL a12", "CALL a12",
  "CALL r16", "BRANCH r16", "STORE d9", "STORE d9", "STORE Indirect", "STORE Indirect", "STORE Indirect", "STORE Indirect",
  "CALL a12", "CALL a12", "CALL a12", "CALL a12", "CALL a12", "CALL a12", "CALL a12", "CALL a12",
  "CALL a16", "JMP a16", "MOV i8, d9", "MOV i8, d9", "MOV i8, Indirect", "MOV i8, Indirect", "MOV i8, Indirect", "MOV i8, Indirect",
  "JMP a12", "JMP a12", "JMP a12", "JMP a12", "JMP a12", "JMP a12", "JMP a12", "JMP a12",
  "MUL", "BRANCH EQUAL i8, r8", "BRANCH EQUAL d9, r8", "BRANCH EQUAL d9, r8", "BRANCH EQUAL Indirect, i8, r8", "BRANCH EQUAL Indirect, i8, r8", "BRANCH EQUAL Indirect, i8, r8", "BRANCH EQUAL Indirect, i8, r8",
  "JMP a12", "JMP a12", "JMP a12", "JMP a12", "JMP a12", "JMP a12", "JMP a12", "JMP a12",
  "DIV", "BRANCH NOT EQUAL i8, r8", "BRANCH NOT EQUAL d9, r8", "BRANCH NOT EQUAL d9, r8", "BRANCH NOT EQUAL Indirect, i8, r8", "BRANCH NOT EQUAL Indirect, i8, r8", "BRANCH NOT EQUAL Indirect, i8, r8", "BRANCH NOT EQUAL Indirect, i8, r8",
  "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8",
  "NOT USED", "NOT USED", "DECREMENT BRANCH NOT ZERO d9, r8", "DECREMENT BRANCH NOT ZERO d9, r8", "DECREMENT BRANCH NOT ZERO Indirect, r8", "DECREMENT BRANCH NOT ZERO Indirect, r8", "DECREMENT BRANCH NOT ZERO Indirect, r8", "DECREMENT BRANCH NOT ZERO Indirect, r8",
  "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8", "BIT SET BRANCH AND CLEAR d9, b3, r8",
  "PUSH d9", "PUSH d9", "INC d9", "INC d9", "INC Indirect", "INC Indirect", "INC Indirect", "INC Indirect",
  "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8",
  "POP d9", "POP d9", "DEC d9", "DEC d9", "DEC Indirect", "DEC Indirect", "DEC Indirect", "DEC Indirect",
  "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8", "BIT SET BRANCH d9, b3, r8",
  "BRANCH ZERO r8", "ADD i8", "ADD d9", "ADD d9", "ADD Indirect", "ADD Indirect", "ADD Indirect", "ADD Indirect",
  "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8",
  "BRANCH NOT ZERO r8", "ADD W/ CARRY i8", "ADD W/ CARRY d9", "ADD W/ CARRY d9", "ADD W/ CARRY Indirect", "ADD W/ CARRY Indirect", "ADD W/ CARRY Indirect", "ADD W/ CARRY Indirect",
  "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8", "BIT NOT SET BRANCH d9, b3, r8",
  "RET", "SUB i8", "SUB d9", "SUB d9", "SUB Indirect", "SUB Indirect", "SUB Indirect", "SUB Indirect",
  "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3",
  "RET INTERRUPT", "SUB CARRY i8", "SUB CARRY d9", "SUB CARRY d9", "SUB CARRY Indirect", "SUB CARRY Indirect", "SUB CARRY Indirect", "SUB CARRY Indirect",
  "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3", "NOT BIT d9, b3",
  "ROTATE RIGHT", "LOAD CONSTANT", "EXCHANGE d9", "EXCHANGE d9", "EXCHANGE Indirect", "EXCHANGE Indirect", "EXCHANGE Indirect", "EXCHANGE Indirect",
  "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3",
  "ROTATE RIGHT W/ CARRY", "OR i8", "OR d9", "OR d9", "OR Indirect", "OR Indirect", "OR Indirect", "OR Indirect",
  "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3", "CLR BIT d9, b3",
  "ROTATE LEFT", "AND i8", "AND d9", "AND d9", "AND Indirect", "AND Indirect", "AND Indirect", "AND Indirect",
  "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3",
  "ROTATE LEFT W/ CARRY", "XOR i8", "XOR d9", "XOR d9", "XOR Indirect", "XOR Indirect", "XOR Indirect", "XOR Indirect",
  "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3", "SET BIT d9, b3"
};
//Loops through an entire byte array of size length and outputs to a file if writeFile is true, otherwise outputs to the console
void Disassemble(const unsigned char* data, const unsigned int size, const bool writeFile = false, const std::string fileName = "");

void PrintDisassembly();

void WriteFileDisassembly();

//Fetches a human readable opcode name for the instruction blocked pointed to by data at location offset
//Returns the length of the opcode
int FetchOpcode(const unsigned char* data, const unsigned int offset, std::string& outName);

//Converts a byte to its representation as a hexadecimal string
//i.e. if data = 255, then this function returns "FF"
std::string ByteToHexOutput(unsigned char data);

//Converts a single 4 byte word to its hex representation
char WordToHex(unsigned char word);