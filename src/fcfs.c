#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include "tracefile.h"
#include "prime.h"
#include "util.h"


void *fcfs(void *args) {

    Trace *trace = args;

    float diff = diff_time_ms(clock(), trace->t0);

    while(trace->dt > diff || trace->deadline <= diff) {

        /* Faz processamento */
        is_prime(1000);
        diff = diff_time_ms(clock(), trace->t0);

    }

    return NULL;
}