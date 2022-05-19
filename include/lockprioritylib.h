#include <lib.h>
#include <unistd.h>

int lockpriority(pid_t proc_pid, int prio)
{
    message m;

    m.m1_i1 = 0;
    m.m1_i2 = proc_pid;
    m.m1_i3 = prio;

    return ( _syscall(PM_PROC_NR, LOCKPRIORITY, &m) );
}