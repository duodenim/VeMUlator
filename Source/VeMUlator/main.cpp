//Copyright 2016 Joseph Schulte
//Licensed under GPLv3
//See included LICENSE file for details

#include <iostream>
#include <string>
#include <fstream>
#include "../VeMUDisassembler/Disassembler.h"
#include "MemoryMap.h"
#include "86KCore.h"
int main(int argc, char *argv[])
{
  std::string fileName;
  std::cout << "Please enter a .VMS game file to open\n";
  std::cin >> fileName;

  std::fstream file(fileName, std::fstream::binary | std::fstream::in);
  if (file.fail())
  {
    std::cout << "File Error";
    exit(1);
  }
  file.seekg(0, std::ios_base::end);
  long fsize = file.tellg();
  file.seekg(0, std::ios_base::beg);

  unsigned char *rom = new unsigned char[ROM_SIZE];
  unsigned char *ram0 = new unsigned char[RAM0_SIZE];
  unsigned char *ram1 = new unsigned char[RAM1_SIZE];
  unsigned char *sfr = new unsigned char[SFR_SIZE];

  file.read((char*)rom, fsize);
  file.close();

  State86K *cpu = new State86K(rom, ram0, ram1, sfr);
  cpu->Init();
  while (!cpu->endProgram)
  {
    cpu->RunInstruction();
  }


  delete[] rom;
  delete[] ram0;
  delete[] ram1;
  delete[] sfr;

  //Wait for input to end program
  std::cin >> fileName;
}