/*
 *  Source com as funções utilizadas pela cthread para gerenciar o
 *  escalonamento das threads a nível de usuário.
 */

#include "../include/cutils.h"

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


// 3 listas pra TCBs de threads em estado apto, de acordo com prioridade
FILA2 readyQueuePrio0;
FILA2 readyQueuePrio1;
FILA2 readyQueuePrio2;

// temos o problema da prioridade na hora de tirar de blocked pra apto 
// vou consultar o carissimi sobre isso, mas não é problema por enquanto
FILA2 blockedQueue;
FILA2 suspenseReadyQueue;
FILA2 suspenseBlockedQueue;

// fila de TCBs bloqueados por cjoin
FILA2 cjoinQueue;

// TCB da thread que está no estado executando
// verificar se essa tem que ser ponteiro ou não
TCB_t *runningThread;

// verificar se essa tem que ser ponteiro ou não
TCB_t mainThread;

// contador pra atribuir o TID
// thread main deve ser TID 0
// todos 32 bits
int numTID = 0;

// verificar se a mainThread já existe
int checkMainThread();

// setta a prio da runningThread
void setRunningThreadPrio(int prio);

// retorna a prio da runningThread
int getRunningThreadPrio();

// Pedro isso é contigo
ucontext_t endExecSchedulerContext;

void createThread();

// lembrar de incrementar
void createTID();

// moveRunningToBlocked (ou Cjoin):
// runningThread->context = getContext()
// salva o contexto em Execução

// AppendFila2(blockedQueue, runningThread) (ou AppendFila2(cjoinQueue, runningThread))
// salva na fila de aptos a thread que vai ser preemptada
void moveRunningToBlocked(); // ou cjoinQueue


// moveRunningToReady()
// runningThread->context = getContext()
// salva o contexto em Execução

// AppendFila2(readyQueuePrioX, runningThread)
// salva na fila de aptos a thread que vai ser preemptada
void moveRunningToReady();

// SCHEDULER:
// seleciona a nova thread a ser executada (genérico pra qualquer troca de contexto)
// basicamente pega a primeira thread de mais alta prioridade.
// Se a fila 2 está vazia, então tenta pegar a primeira da fila 1.

// a nova runningThread é a thread de mais alta prioridade
// runningThread = first(readyQueuePrioX) 
// de novo considerando prioridades

// setContext(runningThread->context)
// seta o contexto atual pro contexto da nova thread
void scheduler() ;

// cria main
// inicializar as filas (support.h)
// cria contexto pra chamada da terminateThread
void initialCreate();

/*
 * todas as thread devem ser ligadas a essa função.
 * quando a thread terminar, linkar ao uc_link dela essa função
 * pra liberar recursos e o tcb, e posteriormente chamar o escalonador.
 * Tem que verificar se a thread terminada bloqueava alguém.
 */
void terminateThread();

