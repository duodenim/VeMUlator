//Copyright 2016 Joseph Schulte
//Licensed under GPLv3
//See included LICENSE file for details
#ifndef MEMORY_MAP
#define MEMORY_MAP

/*
4 Blocks of Memory:

  65536 byte ROM space
  
  RAM: (512 byte total)
    Low 256 byte area mapped to two banks controlled by PSW bit 1
    Bank 0: System Variables / CPU Stack
    Bank 1: General Purpose RAM (Initially mapped to this)

    High 256 byte area mapped to Special Function Registers (SFR)
*/
const int ROM_SIZE = 65536;
const int RAM0_SIZE = 256;
const int RAM1_SIZE = 256;
const int SFR_SIZE = 256;

//Listing of addresses of relevant special function
//registers
enum SFR
{
  ACC = 0x000,
  PSW = 0x001,
  B = 0x002,
  C = 0x003,
  TRL = 0x004,
  TRH = 0x005,
  SP = 0x006,
  XRAM_Start = 0x080,
  XRAM_End = 0x0fb
};

enum SysVar
{
  Stack_Start = 0x80,
  Stack_End = 0xff
};

//AND the PSW with these to get the specific flag
enum PSW_Bits
{
  CARRY = 0b10000000,
  AUX_CARRY = 0b01000000,
  INDIRECT_BANK1 = 0b00010000,
  INDIRECT_BANK0 = 0b00001000,
  OVER_FLOW = 0b00000100,
  RAM_BANK = 0b00000010,
  PARITY = 0b00000001
};
#endif // !MEMORY_MAP