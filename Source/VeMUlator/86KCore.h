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

  int RunInstruction();
protected:
  std::vector < std::function<int(State86K&)>> FUNCTION_TABLE = 
  {
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::JMP, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
    &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction, &State86K::UnImplementedInstruction,
  };
  unsigned int pc;
  unsigned char *rom;
  unsigned char *ramBank0;
  unsigned char *ramBank1;
  unsigned char *sfr;

  int UnImplementedInstruction();

  int JMP();
};

#endif