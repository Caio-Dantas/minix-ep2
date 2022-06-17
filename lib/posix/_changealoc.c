#include <lib.h>
#include <unistd.h>

PUBLIC int changealoc(int strat)
{
  message m;
  m.m1_i1 = strat;

  return(_syscall(MM, CHANGEALOC, &m));
}
