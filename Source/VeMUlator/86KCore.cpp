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

void State86K::Init()
{
  sfr[PSW] = 0b00000010;
  sfr[SP] = 0x80;
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
  std::cout << "AT: " << ByteToHexOutput((pc & 0xff00) >> 8) << " " 
            << ByteToHexOutput(pc & 0xff) << "\n";
  std::cout << "WITH CODE: " << ByteToHexOutput(rom[pc]);

  endProgram = true;
  
  return 0;
}

int State86K::Get4BitNumber(unsigned char data)
{
  int MSB = data & 0b00010000;
  MSB /= 2;
  int LowerBits = data & 0b00000111;

  return MSB + LowerBits;
}

unsigned char * State86K::GetRamBank()
{
  if (sfr[PSW] & RAM_BANK)
  {
    return ramBank1;
  }
  else
  {
    return ramBank0;
  }
}

int State86K::ADD()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::AND()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::BRANCH()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::CALL()
{
  //Push return address onto stack
  int retAddress = pc + 2;
  sfr[SP]++;
  ramBank0[sfr[SP]] = retAddress & 0xff;
  sfr[SP]++;
  ramBank0[sfr[SP]] = (retAddress & 0xff00) >> 8;

  //Build and assign the new address
  int oldPC = pc;
  pc &= 0xf000;
  pc += (rom[oldPC] & 0x0f) << 8;
  pc += rom[oldPC + 1];

  return 2;
}

int State86K::CLR()
{
  int bitNumber = Get4BitNumber(rom[pc]) & 0b00000111;
  if (Get4BitNumber(rom[pc]) & 0b00010000)
  {
    //SFR
    sfr[rom[pc + 1]] &= ~(1 << bitNumber);
  }
  else
  {
    //Normal RAM
    GetRamBank()[rom[pc + 1]] &= ~(1 << bitNumber);
  }

  pc += 2;
  return 1;
}

int State86K::DEC()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::DIV()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::INC()
{
  UnImplementedInstruction();
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

int State86K::LDC()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::LOAD()
{
  unsigned char data;
  if (rom[pc] == 0x02)
  {
    data = GetRamBank()[rom[pc + 1]];
    pc += 2;
  }
  else if (rom[pc] = 0x03)
  {
    data = sfr[rom[pc + 1]];
    pc += 2;
  }
  else
  {
    UnImplementedInstruction(); //Indirect
  }
  sfr[ACC] = data;
  return 1;
}

int State86K::MOV()
{
  unsigned char data;
  int cycles = 1;
  if (rom[pc] == 0x22 || rom[pc] == 0x23) //Direct from ram
  {
    data = rom[pc + 2];
    cycles = 2;
  }
  else //Indirect
  {
    UnImplementedInstruction();
  }

  if (rom[pc] == 0x22)
  {
    GetRamBank()[rom[pc + 1]] = data;
    pc += 3;
  }
  else if (rom[pc] == 0x23)
  {
    sfr[rom[pc + 1]] = data;
    pc += 3;
  }
  return cycles;
}

int State86K::MUL()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::NOP()
{
  return 0;
}

int State86K::NOT()
{
  int bitNumber = Get4BitNumber(rom[pc]) & 0b00000111;
  if (Get4BitNumber(rom[pc]) & 0b00010000)
  {
    //SFR
    sfr[rom[pc + 1]] ^= (1 << bitNumber);
  }
  else
  {
    //Normal RAM
    GetRamBank()[rom[pc + 1]] ^= (1 << bitNumber);
  }

  pc += 2;
  return 1;
  return 0;
}

int State86K::OR()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::POP()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::PUSH()
{
  int address = (rom[pc] & 0b1) << 8;
  address += rom[pc + 1];

  sfr[SP]++;
  ramBank0[sfr[SP]] = GetRamBank()[address];
  pc += 2;
  return 2;
}

int State86K::RET()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::ROTATE()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::SET()
{
  int bitNumber = Get4BitNumber(rom[pc]) & 0b00000111;
  if (Get4BitNumber(rom[pc]) & 0b00010000)
  {
    //SFR
    sfr[rom[pc + 1]] |= (1 << bitNumber);
  }
  else
  {
    //Normal RAM
    GetRamBank()[rom[pc + 1]] |= (1 << bitNumber);
  }

  pc += 2;
  return 1;
}

int State86K::STORE()
{
  if (rom[pc] == 0x12 || rom[pc] == 0x13)
  {
    //Direct
    int address = rom[pc + 1];
    address += (rom[pc] & 0b1) << 8;
    GetRamBank()[address] = sfr[ACC];
    pc += 2;
  }
  else
  {
    //Indirect
    UnImplementedInstruction();
  }
  return 1;
}

int State86K::SUB()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::XCH()
{
  UnImplementedInstruction();
  return 0;
}

int State86K::XOR()
{
  int address;
  switch (rom[pc]) 
  {
  case 0xF1: //Immediate
    sfr[ACC] = rom[pc + 1] ^ sfr[ACC];
    pc += 2;
    break;
  case 0xF2: //Direct
  case 0xF3:
    address = rom[pc + 1];
    address += (rom[pc] & 0b1) << 8;
    sfr[ACC] = GetRamBank()[address] ^ sfr[ACC];
    pc += 2;
    break;
  case 0xF4: //Indirect
  case 0xF5:
  case 0xF6:
  case 0xF7:
    UnImplementedInstruction();
    break;

  default:
    UnImplementedInstruction();
  }
  return 1;
}
