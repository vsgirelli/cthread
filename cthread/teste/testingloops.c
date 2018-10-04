#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>

void LoopThread()
{
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("T %d\n", i);
        cyield();
    }
}

int main()
{
    int i;

    ccreate(LoopThread, NULL, 2);
    cyield();
    
    for(i = 0; i < 10; i++)
    {
        printf("M %d\n", i);
        cyield();
    }
    return(1);
}
