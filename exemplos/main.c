#include <stdio.h>

//#include "../include/support.h"
#include "../include/cthread.h"
csem_t semaphore1;

int tid2;

void *f1(){
    puts("Thread1 before cjoin");
    int err = cjoin(tid2);
    printf("err: %d\n", err);
    puts("Thread1 after cjoin");
}

void *f2(){
  puts("Thread2 imprimindo antes de cyield");
  int tid1 = ccreate(f1, NULL, 1);
  cyield();
  puts("Thread2 imprimindo depois de cyield");
}

void *f3(){
    puts("Thread3 imprimindo");
    tid2 = ccreate(f2, NULL, 1);
    puts("td3 depois de criar td2");
    cjoin(tid2);
    puts("td3 depois de join td2");
}


int main (void)
{
    int size = 100;
    char name[size];
    cidentify(name, size);
    //puts(name);
    //int sid = csem_init(&semaphore1, 0);

    int tid3 = ccreate(f3, NULL, 0);
    puts("liberouuu \n");
    //int tid1 = ccreate(f1, NULL, 0);


    //cyield();


    puts("Yeah boooy");




    puts("nao preempta");


    //int return_value = cyield();


    //int id3 = ccreate(f1, NULL, 1);
    printf("Main saindo...");
}
