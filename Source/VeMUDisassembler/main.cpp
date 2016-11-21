//Copyright 2016 Joseph Schulte
//Licensed under GPLv3
//See included LICENSE file for details

#include <iostream>
#include <string>
#include <fstream>
#include "Disassembler.h"
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

  unsigned char *program = new unsigned char[fsize];
  file.read((char*)program, fsize);
  file.close();

  Disassemble(program, fsize, MakeFileName(fileName));
  delete program;

}