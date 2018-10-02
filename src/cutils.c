/*
 *  Source com as funções utilizadas pela cthread para gerenciar o
 *  escalonamento das threads a nível de usuário.
 */
#include "../include/support.h"
#include "../include/cdata.h"
#include "../include/config.h"
#include "../include/cutils.h"
#include "../include/config.h"
#include "../include/cdata.h"
#include "../include/support.h"
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <string.h>

int numTID = 0;
int mainThreadInitialized = 0;
int yielding_tid = -1;

// procurar thread em uma determinada lista
// se encontrou retorna 0
// caso contrario, retorna THREAD_NOT_FOUND
int searchThread(PFILA2 queue, int tid){
	TCB_t *pThread;
	FirstFila2(queue);			
	pThread = (TCB_t*) GetAtIteratorFila2(queue);
	while(pThread != NULL){
		if(pThread->tid == tid){
			// found thread and return
			return 0;
		} else{
			// otherwise, keep searching
			NextFila2(queue);
			pThread = (TCB_t*) GetAtIteratorFila2(queue);
		}
	}
	return THREAD_NOT_FOUND;		
}

// verifica se a thread ja esta bloqueando alguem
// se nao bloqueia ninguem retorna 0 
// caso contrario, THREAD_ALREADY_BLOCKING
int checkThreadBlocking(PFILA2 queue, int tid){
	cjoin_thread *pCjoin_thread;
	FirstFila2(queue);
	pCjoin_thread = (cjoin_thread*) GetAtIteratorFila2(queue);
	while(pCjoin_thread != NULL){
		if(pCjoin_thread->blockingTID == tid){			
			return THREAD_ALREADY_BLOCKING;
		} else{	
			NextFila2(queue);
			pCjoin_thread = (cjoin_thread*) GetAtIteratorFila2(queue);
		}	
	}
	return 0;
}

// verifica se eh possivel bloquear a thread referenciada por esse tid
// 0 se eh possivel
// caso contrario, erro:
//  THREAD_ALREADY_BLOCKING
//  THREAD_NOT_FOUND
int canBlock(int tid) {
    // primeiro procura pela thread na lista de cjoinQueue
    // se já ta em cjoinQueue, retrna THREAD_ALREADY_BLOCKING    
    if(checkThreadBlocking(&cjoinQueue, tid) != 0)
        return THREAD_ALREADY_BLOCKING;
    // senão, procura nas demais listas
    if(searchThread(&readyQueuePrio0, tid) == 0)
        return 0;
    if(searchThread(&readyQueuePrio1, tid) == 0)
        return 0;
    if(searchThread(&readyQueuePrio2, tid) == 0)
        return 0;
    if(searchThread(&blockedQueue, tid) == 0)
        return 0;
    return THREAD_NOT_FOUND;
}


// verificar se a mainThread já existe
int checkMainThread()
{
    if(mainThreadInitialized == 0)
    {
        return 1;
    }
    return 0;
}

TCB_t* createThread(void* (*start)(void*), void *arg, int prio, int tid)
{
    TCB_t * newThread = (TCB_t*) malloc(sizeof(TCB_t)) ;

    /**
        Criacao do contexto
    */
    getcontext(&newThread->context);
    newThread->context.uc_stack.ss_sp = (char *) malloc (SIGSTKSZ);
    newThread->context.uc_stack.ss_size = SIGSTKSZ;
    newThread->context.uc_link = &terminateContext;
    makecontext(&(newThread->context), (void (*)(void)) start, 1, arg);

    /**
        Definicao dos atributos do TCB
    */
    newThread->tid = tid;
    newThread->state = PROCST_APTO;
    newThread->prio = prio;
    newThread->data = NULL;

    return newThread;
}

PFILA2 getThreadReadyPrioQueue( TCB_t * thread)
{
    if (thread->prio == 0 )
    {
        return &readyQueuePrio0;
    }
    if (thread->prio == 1)
    {
        return &readyQueuePrio1;
    }
    if (thread->prio == 2)
    {
        return &readyQueuePrio2;
    }
    return NULL;
}

int createTID()
{
    return ++numTID;

}

// AppendFila2(blockedQueue, runningThread) (ou
// salva na fila de aptos a thread que vai ser preemptada
int moveRunningToBlocked()
{
    TCB_t* blockedThread = runningThread;

    blockedThread->state = PROCST_BLOQ;

    if(AppendFila2(&blockedQueue, (void*)blockedThread) != 0)
    {
        return -1;
    }
    return FUNC_WORKING;
}

int moveBlockToReady(int tid)
{
    // pega a thread bloqueada
    TCB_t* thread = getThreadAndDelete(&blockedQueue, tid);

    thread->state = PROCST_APTO;

    PFILA2 FilaCorrespondente = getThreadReadyPrioQueue(thread);

    AppendFila2(FilaCorrespondente, thread);

    return FUNC_WORKING;
}


int moveRunningToCjoin()
{
    //AppendFila2(&cjoinQueue, runningThread);
    return FUNC_NOT_IMPLEMENTED;
}

/**
    Dada uma thread recém criada, move-a para a lista de acordo com sua prioridade
*/
int moveCreatedToList(TCB_t* newThread)
{

    PFILA2 filaCorrespondente = getThreadReadyPrioQueue(newThread);

    if ( AppendFila2(filaCorrespondente, newThread) )
    {
        return FUNC_NOT_WORKING;
    }

    return FUNC_WORKING;

}

// Salva na fila de aptos a thread que vai ser preemptada
int moveRunningToReady()
{
    runningThread->state = PROCST_APTO;

    PFILA2 FilaCorrespondente = getThreadReadyPrioQueue(runningThread);

    if ( AppendFila2(FilaCorrespondente, runningThread) )
    {
        return FUNC_NOT_WORKING;
    }

    runningThread = NULL;
    return FUNC_WORKING;
}

/**
    Retorna 0 quando existe uma fila com a prioridade maior que contenha threads em apto.
*/
int existsHigherPrioThread(int prio)
{
    if (prio == 0)
    {
        return -1;
    }
    else
    {
        if (prio == 1)
        {
            return FirstFila2(&readyQueuePrio0);
        }
        if (prio == 2)
        {
            return (FirstFila2(&readyQueuePrio0) && FirstFila2(&readyQueuePrio1));
        }
    }
    return -1;
}

// setContext(runningThread->context)
// seta o contexto atual pro contexto da nova thread
void scheduler()
{
    // Caso a thread com prio2 nao tenha acabado de fazer um yield e haja thread com prio2
    if (FirstFila2(&readyQueuePrio0) == 0 )
    {
        runningThread = (TCB_t *) GetAtIteratorFila2(&readyQueuePrio0);
        DeleteAtIteratorFila2(&readyQueuePrio0);
        setcontext(&(runningThread->context));
    }
    else if (FirstFila2(&readyQueuePrio1) == 0 )
    {
        runningThread = (TCB_t *) GetAtIteratorFila2(&readyQueuePrio1);
        DeleteAtIteratorFila2(&readyQueuePrio1);
        setcontext(&(runningThread->context));
    }
    else if (FirstFila2(&readyQueuePrio2) == 0 )
    {
        runningThread = (TCB_t *) GetAtIteratorFila2(&readyQueuePrio2);
        DeleteAtIteratorFila2(&readyQueuePrio2);
        setcontext(&(runningThread->context));
    }
}

/*
 *  Verifica se a thread que terminou est� bloqueando alguma thread.
 *  Caso esteja, liberar a thread bloqueada.
 */
void checkIfBlocking() {
  cjoin_thread *cjt; 
  FirstFila2(&cjoinQueue);
  cjt = (cjoin_thread*) GetAtIteratorFila2(&cjoinQueue);

  while (cjt != NULL) {
    // se o algum blockingTID for igual ao tid da thead em execu��o
    if (cjt->blockingTID == runningThread->tid) {
      // ent�o procurar em blockedQueue pela thread de tid blockedTID
      // e mover esta para a fila de apto correspondente
      moveBlockToReady(cjt->blockedTID);
      DeleteAtIteratorFila2(&cjoinQueue); 
      return;
    }
    else {  
      NextFila2(&cjoinQueue);
      cjt = (cjoin_thread*) GetAtIteratorFila2(&cjoinQueue);
    }
  }
}

/*
 * todas as thread devem ser ligadas a essa função.
 * quando a thread terminar, linkar ao uc_link dela essa função
 * pra liberar recursos e o tcb, e posteriormente chamar o escalonador.
 * Tem que verificar se a thread terminada bloqueava alguém.
 */
void terminateThread()
{
    checkIfBlocking();

    free(runningThread->context.uc_stack.ss_sp);
    free(runningThread);

    runningThread = NULL;

    scheduler();

    return;
}


int isEmptyQueues()
{
    return FirstFila2(&readyQueuePrio0) && FirstFila2(&readyQueuePrio1) && FirstFila2(&readyQueuePrio2);
}

// cria main
// inicializar as filas (support.h)
// cria contexto pra chamada da terminateThread
int initialCreate()
{
    mainThreadInitialized = 1;
    /**
        Criacao das filas
    */
    CreateFila2(&readyQueuePrio0);
    CreateFila2(&readyQueuePrio1);
    CreateFila2(&readyQueuePrio2);

    CreateFila2(&blockedQueue);
    CreateFila2(&suspendedReadyQueue);
    CreateFila2(&suspendedBlockedQueue);

    CreateFila2(&cjoinQueue);

    /** Criacao da mainThread
    */
    mainThread = (TCB_t*) malloc(sizeof(TCB_t)) ;

    //mainThread->tid = (int) MAIN_THREAD_TID;
    mainThread->tid = 0;
    mainThread->state = PROCST_APTO;
    mainThread->prio = 2;
    getcontext(&mainThread->context);
    mainThread->data = NULL;

    runningThread = mainThread;

    /** Inicia o terminate context
    */
    getcontext(&terminateContext);
    terminateContext.uc_stack.ss_sp = (char *) malloc (SIGSTKSZ);
    terminateContext.uc_stack.ss_size = SIGSTKSZ;
    terminateContext.uc_link = 0;
    makecontext(&terminateContext, (void (*)(void)) terminateThread , 0);

    /** Inicia o scheduler context
    */
    getcontext(&schedulerContext);
    schedulerContext.uc_stack.ss_sp = (char *) malloc (SIGSTKSZ);
    schedulerContext.uc_stack.ss_size = SIGSTKSZ;
    schedulerContext.uc_link = 0;
    makecontext(&schedulerContext, (void (*)(void)) scheduler , 0);

    return FUNC_NOT_IMPLEMENTED;
}

TCB_t *getThreadAndDelete(PFILA2 queue, int tid)
{
    TCB_t *pThread;
    FirstFila2(queue);
    pThread = (TCB_t*) GetAtIteratorFila2(queue);
    while(pThread != NULL)
    {
        if(pThread->tid == tid)
        {
            DeleteAtIteratorFila2(queue);
            return pThread;
        }
        else
        {
            // otherwise, keep searching
            NextFila2(queue);
            pThread = (TCB_t*) GetAtIteratorFila2(queue);
        }
    }
    return NULL;
}
