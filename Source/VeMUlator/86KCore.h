//Copyright 2016 Joseph Schulte
//Licensed under GPLv3
//See included LICENSE file for details
#ifndef CORE_86K
#define CORE_86K

#include "MemoryMap.h"
class State86K
{
protected:
  unsigned int pc;
  unsigned char *rom;
  unsigned char *ramBank0;
  unsigned char *ramBank1;
  unsigned char *sfr;
};

#endif