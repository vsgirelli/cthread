#include <stdio.h>

#include "../include/support.h"
#include "../include/cthread.h"

void *f3(){

    puts("Thread1 imprimindo");
}

int main (void)
{
    int id = ccreate(f3, NULL, 1);

    printf("Main saindo...");
}
