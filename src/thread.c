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
    float diff = diff_time_ms(clock(), trace->t0);

    /* Espera para ser marcada para rodar */
    while(trace->to_run == 0) {
     //   printf("[%s] esperando para comecar ....\n", trace->nome);
        usleep(1000);
    }
    
    /* Comeca o processamento */
    printf("Comecando processamento da thread %s", trace->nome);

    pthread_mutex_lock(&lock);
    occupied_cores++;
    pthread_mutex_unlock(&lock);

    clock_t t = clock();

    while(trace->runtime < trace->dt) {
        is_prime(1000); /* Gasta processamento */
        diff = diff_time_ms(clock(), t);
        printf("Deu erro aqui?");
        trace->runtime += diff;
    }

    /* terminou o process */
    pthread_mutex_lock(&lock);
    occupied_cores--;
    pthread_mutex_unlock(&lock); 
    
    trace->finished = 1;

    return NULL;
}


int finished(Tracefile *tracefile) {

    int i;

    for(i = 0; i < tracefile->length; i++) {
        if(tracefile->trace[i]->finishe == 0)
            return 0;
    }

    return 1;
}
