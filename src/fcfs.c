#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include "tracefile.h"
#include "prime.h"
#include "util.h"


/* First-Come First-Served */
/**
Criar cada thread, e ficar em loop se esta precisa ser rodada


*/
void *fcfs(void *args) {

    Tracefile *tracefile = args;
    int i;




    // /* Percorre todos os trace */
    // for(i = 0; i < tracefile->length; i++) {
    //     float diff = diff_time_ms(clock(), trace->t0);

    // }

    // while(trace->dt > diff || trace->deadline <= diff) {

    //     /* Faz processamento */
    //     is_prime(1000);
    //     diff = diff_time_ms(clock(), trace->t0);

    // }

    return NULL;
}