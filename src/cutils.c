/*
 *  Source com as funções utilizadas pela cthread para gerenciar o
 *  escalonamento das threads a nível de usuário.
 */

#include "../include/cutils.h"
#include "../include/config.h"
#include "../include/cdata.h"
#include "../include/support.h"
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <string.h>

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

int searchThread(int tid) {
  // primeiro procura pela thread na lista de cjoinQueue
  // se já ta em cjoinQueue, retrna THREAD_ALREADY_BLOCKING
  // senão, procura nas demais listas
  return 0;
}

// verificar se a mainThread já existe
int checkMainThread();

void createThread();

// lembrar de incrementar
void createTID();

// moveRunningToBlocked (ou Cjoin):
// runningThread->context = getContext()
// salva o contexto em Execução

// AppendFila2(blockedQueue, runningThread) (ou 
// salva na fila de aptos a thread que vai ser preemptada
int moveRunningToBlocked() {
  if (AppendFila2(&blockedQueue, runningThread) != 0) {
    return APPEND_ERROR;
  }

  return 0;
}

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
int scheduler() {
  return FUNC_NOT_IMPLEMENTED;
}

// cria main
// inicializar as filas (support.h)
// cria contexto pra chamada da terminateThread e do scheduler
int initialCreate() {
  printf("initialCreate called\n");

  return 0;
}

/*
 * todas as thread devem ser ligadas a essa função.
 * quando a thread terminar, linkar ao uc_link dela essa função
 * pra liberar recursos e o tcb, e posteriormente chamar o escalonador.
 * Tem que verificar se a thread terminada bloqueava alguém.
 */
void terminateThread();

/*
void createThreads() {
    TCB_t * t1 = (TCB_t*)malloc(sizeof(TCB_t));
    TCB_t * t2 = (TCB_t*)malloc(sizeof(TCB_t));

    // thread 1
    t1->tid = 0;
    t1->prio = 0;
    t1->state = THREAD_STATE_RUNNING;
    getcontext(t1->context);
    
    getcontext(&(t1->context));
    t1->context.uc_link = &terminateThread;
    t1->context.uc_stack.ss_sp = (char*)malloc(SIGSTKSZ);
    t1->context.uc_stack.ss_size = SIGSTKSZ;
    makecontext(&(t1->context), (void(*)(void))start, 1, arg);

    // thread 2
    t2->tid = 0;
    t2->prio = 0;
    t2->state = THREAD_STATE_READY;
    getcontext(t2->context);
    
    getcontext(&(t2->context));
    t2->context.uc_link = &terminateThread;
    t2->context.uc_stack.ss_sp = (char*)malloc(SIGSTKSZ);
    t2->context.uc_stack.ss_size = SIGSTKSZ;
    makecontext(&(t2->context), (void(*)(void))start, 1, arg);
}*/
