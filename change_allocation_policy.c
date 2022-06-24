#include <unistd.h>
#include <stdio.h>

int main(void) 
{
    int r;
    r = changealoc(NEXT_FIT);
    printf("Aloc strat is %d\n", r);
    return 0;
}

