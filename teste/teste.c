#include <stdio.h>
#include "../include/cthread.h"

void *th2(void) {
		printf ("thread de mais alta prio\n");

		cyield();
	return NULL;
}

void *th1(void) {
  int id2 = ccreate(th2, NULL, 2);
  printf("thread de alta prio fez cyield\n");

  if (cjoin(id2)<0) {
    printf ("Erro no cjoin(th2).\n");
  }
  printf("thread de alta prio liberou\n");
  cyield();

  return NULL;
}

int main(int argc, char *argv[]) {
  int id1;
	if ( (id1=ccreate(th1, NULL, 1))<0) {
		printf ("Erro no ccreate(th1, , 1)\n");
	}
  else {
		if (cjoin(id1)<0) {
			printf ("Erro no cjoin(th1).\n");
		}
    else {
			cyield();
		}
	}
	printf ("Fim do main\n");
	return 0;
}


