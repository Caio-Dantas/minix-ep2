/* ######################################################################## */
#include <lib.h>
#include <unistd.h>

int lockpriority(int pid_filho, int prioridade)
{
    message m;

    m.m1_i1 = pid_filho;
    m.m1_i2 = prioridade;

    return ( _syscall(PM_PROC_NR, LOCKPRIORITY, &m) );
}
/* ######################################################################## */
