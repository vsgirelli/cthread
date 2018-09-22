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
    if(checkThreadBlocking(cjoinQueue, tid) != 0)
        return THREAD_ALREADY_BLOCKING;
    // senão, procura nas demais listas
    if(searchThread(readyQueuePrio0, tid) == 0)
        return 0;
    if(searchThread(readyQueuePrio1, tid) == 0)
        return 0;
    if(searchThread(readyQueuePrio2, tid) == 0)
        return 0;
    if(searchThread(blockedQueue, tid) == 0)
        return 0;
    return THREAD_NOT_FOUND;
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
void moveRunningToBlocked(); // ou cjoinQueue

int moveRunningToCjoin() {
    AppendFila2(&cjoinQueue, runningThread);
    return FUNC_NOT_IMPLEMENTED;
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
void scheduler() ;

// cria main
// inicializar as filas (support.h)
// cria contexto pra chamada da terminateThread
int initialCreate();

/*
 * todas as thread devem ser ligadas a essa função.
 * quando a thread terminar, linkar ao uc_link dela essa função
 * pra liberar recursos e o tcb, e posteriormente chamar o escalonador.
 * Tem que verificar se a thread terminada bloqueava alguém.
 */
void terminateThread();

