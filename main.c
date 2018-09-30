#include <stdio.h>

#include "include/cthread.h"
#include "include/support.h"

void *f3(){

    puts("ola");
}

int main (void)
{
    int id = ccreate(f3, NULL, 0);

    return 0;


}
