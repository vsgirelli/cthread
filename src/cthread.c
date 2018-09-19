#include "../include/cthread.h"
#include "../include/config.h"
/******************************************************************************
Globais que acho que precisaremos:


u_context runningThread: Contexto da thread em execução
u_context scheduler: Contexto do escalonador, precisamos associar esse contexto ao u_link de cada thread criada

* Filas *

bool cthreadStarted: Na primeira chamada de alguma funcao da lib precisamos criar o contexto do escalonador e da main, usada para marcar isso!


******************************************************************************/

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


    // cria_novathread:
    // Utilizamos a funcao createThread para criar a nova thread
    // Apontando para o scheduler como retorno
    // Após isso chamar o scheduler CASO a thread seja de maior prioridade que a atual



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
    // Coloca  a thread na fila de aptos
    // Salva o contexto atual
    // Chama o escalonador


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

    // Verificar se a prioridade está dentre as possíveis
    // POsso aumentar a prioridade da main?

    // Pela  variável global da thread em execução, setar sua prio
    // Se a prio for < 3  a gente percorre as threads em apto para ver se alguma tem mais prioridade
    // Se encontrar chama o escalonador!!

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

    (Anotações sobre a cjoin no dúvidas)
******************************************************************************/
int cjoin(int tid) {
    // Verificar a existência do tid
    // Verificar se não é um pedido de espera para a main

    // Verificar se não chama para uma thread que já está bloqueando, aqui podemos fazer 2 coisas:
    // 1 - Criar uma fila com "threads bloqueadoras" e percorrer para ver se nao existe
    // 2 - Percorrer a fila de threads bloqueadas esperando join para verificar se aquele tid está bloqueando alguma

    // Após isso acho que  é só salvar o contexto e bloquear a thread e eras isso pessoal


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

  * 1 para mutex. +1 pra questão de recursos.

  *
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
******************************************************************************/
int csignal(csem_t *sem) {
  return FUNC_NOT_IMPLEMENTED;
}

/******************************************************************************
Parâmetros:
  name:ponteiro para uma área de memória onde deve ser escrito um string que contém os nomes dos componentes do grupo e seus números de cartão.
  Deve ser uma linha por componente.
  size:quantidade máxima de caracteres que podem ser copiados para o string de identificação dos componentes do grupo.
Retorno:
  Quando executada corretamente: retorna 0 (zero)
  Caso contrário, retorna um valor negativo.
******************************************************************************/
int cidentify (char *name, int size) {
  return FUNC_NOT_IMPLEMENTED;
}
