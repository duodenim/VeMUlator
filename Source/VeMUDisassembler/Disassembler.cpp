//Copyright 2016 Joseph Schulte
//Licensed under GPLv3
//See included LICENSE file for details
#include "Disassembler.h"

void Disassemble(const unsigned char * data, const unsigned int size, const bool writeFile, const std::string fileName)
{
  int pc = 0;
  while (pc < size)
  {
    
  }
}

void PrintDisassembly()
{
}

void WriteFileDisassembly()
{
}

int FetchOpcode(const unsigned char * data, const unsigned int offset, std::string & outName)
{
  return 0;
}

std::string ByteToHexOutput(unsigned char data)
{
  unsigned char highWord = (data & 0b11110000) / 16;
  unsigned char lowWord = data & 0b00001111;
  std::string out;
  out += WordToHex(highWord);
  out += WordToHex(lowWord);
  return out;
}

char WordToHex(unsigned char word)
{
  if (word < 10)
  {
    return word + 48;
  }
  else
  {
    return word + 55;
  }
}
