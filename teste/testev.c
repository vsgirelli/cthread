#include <stdio.h>
#include "../include/cthread.h"

int tid[20];
int tid2[20];
int itid = 0;

void *th2(void) {
  int cont=100;

  while(cont) {
    printf ("%d",itid);
    --cont;
  }
}

void *th(void *param) {
  int cont=100;


 // while(cont) {
   // printf ("%d\n",param);
    //--cont;

    //cyield();
  //}

  return NULL;
}

int main(int argc, char *argv[]) {
  int delay=100;
  char name[256];

  cidentify (name, 255);
  printf ("GRUPO: %s\n\n", name);

  int i;
  for (i = 0; i < 20; i++) {
    tid[i] = ccreate(th, (void*)i, 1);
    printf("tid: %d\n", tid[i]);
  }

  while(--delay) {
    printf ("0");
    cyield();
  }

  printf ("Fim do main\n");
  return 0;
}





