//Copyright 2016 Joseph Schulte
//Licensed under GPLv3
//See included LICENSE file for details
#ifndef CORE_86K
#define CORE_86K
#include <vector>
#include <functional>
#include "MemoryMap.h"
#include "..\VeMUDisassembler\Disassembler.h"
class State86K
{
public:
  //Set to true to end emulation loop
  bool endProgram;

  State86K(unsigned char *inRom, unsigned char *inRamBank0, unsigned char *inRamBank1, unsigned char *inSfr);

  void Init();
  int RunInstruction();
protected:
  std::vector < std::function<int(State86K&)>> FUNCTION_TABLE = 
  {
    &State86K::NOP, &State86K::BRANCH, &State86K::LOAD, &State86K::LOAD,
    &State86K::LOAD, &State86K::LOAD, &State86K::LOAD, &State86K::LOAD,
    &State86K::CALL, &State86K::CALL, &State86K::CALL, &State86K::CALL,
    &State86K::CALL, &State86K::CALL, &State86K::CALL, &State86K::CALL,
    &State86K::CALL, &State86K::BRANCH, &State86K::STORE, &State86K::STORE,
    &State86K::STORE, &State86K::STORE, &State86K::STORE, &State86K::STORE,
    &State86K::CALL, &State86K::CALL, &State86K::CALL, &State86K::CALL,
    &State86K::CALL, &State86K::CALL, &State86K::CALL, &State86K::CALL,
    &State86K::CALL, &State86K::JMP, &State86K::MOV, &State86K::MOV,
    &State86K::MOV, &State86K::MOV, &State86K::MOV, &State86K::MOV,
    &State86K::JMP, &State86K::JMP, &State86K::JMP, &State86K::JMP,
    &State86K::JMP, &State86K::JMP, &State86K::JMP, &State86K::JMP,
    &State86K::MUL, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::JMP, &State86K::JMP, &State86K::JMP, &State86K::JMP,
    &State86K::JMP, &State86K::JMP, &State86K::JMP, &State86K::JMP,
    &State86K::DIV, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::NOP, &State86K::NOP, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::PUSH, &State86K::PUSH, &State86K::INC, &State86K::INC,
    &State86K::INC, &State86K::INC, &State86K::INC, &State86K::INC,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::POP, &State86K::POP, &State86K::DEC, &State86K::DEC,
    &State86K::DEC, &State86K::DEC, &State86K::DEC, &State86K::DEC,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::ADD, &State86K::ADD, &State86K::ADD,
    &State86K::ADD, &State86K::ADD, &State86K::ADD, &State86K::ADD,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::ADD, &State86K::ADD, &State86K::ADD,
    &State86K::ADD, &State86K::ADD, &State86K::ADD, &State86K::ADD,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH, &State86K::BRANCH,
    &State86K::RET, &State86K::SUB, &State86K::SUB, &State86K::SUB,
    &State86K::SUB, &State86K::SUB, &State86K::SUB, &State86K::SUB,
    &State86K::NOT, &State86K::NOT, &State86K::NOT, &State86K::NOT,
    &State86K::NOT, &State86K::NOT, &State86K::NOT, &State86K::NOT,
    &State86K::RET, &State86K::SUB, &State86K::SUB, &State86K::SUB,
    &State86K::SUB, &State86K::SUB, &State86K::SUB, &State86K::SUB,
    &State86K::NOT, &State86K::NOT, &State86K::NOT, &State86K::NOT,
    &State86K::NOT, &State86K::NOT, &State86K::NOT, &State86K::NOT,
    &State86K::ROTATE, &State86K::LDC, &State86K::XCH, &State86K::XCH,
    &State86K::XCH, &State86K::XCH, &State86K::XCH, &State86K::XCH,
    &State86K::CLR, &State86K::CLR, &State86K::CLR, &State86K::CLR,
    &State86K::CLR, &State86K::CLR, &State86K::CLR, &State86K::CLR,
    &State86K::ROTATE, &State86K::OR, &State86K::OR, &State86K::OR,
    &State86K::OR, &State86K::OR, &State86K::OR, &State86K::OR,
    &State86K::CLR, &State86K::CLR, &State86K::CLR, &State86K::CLR,
    &State86K::CLR, &State86K::CLR, &State86K::CLR, &State86K::CLR,
    &State86K::ROTATE, &State86K::AND, &State86K::AND, &State86K::AND,
    &State86K::AND, &State86K::AND, &State86K::AND, &State86K::AND,
    &State86K::SET, &State86K::SET, &State86K::SET, &State86K::SET,
    &State86K::SET, &State86K::SET, &State86K::SET, &State86K::SET,
    &State86K::ROTATE, &State86K::XOR, &State86K::XOR, &State86K::XOR,
    &State86K::XOR, &State86K::XOR, &State86K::XOR, &State86K::XOR,
    &State86K::SET, &State86K::SET, &State86K::SET, &State86K::SET,
    &State86K::SET, &State86K::SET, &State86K::SET, &State86K::SET,
  };
  unsigned int pc;
  unsigned char *rom;
  unsigned char *ramBank0;
  unsigned char *ramBank1;
  unsigned char *sfr;

  int UnImplementedInstruction();

  //Many instructions need a number composed of bits 0,1,2 and 4
  //This function returns a 4 bit word composed of these 4 bits (big endian)
  int Get4BitNumber(unsigned char data);

  //Returns a pointer to the current RAM bank as provided by the RAM_BANK flag
  //Will either be equal to ramBank0 or ramBank1
  unsigned char *GetRamBank();
  //-----INSTRUCTIONS-----//
  int ADD();
  int AND();
  int BRANCH();
  int CALL();
  int CLR();
  int DEC();
  int DIV();
  int INC();
  int JMP();
  int LDC();
  int LOAD();
  int MOV();
  int MUL();
  int NOP();
  int NOT();
  int OR();
  int POP();
  int PUSH();
  int RET();
  int ROTATE();
  int SET();
  int STORE();
  int SUB();
  int XCH();
  int XOR();

};

#endif