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
        getcontext(&scheduler);
        scheduler.uc_stack.ss_sp = (char *) malloc(8192 * sizeof(char));
        scheduler.uc_stack.ss_size = 8192 * sizeof(char);
        scheduler.uc_link = &ctx[0];
        makecontext(&scheduler, schedThread, 0);
        sched_init = 1;
    }

    puts("SCHEDULED");
}

int
main (void)
{
    char st1[8192];
    char st2[8192];
    char st3[8192];

    scheduler_point();


    getcontext(&ctx[1]);
    ctx[1].uc_stack.ss_sp = st1;
    ctx[1].uc_stack.ss_size = sizeof st1;
    ctx[1].uc_link = &scheduler;
    makecontext(&ctx[1], f1, 0);


    getcontext(&ctx[2]);
    ctx[2].uc_stack.ss_sp = st2;
    ctx[2].uc_stack.ss_size = sizeof st2;
    ctx[2].uc_link = &scheduler;
    makecontext(&ctx[2], f2, 0);


    getcontext(&ctx[3]);
    ctx[3].uc_stack.ss_sp = st3;
    ctx[3].uc_stack.ss_size = sizeof st3;
    ctx[3].uc_link = &scheduler;
    makecontext(&ctx[3], f3, 0);


    swapcontext(&ctx[0], &ctx[2]);
    swapcontext(&ctx[0], &ctx[1]);
    puts("T1");
    swapcontext(&ctx[0], &ctx[3]);
    return 0;


}
