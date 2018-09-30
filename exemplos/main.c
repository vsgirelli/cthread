#include <stdio.h>

//#include "../include/support.h"
#include "../include/cthread.h"
csem_t semaphore1;

void *f3(){
    puts("Thread3 imprimindo");
}

void *f2(){
    puts("Thread2 before cwait");
    int cid = cwait(&semaphore1);
    puts("Thread2 after wait");
}

void *f1(){
    puts("Thread1 imprimindo");
    csignal(&semaphore1);
}

int main (void)
{
    int size = 100;
    char name[size];
    cidentify(name, size);
    //puts(name);
    int sid = csem_init(&semaphore1, 0);

    //int tid = ccreate(f3, NULL, 2);
    int tid2 = ccreate(f2, NULL, 2);
    int tid3 = ccreate(f1, NULL, 2);


    cyield();


    puts("Yeah boooy");




    puts("nao preempta");


    //int return_value = cyield();


    //int id3 = ccreate(f1, NULL, 1);
    printf("Main saindo...");
}
