#include <stdio.h>
#include "../include/cthread.h"

int tid[20];
int tid2[20];
int itid = 0;

void *th2(void) {
  printf("filha de maior prio\n");
}

void *th(void *param) {
  int cont=100;

  printf("thread %d executando\n", (void*)param);

  tid2[itid] = ccreate(th2, NULL, 2);
  itid++;
  printf("thread %d executando depois do retorno da filha\n", (void*)param);

  return NULL;
}

int main(int argc, char *argv[]) {
  int delay=100;
  char name[256];

  cidentify (name, 255);
  printf ("GRUPO: %s\n\n", name);

  int i;
  for (i = 0; i < 10; i++) {
    tid[i] = ccreate(th, (void*)i+1, 2);
    //printf("tid: %d\n", tid[i]);
  }

  int err = cjoin(tid[0]);
  printf("err: %d\n", err);
  err = cjoin(tid2[5]);
  printf("err: %d\n", err);
  //cyield();


  printf ("Fim do main\n");
  return 0;
}





