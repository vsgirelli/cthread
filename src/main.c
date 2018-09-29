#include <stdio.h>

#include "../include/support.h"
#include "../include/cthread.h"

void *f3(){
    int d = cyield();
    puts("Thread3 imprimindo");
}

void *f2(){
    puts("Thread2 imprimindo");
    int i = cyield();
}

void *f1(){
    puts("Thread3 imprimindo");

}

int main (void)
{
    int size = 100;
    char name[size];
    cidentify(name, size);

    //puts(name);

    int id = ccreate(f3, NULL, 2);
    int id2 = ccreate(f2, NULL, 2);
    int d = cyield();
    int f = cyield();
    puts("nao preempta");


    //int return_value = cyield();


    //int id3 = ccreate(f1, NULL, 1);
    printf("Main saindo...");
}
