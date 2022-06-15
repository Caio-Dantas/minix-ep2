#include <unistd.h>
#include <stdio.h>

int main(void) 
{
    int r;
    r = changealoc(RANDOM_FIT);
    printf("Aloc strat is %d\n", r);
    return 0;
}

