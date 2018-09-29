/*
 *  Arquivo para conter códigos de erro,
 *  valores de prioridade,
 *  estados das threads
 */
#ifndef __cconfig__
#define __cconfig__

// CÓDIGOS DE ERRO
// aparentemente, ele quer valores negativos pra erro
#define FUNC_WORKING 0
#define FUNC_NOT_IMPLEMENTED -1
#define FUNC_NOT_WORKING -2
/*
 * Os valores de prioridade válidos são
 * 0 - alta
 * 1 - média
 * 2 - baixa
 * Caso uma prioridade diferente for informada, informar código de erro.
 */
#define PRIO_ERROR -3
// thread de um dado tid não existe
#define THREAD_NOT_FOUND -4
#define THREAD_ALREADY_BLOCKING -5
#define NO_THREAD_TO_SCHEDULE -6
#define INSUFICIENT_SIZE -7
#define SEM_INIT_ERROR -8
#define NOT_INITIALIZED_SEM -9
#define THREAD_NOT_BLOCKED -10;

// CÓDIGOS DE PRIORIDADE
#define PRIO_0 0
#define PRIO_1 1
#define PRIO_2 2


// ESTADOS DE EXECUÇÃO DAS THREADS
#define THREAD_STATE_CREATED 0
#define THREAD_STATE_READY 1
#define THREAD_STATE_RUNNING 2
#define THREAD_STATE_BLOCKED 3
#define THREAD_STATE_FINISHED 4
#define THREAD_STATE_SUSPENDED_READY 5
#define THREAD_STATE_SUSPENDED_BLOCKED 6

#endif
