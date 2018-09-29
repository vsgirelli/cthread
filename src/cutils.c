/*
 *  Source com as funções utilizadas pela cthread para gerenciar o
 *  escalonamento das threads a nível de usuário.
 */
#include "../include/support.h"
#include "../include/cdata.h"
#include "../include/config.h"
#include "../include/cutils.h"


int numTID = 0;
int mainThreadInitialized = 0;
int yielding_tid = -1;

// PEDRO THINGS (remove o que tu acha que é removível Pebronha)
/******************************************************************************
Globais que acho que precisaremos:

u_context runningThread: Contexto da thread em execução
valéria: eu acho que não é um contexto, pelo que falamos hoje, é um TCB mesmo
u_context scheduler: Contexto do escalonador, precisamos associar esse contexto ao u_link de cada thread criada
valéria: isso seria associar a função de término né? e é ela quem chama o escalonador, certo?

* Filas *

bool cthreadStarted: Na primeira chamada de alguma funcao da lib precisamos criar o contexto do escalonador e da main, usada para marcar isso!

******************************************************************************/
void setYieldingTID(int tid){

    yielding_tid = tid;

}


int searchThread(int tid)
{
    // primeiro procura pela thread na lista de cjoinQueue
    // se já ta em cjoinQueue, retrna THREAD_ALREADY_BLOCKING
    // senão, procura nas demais listas
    return FUNC_NOT_IMPLEMENTED;
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
    newThread->state = THREAD_STATE_READY;
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

}

int createTID()
{
    return ++numTID;

}
// moveRunningToBlocked (ou Cjoin):
// runningThread->context = getContext()
// salva o contexto em Execução

// AppendFila2(blockedQueue, runningThread) (ou
// salva na fila de aptos a thread que vai ser preemptada
int moveRunningToBlocked()
{
    return FUNC_WORKING;
}// ou cjoinQueue

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

    if ( AppendFila2(FilaCorrespondente, runningThread) ){

        return FUNC_NOT_WORKING;

    }

    runningThread = NULL;

    return FUNC_WORKING;

}

// setContext(runningThread->context)
// seta o contexto atual pro contexto da nova thread
void *scheduler()
{

    // Caso a thread com prio2 nao tenha acabado de fazer um yield e haja thread com prio2
    if (FirstFila2(&readyQueuePrio0) == 0 ){

        runningThread = (TCB_t *) GetAtIteratorFila2(&readyQueuePrio0);
        setcontext(&(runningThread->context));

    }

    else if (FirstFila2(&readyQueuePrio1) == 0 ) {

        runningThread = (TCB_t *) GetAtIteratorFila2(&readyQueuePrio1);
        setcontext(&(runningThread->context));

    }


    else if (FirstFila2(&readyQueuePrio2) == 0 ){

        runningThread = (TCB_t *) GetAtIteratorFila2(&readyQueuePrio2);
        DeleteAtIteratorFila2(&readyQueuePrio2);
        setcontext(&(runningThread->context));

    }

}

/*
 * todas as thread devem ser ligadas a essa função.
 * quando a thread terminar, linkar ao uc_link dela essa função
 * pra liberar recursos e o tcb, e posteriormente chamar o escalonador.
 * Tem que verificar se a thread terminada bloqueava alguém.
 */
void *terminateThread()
{

    free(runningThread->context.uc_stack.ss_sp);
    free(runningThread);

    runningThread = NULL;

    scheduler();

    return;
}


int isEmptyQueues(){

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


