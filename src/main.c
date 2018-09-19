#include <stdio.h>
#include <ucontext.h>

static ucontext_t scheduler;
char sched_init = 0;
static ucontext_t ctx[4];


static void
f1 (void)
{
    puts("start f1");
    swapcontext(&ctx[1], &ctx[2]);
    puts("finish f1");
}


static void
f2 (void)
{
    puts("start f2");
    swapcontext(&ctx[2], &ctx[1]);
    puts("finish f2");
}


static void
f3 (void)
{
    puts("Entrou F3");

}
static void schedThread(){

    puts("Miiip");
    makecontext(&scheduler, schedThread, 0);
}

static void
scheduler_point (void)
{
    if (sched_init == 0){
        // Obtenho o contexto e salvo ele alocando a pilha para o escalonador
        getcontext(&scheduler);
        scheduler.uc_stack.ss_sp = (char *) malloc(8192 * sizeof(char));
        scheduler.uc_stack.ss_size = 8192 * sizeof(char);
        scheduler.uc_link = &ctx[0];
        // Quando executar essa contexto executará a funcao schedThread
        makecontext(&scheduler, schedThread, 0);
        sched_init = 1;
    }
}

int
main (void)
{

    // Aqui eu estaria alocando o a pilha para cada thread que eu vou criar
    char st1[8192];
    char st2[8192];
    char st3[8192];

    // Funcao para definir o escalonador
    scheduler_point();

    //Aqui estou definindo o que seria a thread f1
    getcontext(&ctx[1]);
    ctx[1].uc_stack.ss_sp = st1;
    ctx[1].uc_stack.ss_size = sizeof st1;
    // Ponto de retorno é o escalonador
    ctx[1].uc_link = &scheduler;
    makecontext(&ctx[1], f1, 0);


    // Definindo a thread f2
    getcontext(&ctx[2]);
    ctx[2].uc_stack.ss_sp = st2;
    ctx[2].uc_stack.ss_size = sizeof st2;
    // POnto de retorno é o escalonador
    ctx[2].uc_link = &scheduler;
    makecontext(&ctx[2], f2, 0);

    // Definindo a thread f3
    getcontext(&ctx[3]);
    ctx[3].uc_stack.ss_sp = st3;
    ctx[3].uc_stack.ss_size = sizeof st3;
    // POnto de retorno é o escalonador
    ctx[3].uc_link = &scheduler;
    makecontext(&ctx[3], f3, 0);

    //  Troco o contexto atual para o &ctx[2] que contém a thread f2
    swapcontext(&ctx[0], &ctx[2]);
    // Troco o contexto atual para o &ctx[1] que contém a thread f1
    swapcontext(&ctx[0], &ctx[1]);
    puts("T1");
    // Troco o contexto agora para a thread f3
    swapcontext(&ctx[0], &ctx[3]);



    return 0;


}
