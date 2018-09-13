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
int ccreate (void* (*start)(void*), void *arg, int prio) {
  /*
   *if (prio != PRIO_0 && prio != PRIO_1 && prio != PRIO_2) {
   *  return PRIO_ERROR;
   *}
   */
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
  return FUNC_NOT_IMPLEMENTED;
}

/******************************************************************************
Parâmetros:
  tid:identificador da thread cujo término está sendo aguardado.
Retorno:
  Quando executada corretamente: retorna 0 (zero)
  Caso contrário, retorna um valor negativo.
******************************************************************************/
int cjoin(int tid) {
  return FUNC_NOT_IMPLEMENTED;
}

/******************************************************************************
Parâmetros:
  sem:ponteiro para uma variável do tipo csem_t. Aponta para uma estrutura de dados que representa a variável semáforo.
  count: valor a ser usado na inicialização do semáforo. Representa a quantidade de recursos controlados pelo semáforo.
Retorno:
  Quando executada corretamente: retorna 0 (zero)
  Caso contrário, retorna um valor negativo.
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
