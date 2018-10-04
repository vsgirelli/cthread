#include <stdio.h>
#include "../include/cthread.h"

void *th2(void *param) {
	int n=(int)param;
	int cont=50;
	while(cont) {
    printf ("***%d\n",n);
    --cont;

    cyield();
	}
	printf ("Fim da th2\n");
	return NULL;
}

int main(int argc, char *argv[]) {
	char	name[256];
	int	id2;
	
	cidentify (name, 255);
	printf ("GRUPO: %s\n\n", name);	
	
	if ( (id2=ccreate(th2, (void *)2, 2))<0) {
		printf ("Erro no ccreate\n");
	} else {
    printf("cyield ok\n");
    cyield();
		if (cjoin(id2)<0) {
			printf ("Erro no cjoin(th2).\n");
		}
	}
	printf ("Fim do main\n");
	return 0;
}


