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

        if ( swapcontext(&preemptedThread->context, &runningThread->context) == -1 )
        {

            return FUNC_NOT_WORKING;

        }

    }
    else
    {
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

    if (isEmptyQueues())
    {
        // Nothing to do, continua o fluxo da thread
        return FUNC_WORKING;
    }

    yieldingThread = runningThread;

    moveRunningToReady();

    if ( swapcontext(&yieldingThread->context, &schedulerContext) == -1)
    {

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

    if ( prio > runningThread->prio)
    {
        runningThread->prio = prio;
        //Procura para ver se há uma thread com maior prio
        if (existsHigherPrioThread(prio) == 0)
        {
            TCB_t * preemptedThread = runningThread;
            moveRunningToReady();
            if ( swapcontext(&preemptedThread->context, &schedulerContext) == -1 )
            {

                return FUNC_NOT_WORKING;

            }
        }

    } else {

        runningThread->prio = prio;

    }
    return FUNC_WORKING;
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
    if(checkMainThread() != 0 )
        initialCreate();
    // inicializar o semaforo
    sem->count = count;

    sem->fila = (PFILA2) malloc(sizeof(FILA2));
    // fila será uma lista de filas, contendo uma fila
    // para cada prioridade
    if(CreateFila2(sem->fila) != 0)
        return SEM_INIT_ERROR;

    return 0;
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
    if(checkMainThread() != 0 )
        initialCreate();
    if(sem == NULL)
    {
        return NOT_INITIALIZED_SEM;
    }
    sem->count = sem->count - 1;
    // colocar a thread para bloqueado
    if(sem->count < 0)
    {
        // move para bloqueado
        TCB_t* blockedThread = runningThread;
        if(moveRunningToBlocked() != 0)
        {
            return -1;
        }

        // insere no semaforo para ser acordado pelo csignal
        // ordenado pela prioridade
        TCB_t *pThread;
        FirstFila2(sem->fila);
        pThread = (TCB_t*) GetAtIteratorFila2(sem->fila);
        // caso a fila esta vazia ou eh de menos prio
        // insere no final
        if(pThread == NULL || blockedThread->prio == 2)
        {
            if(AppendFila2(sem->fila, (void*)blockedThread) != 0)
            {
                return -1;
            }
        }
        // caso a prio eh a mais alta
        // insere no inicio
        else if(blockedThread->prio == 0)
        {
            InsertBeforeIteratorFila2(sem->fila, blockedThread);
        }
        // caso seja de media prioridade, ver onde colocar
        else
        {
            //itera sobre a lista do sem
            int bf = -1;
            while(pThread != NULL)
            {
                // caso a prioridade da thread a ser bloqueada eh a maior
                if(pThread->prio > blockedThread->prio)
                {
                    // para o laco e adiciona um boleano dizendo que sera
                    // inserida antes da thread corrente
                    bf = 0;
                    break;
                }
                else
                {
                    NextFila2(sem->fila);
                    pThread = (TCB_t*) GetAtIteratorFila2(sem->fila);
                }
            }
            // caso nao precise inserir antes, significa que soh ha threads
            // de maior prioridade, entao bf = -1 e insere no final da fila
            if(bf==0)
                InsertBeforeIteratorFila2(sem->fila, blockedThread);
            else
                AppendFila2(sem->fila, (void*)blockedThread);
        }
        // escalonador ira colocar alguem para ser executado
        TCB_t * exitedThread = runningThread;

        if ( swapcontext(&exitedThread->context, &schedulerContext) == -1 )
        {

            return FUNC_NOT_WORKING;

        }
        //scheduler();
    }
    return 0;
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
    if(checkMainThread() != 0 )
        initialCreate();
    if(sem == NULL)
    {
        return NOT_INITIALIZED_SEM;
    }

    sem->count = sem->count + 1;
    // Se fila não está vazia
    if(FirstFila2(sem->fila) == 0)
    {
        // Pega o primeiro para acordar e remove da fila
        TCB_t* wakeThread = (TCB_t*) GetAtIteratorFila2(sem->fila);

        DeleteAtIteratorFila2(sem->fila);

        // Remove da fila de bloqueado e colocar para apto
        if(wakeThread->state == PROCST_BLOQ)
        {
            if(moveBlockToReady(wakeThread->tid) < 0)
            {
                return -1;
            }
            // como a movimentacao para a fila de apto
            // eh necessario chamar o escalonador
            if(runningThread->prio > wakeThread->prio){
                TCB_t * preemptedThread = runningThread;

                if ( swapcontext(&preemptedThread->context, &wakeThread->context) == -1 )
                {

                    return FUNC_NOT_WORKING;

                }
                //scheduler();
            }
        }
        else
        {
            return THREAD_NOT_BLOCKED;
        }
    }
    return FUNC_WORKING;
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

    if (strlen(componentes) > size)
    {
        return INSUFICIENT_SIZE;
    }

    strcpy(name, componentes);

    return FUNC_WORKING;
}
