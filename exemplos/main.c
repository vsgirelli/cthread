#include <stdio.h>
#include "../include/cthread.h"
#include "../include/support.h"
#include "../include/cutils.h"

void* f3 (void *arg)
{
    puts("Entrou F3");

}

int main (void)
{

  int id, i;

  id = ccreate(f3, NULL, 0);

  return 0;


}
