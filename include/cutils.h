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

#include "../include/config.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/support.h"
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <string.h>

// 3 listas pra TCBs de threads em estado apto, de acordo com prioridade
extern FILA2 readyQueuePrio0;
extern FILA2 readyQueuePrio1;
extern FILA2 readyQueuePrio2;

// temos o problema da prioridade na hora de tirar de blocked pra apto 
// vou consultar o carissimi sobre isso, mas não é problema por enquanto
extern FILA2 blockedQueue;
extern FILA2 suspendedReadyQueue;
extern FILA2 suspendedBlockedQueue;

// fila de TCBs bloqueados por cjoin
extern FILA2 cjoinQueue;

// TCB da thread que está no estado executando
// verificar se essa tem que ser ponteiro ou não
extern TCB_t *runningThread;

// verificar se essa tem que ser ponteiro ou não
extern TCB_t mainThread;

// contador pra atribuir o TID
// thread main deve ser TID 0
// todos 32 bits
extern int numTID = 0;

// Pedro isso é contigo
extern ucontext_t endExecSchedulerContext;

// struct com o tid bloqueado e com o tid bloqueador das threads por efeito de
// um cjoin()
typedef struct cjt {
  int blockedTID; // thread bloqueada
  int blockingTID; // thread bloqueadora
} cjoin_thread;

// TODO atualizar a declaração de acordo com a última versão das funções.
void scheduler(void);
void initialCreate(void);
int checkMainThread(void);
void setRunningThreadPrio(int prio);
int getRunningThreadPrio(void);
