//Copyright 2016 Joseph Schulte
//Licensed under GPLv3
//See included LICENSE file for details
#include <iostream>
#include <fstream>
#include "Disassembler.h"

void Disassemble(const unsigned char * data, const unsigned int size, const std::string fileName)
{
  std::fstream fout(fileName, std::fstream::out);
  int pc = 0;
  std::string currentOpcode;
  std::string currentLocation;
  if (!fout.fail())
  {
    while (pc < size)
    {
      currentLocation = "";
      currentLocation += ByteToHexOutput((pc & 0b1111111100000000) / 256);
      currentLocation.append(" ");
      currentLocation += ByteToHexOutput(pc & 0b11111111);
      currentLocation.append("   ");
      pc += FetchOpcode(data, pc, currentOpcode);
      fout << currentLocation << currentOpcode << "\n";
    }
  }

  fout.close();
  return;
}

int FetchOpcode(const unsigned char * data, const unsigned int offset, std::string & outName)
{
  int size = SIZE_LIST[data[offset]];
  outName = "";
  for (int i = 0; i < size; i++)
  {
    outName += ByteToHexOutput(data[offset + i]);
    outName.append(" ");
  }

  outName.append(OPCODE_LIST[data[offset]]);
  
  return size;
}

std::string MakeFileName(std::string inputFileName)
{
  std::string output = inputFileName;
  int extLocation = output.find_last_of('.');
  
  output.erase(extLocation);
  //Add "DISASSEMBLY"
  output.append("DISASSEMBLY");
  
  //Replace file extension
  output.append(".txt");

  return output;
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
