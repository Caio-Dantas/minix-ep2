/* ######################################################################## */
#include <lib.h>
#include <unistd.h>

int lockpriority(pid_t proc_pid, int prio)
{
    message m;

    m.m1_i1 = proc_pid;
    m.m1_i2 = prio;

    return ( _syscall(PM_PROC_NR, LOCKPRIORITY, &m) );
}
/* ######################################################################## */
