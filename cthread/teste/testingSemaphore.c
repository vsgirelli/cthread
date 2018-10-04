#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>

csem_t semaphore;

void* th()
{
    cwait(&semaphore);
    printf("and this should appear after that!\n");
    csignal(&semaphore);
    return NULL;
}

void* th2()
{
    cwait(&semaphore);
    printf("This will be the last one!\n");
    csignal(&semaphore);
    return NULL;
}

int main()
{
    int err = csem_init(&semaphore, 1);
    //printf("err %d\n", err);
    cwait(&semaphore);
    ccreate(th, NULL, 0);
    ccreate(th2, NULL, 0);
    cyield();

    printf("This should appear first\n");
    csignal(&semaphore);
    printf("olar\n");
    cyield();
    cyield();

    return 0;
}
