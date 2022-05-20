#include <lockprioritylib.h>
#include <stdio.h>
int main(void)
{
    pid_t my_pid = 3355;
    int prio = 14;
    int r = lockpriority(my_pid, prio);
    printf("res is %d", r);
    return 0;
}