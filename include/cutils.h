/*
 *  Header com as funções utilizadas pela cthread para gerenciar o
 *  escalonamento das threads a nível de usuário.
 */

// TODA FUNÇÃO QUE *DEVERÁ SER CHAMADA* PELA cthread.c PARA ESCALONAR,
// MUDAR DE FILA, ADICIONAR EM FILA, PREEMPTAR, SEMÁFORO, QUALQUER COISA QUE A
// cthread.c PRECISE, DEVE SER DECLARADO AQUI COMO AS FUNÇÕES ABAIXO.

// todos os .h estão sendo incluídos aqui, portanto, os demais .h e .c apenas
// devem incluir cutils.h
// pra não haver múltiplos includes
#ifndef __cutils__
#define __cutils__

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <string.h>

#define MAIN_THREAD_TID = 0

// 3 listas pra TCBs de threads em estado apto, de acordo com prioridade
FILA2 readyQueuePrio0;
FILA2 readyQueuePrio1;
FILA2 readyQueuePrio2;

// temos o problema da prioridade na hora de tirar de blocked pra apto
// vou consultar o carissimi sobre isso, mas não é problema por enquanto
FILA2 blockedQueue;
FILA2 suspendedReadyQueue;
FILA2 suspendedBlockedQueue;

// fila de TCBs bloqueados por cjoin
FILA2 cjoinQueue;

// TCB da thread que está no estado executando
// verificar se essa tem que ser ponteiro ou não
TCB_t *runningThread;

// verificar se essa tem que ser ponteiro ou não
TCB_t *mainThread;

// Contexto de execução ao término de uma thread
ucontext_t terminateContext;

// Contexto do scheduler
ucontext_t schedulerContext;


// contador pra atribuir o TID
// thread main deve ser TID 0
// todos 32 bits
int numTID;

// Pedro isso é contigo
ucontext_t endExecSchedulerContext;

// struct com o tid bloqueado e com o tid bloqueador das threads por efeito de
// um cjoin()
typedef struct cjt {
  int blockedTID; // thread bloqueada
  int blockingTID; // thread bloqueadora
} cjoin_thread;

// TODO atualizar a declaração de acordo com a última versão das funções.
void *scheduler(void);
int initialCreate(void);
int checkMainThread(void);
void setRunningThreadPrio(int prio);
int getRunningThreadPrio(void);
TCB_t * getThread(int tid);
int createTID();
int moveCreatedToList(TCB_t* newThread);
TCB_t* createThread(void* (*start)(void*), void *arg, int prio, int tid);

int searchThread(int tid);
int existsHigherPrioThread(int prio);
int moveRunningToReady();
int moveRunningToCjoin();
int moveRunningToBlocked();
int moveBlockToReady();
int isEmptyQueues();
TCB_t *getThreadAndDelete(PFILA2 queue, int tid);

#endif
