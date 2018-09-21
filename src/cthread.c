/*
 *  Arquivo com a implementação das funções da biblioteca de thread cthread.
 */

#include "../include/cutils.h"
// o ideal seria apenas adicionarmos a cthread.h, porém não podemos adicionar
// lá a cutils.h

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
int ccreate (void* (*start)(void*), void *arg, int prio) {
  if(checkMainThread() != 0 )
    initialCreate();

    // Verifica prioridade
   if (prio != PRIO_0 && prio != PRIO_1 && prio != PRIO_2) {
     return PRIO_ERROR;
   }
    // http://pubs.opengroup.org/onlinepubs/009695299/functions/makecontext.html
    // Prioridade dentro dos padrões, próximos passos:
    // Verificar se a thread main foi criada, 2 casos possíveis:
    //       1 - Se não existir, vamos ter que criar ela, pegar seu contexto e salvar num TCB,
    //           podemos criar uma funcao createThread(u_context, func, arg)
    //       2 - Caso exista prosseguimos para cria_novathread:

   // novo tid
   // criar contexto nova thread (linkar pra rotina de terminateThread)
   // criar tcb nova thread
   // linkar contexto ao TCB
   // Verificar se prio > runningThread->prio
   //     se sim, chama função que salva o contexto atual e bota o TCB pra o apto
   //             chama scheduler pra selecionar próxima thread.
   //     se não, adicionar para a fila certa de apto
    // retorna ok

  return FUNC_NOT_IMPLEMENTED;
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
int cyield(void) {
    // chama função que salva o contexto e bota o TCB pra o apto
    // chama scheduler pra selecionar próxima thread.

  return FUNC_NOT_IMPLEMENTED;
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
int csetprio(int tid, int prio) {
  if (prio != PRIO_0 && prio != PRIO_1 && prio != PRIO_2) {
    return PRIO_ERROR;
  }
  // POsso aumentar a prioridade da main?

  setRunningThreadPrio(prio);
  // if the new priority is lower than the higher priority,
  // then check if there is any thread with higher priority,
  // if so, the current thread must suffer preemption.
  if (getRunningThreadPrio() < PRIO_2) {
    // usar as funções da support.h pra percorrer as listas
    // verifica na fila de prio 2
    //    se achou, chama função que salva o contexto e bota o TCB pra o apto
    //              chama scheduler pra selecionar próxima thread.
    // se vazia, verifica na fila de prio 1
    //    se achou, chama função que salva o contexto e bota o TCB pra o apto
    //              chama scheduler pra selecionar próxima thread.
    // se não achou em 2 e em 1, então não preempta, pq não há nenhuma thread de
    // prioridade maior
  }

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
int cjoin(int tid) {
    // Verificar a existência do tid pelo qual se quer bloquear
    // Verificar se não é um pedido de espera para a main (erro?)

    // Verificar se não chama para uma thread que já está bloqueando:
    // se, em cjoinQueue, existir um nó cujo blockingTID == tid
    // então retorna erro
    // senão, AppendFila2(cjoinQueue, novo nó)
    // o novo nó irá possuir o tid e o runningThread->tid

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
int csem_init(csem_t *sem, int count) {
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
int cwait(csem_t *sem) {
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
int csignal(csem_t *sem) {
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
int cidentify (char *name, int size) {
  return FUNC_NOT_IMPLEMENTED;
}
