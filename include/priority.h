#include <lib.h>

PUBLIC int lockpriority(pid_t child_process, int priority) {

    message m;

    m.m1_i1 = child_process;
    m.m1_i2 = priority;

    _syscall(MM, LOCKPRIORITY, &m);

}


PUBLIC int unlockpriority(pid_t child_process, int priority) {
    return 0;
}