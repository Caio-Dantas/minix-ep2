#include "syslib.h"

/*===========================================================================*
 *                                sys_nice			     	     *
 *===========================================================================*/
PUBLIC int sys_nice(int proc, int prio)
{
  message m;

  m.m1_i1 = proc;
  m.m1_i2 = prio;
/* ######################################################################## */
  m.m1_i3 = 0;
/* ######################################################################## */
  return(_taskcall(SYSTASK, SYS_NICE, &m));
}
