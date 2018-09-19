tcb main (se tcb main == null, then createMain());

FILA2 readyQueuePrio0;
FILA2 readyQueuePrio1;
FILA2 readyQueuePrio2;

FILA2 blockedQueue;
FILA2 suspenseReadyQueue;
FILA2 suspenseBlockedQueue;

// fila de TCBs bloqueados por cjoin
FILA2 cjoinQueue;

TCB_t *runningThread;

TCB_t mainThread;

int numberOfThreads = 0;

ucontext_t endExecSchedulerContext;

// struct com o tid bloqueado e com o tid bloqueador das threads por efeito de
// um cjoin()
typedef struct cjt {
  int blockedTID; // thread bloqueada
  int blockingTID; // thread bloqueadora
} cjoin_thread;

// moveRunningToBlocked (ou Cjoin):
// runningThread->context = getContext()
// salva o contexto em Execução

// AppendFila2(blockedQueue, runningThread) (ou AppendFila2(cjoinQueue, runningThread))
// salva na fila de aptos a thread que vai ser preemptada
moveRunningToBlocked(); // ou cjoinQueue


// moveRunningToReady()
// runningThread->context = getContext()
// salva o contexto em Execução

// AppendFila2(readyQueuePrioX, runningThread)
// salva na fila de aptos a thread que vai ser preemptada
moveRunningToReady();

// SCHEDULER:
// seleciona a nova thread a ser executada (genérico pra qualquer troca de contexto)
// basicamente pega a primeira thread de mais alta prioridade.
// Se a fila 2 está vazia, então tenta pegar a primeira da fila 1.

// a nova runningThread é a thread de mais alta prioridade
// runningThread = first(readyQueuePrioX) 
// de novo considerando prioridades

// setContext(runningThread->context)
// seta o contexto atual pro contexto da nova thread
scheduler() ;

// cria main
// inicializar as filas (support.h)
// cria contexto pra chamada da terminateThread
initialCreate();

/*
 * todas as thread devem ser ligadas a essa função.
 * quando a thread terminar, linkar ao uc_link dela essa função
 * pra liberar recursos e o tcb, e posteriormente chamar o escalonador.
 * Tem que verificar se a thread terminada bloqueava alguém.
 */
terminateThread();

createThread();

// lembrar de incrementar
createTID();
