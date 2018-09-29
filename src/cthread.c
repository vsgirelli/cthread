/*
 *  Arquivo com a implementação das funções da biblioteca de thread cthread.
 */
#include "../include/support.h"
#include "../include/cdata.h"
#include "../include/config.h"
#include "../include/cutils.h"
#include "../include/cthread.h"


/******************************************************************************
Parâmetros:
  start: ponteiro para a função que a thread executará.
  arg: um parâmetro que pode ser passado para a thread na sua criação.
  prio: valores numéricos 0, 1 e 2 (alta, média e baixa prioridade).
        (código de erro para demais valores)
Retorno:
  Se correto => Valor positivo, que representa o identificador da thread criada
  Se erro	   => Valor negativo.

Observações:
  * A função deve alocar TCBs e estruturas necessárias para gerência da thread.
  * Ao final da criação da thread, ela deve ser inserida ao fim da lista de aptos (FIFO).

  * A função main possui um comportamento diferente (seção 4 do enunciado).

  * Quando um thread de maior prioridade for criada, a thread criadora deve ser preemptada.

******************************************************************************/

int ccreate (void* (*start)(void*), void *arg, int prio)
{

    int tid;
    TCB_t* newThread = NULL;
    if(checkMainThread() != 0 )
        initialCreate();

    // Verifica prioridade
    if (prio < PRIO_0 || prio > PRIO_2)
    {
        return PRIO_ERROR;
    }

    tid = createTID();

    newThread = createThread(start, arg, prio, tid);


    if (newThread->prio < runningThread->prio)
    {
        TCB_t * preemptedThread = runningThread;

        moveRunningToReady();

        runningThread = newThread;

        if ( swapcontext(&(preemptedThread->context), &(runningThread->context)) == -1 ) {

            return FUNC_NOT_WORKING;

        }

    } else {
        moveCreatedToList(newThread);

    }


    return tid;
}

/******************************************************************************
Parâmetros:
Sem parâmetros
Retorno:
  Quando executada corretamente: retorna 0 (zero)
  Caso contrário, retorna um valor negativo.

Observações:
  * Thread que executa essa função retorna para a fila de aptos.

  * Escalonador deve ser chamado para selecionar a próxima thread.

******************************************************************************/
int cyield(void)
{
    TCB_t* yieldingThread;

    if (isEmptyQueues()){
        // Nothing to do, continua o fluxo da thread
        return FUNC_WORKING;
    }

    yieldingThread = runningThread;

    moveRunningToReady();

    if ( swapcontext(&yieldingThread->context, &schedulerContext) == -1){

        return FUNC_NOT_WORKING;

    }

    return FUNC_WORKING;
}

/******************************************************************************
Parâmetros:
  tid: identificador da thread cuja prioridade será alterada (deixar sempre esse campo como NULL em 2018/02)
  prio: nova prioridade da thread.
Retorno:
  Quando executada corretamente: retorna 0 (zero)
  Caso contrário, retorna um valor negativo.

Observações:
  * Se a thread setar sua prioridade a um valor menor do que a prioridade de um
  thread no estado apto, o escalonador deve ser chamado para preemptar a
  thread chamadora.

******************************************************************************/
int csetprio(int tid, int prio)
{
    if (prio < PRIO_0 || prio > PRIO_2)
    {
        return PRIO_ERROR;
    }
    // POsso aumentar a prioridade da main?

// setRunningThreadPrio(prio);
    // if the new priority is lower than the higher priority,
    // then check if there is any thread with higher priority,
    // if so, the current thread must suffer preemption.
    //if (getRunningThreadPrio() < PRIO_2) {
    // usar as funções da support.h pra percorrer as listas
    // verifica na fila de prio 2
    //    se achou, chama função que salva o contexto e bota o TCB pra o apto
    //              chama scheduler pra selecionar próxima thread.
    // se vazia, verifica na fila de prio 1
    //    se achou, chama função que salva o contexto e bota o TCB pra o apto
    //              chama scheduler pra selecionar próxima thread.
    // se não achou em 2 e em 1, então não preempta, pq não há nenhuma thread de
    // prioridade maior
    //}

    return FUNC_NOT_IMPLEMENTED;
}

/******************************************************************************
Parâmetros:
  tid:identificador da thread cujo término está sendo aguardado.
Retorno:
  Quando executada corretamente: retorna 0 (zero)
  Caso contrário, retorna um valor negativo.

Observações:
  * Uma thread só pode ser esperada por uma única thread. Apenas a primeira
    thread que pedir cjoin fica bloqueada.

  * A partir da segunda chama pra mesma thread, cjoin deve retornar código de erro.

  * Se a chamada for para uma thread que não existe ou que já foi terminada,
    cjoin retorna um código de erro.

  * Não há estado zombie.

  * Quando uma thread que bloqueava outras terminar, o escalonador deve ser chamado e
    deve levar em conta as prioridades.

    (Anotações sobre a cjoin no dúvidas e no labbook)
******************************************************************************/
int cjoin(int tid)
{
    cjoin_thread *cjt;

    if(mainThread == NULL)
    {
        if (initialCreate() != 0)
        {
            // TODO criar código pra erro de inicialização de fila
        }
        // se a thread main não existia, significa que não existia mais nenhuma thread
        // então pode restornar erro de THREAD_NOT_FOUND
        return THREAD_NOT_FOUND;
    }

    // Verificar se a thread já bloqueia alguém
    // e depois verifica a existência do tid pelo qual se quer bloquear
    if(searchThread(tid) == THREAD_ALREADY_BLOCKING)
    {
        return THREAD_ALREADY_BLOCKING;
    }
    else if (searchThread(tid) == THREAD_NOT_FOUND)
    {
        return THREAD_NOT_FOUND;
    }

    // TODO Verificar se não é um pedido de espera para a main (erro?)

    cjt = (cjoin_thread*) malloc(sizeof(cjoin_thread));
    cjt->blockedTID = runningThread->tid;
    cjt->blockingTID = tid;
    //AppendFila2(&cjoinQueue, cjt);

    // chama função que salva o contexto e bota o TCB pra bloqueado
    // chama scheduler pra selecionar próxima thread.
    return FUNC_NOT_IMPLEMENTED;
}

/******************************************************************************
Parâmetros:
  sem:ponteiro para uma variável do tipo csem_t. Aponta para uma estrutura de dados que representa a variável semáforo.
  count: valor a ser usado na inicialização do semáforo. Representa a quantidade de recursos controlados pelo semáforo.
Retorno:
  Quando executada corretamente: retorna 0 (zero)
  Caso contrário, retorna um valor negativo.

Observações:
  * inicializa o semáforo.

  * deve ser chamada obrigatoriamente antes de cwait e csignal.

  * 1 para mutex. Outros valores pra questão de recursos.
******************************************************************************/
int csem_init(csem_t *sem, int count)
{
    return FUNC_NOT_IMPLEMENTED;
}

/******************************************************************************
Parâmetros:
  sem:ponteiro para uma variável do tipo semáforo.
Retorno:
  Quando executada corretamente: retorna 0 (zero)
  Caso contrário, retorna um valor negativo.

Observações:
  * Solicitar um recurso.

  * Se count > 0, recurso livre, então decrementa count e deixa a thread executar.

  * Se count <= 0, recurso ocupado, então decrementa count e bota a thread pra
    dormir (bota ela na lista do semáforo).

  * Sempre se decrementa o count.
******************************************************************************/
int cwait(csem_t *sem)
{
    return FUNC_NOT_IMPLEMENTED;
}

/******************************************************************************
Parâmetros:
  sem:ponteiro para uma variável do tipo semáforo.
Retorno:
  Quando executada corretamente: retorna 0 (zero)
  Caso contrário, retorna um valor negativo.

Observações:
  * A cada chamada incrementa-se o count.

  * Se houver mais de uma thread bloqueada, a primeira deve ser posta pro estado apto
    (devido à política FIFO).

  * Lembrar que o escalonador é preemptivo por prioridade. Então se csignal
    acordar uma thread de mais alta prioridade, a que está executando tem que
    ser preemptada.

  * Deve haver política de prioridade também para as threads que estão
   aguardando pelo recurso. Se houver uma de média e uma de alta esperando,
    mesmo que a de média tenha chego antes, a de alta deve ganhar o recurso.
******************************************************************************/
int csignal(csem_t *sem)
{
    return FUNC_NOT_IMPLEMENTED;
}

/******************************************************************************
Parâmetros:
  name: ponteiro para uma área de memória onde deve ser escrito um string que
    contém os nomes dos componentes do grupo e seus números de cartão.
    Deve ser uma linha por componente.
  size: quantidade máxima de caracteres que podem ser copiados para o string de
    identificação dos componentes do grupo.
Retorno:
  Quando executada corretamente: retorna 0 (zero)
  Caso contrário, retorna um valor negativo.
******************************************************************************/
int cidentify (char *name, int size)
{
    char* componentes = "Leandro Pereira - 00273114 \nPedro Trindade - 00264846\nValeria Girelli - 00261596";

    if (strlen(componentes) > size) {
        return INSUFICIENT_SIZE;
    }

    strcpy(name, componentes);

    return FUNC_WORKING;
}
