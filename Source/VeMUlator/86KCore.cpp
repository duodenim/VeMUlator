//Copyright 2016 Joseph Schulte
//Licensed under GPLv3
//See included LICENSE file for details
#include <iostream>
#include "86KCore.h"


State86K::State86K(unsigned char * inRom, unsigned char * inRamBank0, unsigned char * inRamBank1, unsigned char * inSfr)
{
  rom = inRom;
  ramBank0 = inRamBank0;
  ramBank1 = inRamBank1;
  sfr = inSfr;
  pc = 0;
  endProgram = false;
}

int State86K::RunInstruction()
{
  int cycles = 0;
  FUNCTION_TABLE[rom[pc]](*this);
  return cycles;
}

int State86K::UnImplementedInstruction()
{
  std::cout << "FATAL ERROR: UNIMPLEMENTED INSTRUCTION\n";
  std::cout << "AT: " << pc << "\n";
  std::cout << "WITH CODE: " << ByteToHexOutput(rom[pc]);

  endProgram = true;

  return 0;
}

int State86K::JMP()
{
  unsigned int newAddress;
  int cycles = 0;
  if (rom[pc] == 0x21) //16-bit address
  {
    newAddress = rom[pc + 2];
    newAddress += rom[pc + 1] * 256;
    pc = newAddress;
    cycles = 2;
  }
  else //12-bit address
  {
    //TODO - 12-bit address JUMP
    UnImplementedInstruction();
  }
  return cycles;
}
