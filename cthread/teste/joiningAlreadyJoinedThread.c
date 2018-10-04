#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>


void* ShowsString(void *arg){
    char* argument = (char *) arg;
    printf("%s\n", argument);
    if(cyield() == -1) printf("readyQueue is empty\n");
    printf("Returning to ShowsString\n");
    return NULL;
}

void* JoinsThread(void *tid){
    int* joinToTID = (int *)tid;
    printf("I got into JoinsThread! \n"); 
    printf("Trying to join thread TID %d\n", joinToTID);
    if(cjoin(joinToTID) == -1) printf("The thread couldn't join\n");
    return NULL;
}

int main(){
    char arg[] = "Sphinx of black quartz, judge my vow";
    
    int tid1 = ccreate(ShowsString, (void *) arg, 0);
    int tid2 = ccreate(JoinsThread, (void *) tid1, 0);

    printf("Main done creating its children\n");
    cjoin(tid1);

    return(1);
}
