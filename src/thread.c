#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include "tracefile.h"
#include "prime.h"
#include "util.h"

int debug = 0;
int occupied_cores = 0;
pthread_mutex_t lock;


void *worker(void *args) {

    Trace *trace = args;
    int max_cores = n_cores();
    float diff = diff_time_ms(clock(), trace->t0);

    /* Espera para ser marcada para rodar */
    while(trace->to_run == 0) {
        usleep(10000);
    }
    
    pthread_mutex_lock(&lock);
    occupied_cores++;

    clock_t t = clock();


    while(trace->runtime < trace->dt) {
        is_prime(10000); /* Gasta processamento */
        diff = diff_time_ms(clock(), t);
        trace->runtime += diff;
    }

    occupied_cores--;
    
    trace->finished = 1;
    pthread_mutex_unlock(&lock); 

    return NULL;
}


int finished(Tracefile *tracefile) {

    int i;

    for(i = 0; i < tracefile->length; i++) {
        if(tracefile->trace[i]->finished == 0)
            return 0;
    }

    return 1;
}
