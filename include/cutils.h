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
#include <ucontext_t.h>
#include <string.h>

// struct com o tid bloqueado e com o tid bloqueador das threads por efeito de
// um cjoin()
typedef struct cjt {
  int blockedTID; // thread bloqueada
  int blockingTID; // thread bloqueadora
} cjoin_thread;

// TODO atualizar a declaração de acordo com a última versão das funções.
void scheduler();
void initialCreate();
