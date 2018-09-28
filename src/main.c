#include <stdio.h>

#include "../include/support.h"
#include "../include/cthread.h"

void *f3(){

    puts("Thread1 imprimindo");
}

void *f2(){
    puts("Thread2 imprimindo");
}

void *f1(){
    puts("Thread3 imprimindo");

}

int main (void)
{
    int size = 10;
    char name[size];
    cidentify(name, size);

    //puts(name);

    int id = ccreate(f3, NULL, 0);
    puts("Main segue forte");
    int id2 = ccreate(f2, NULL, 0);

    int return_value = cyield();


    //int id3 = ccreate(f1, NULL, 1);
    printf("Main saindo...");
}
