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
    while(trace->to_run == 0 || occupied_cores > max_cores) {
        usleep(1000*10);
    }
    
    /* Comeca o processamento */
    printf("Comecando processamento da thread %s\n", trace->nome);

    pthread_mutex_lock(&lock);
    occupied_cores++;
    pthread_mutex_unlock(&lock);

    clock_t t = clock();

    printf("Cores Ocuppied [%d]\n", occupied_cores);
    while(trace->runtime < trace->dt) {
     //   printf("%s ja rodei por %lf - %lf\n", trace->nome, trace->runtime, trace->dt);
        is_prime(1000); /* Gasta processamento */
        diff = diff_time_ms(clock(), t);
        trace->runtime += diff;
    }

    /* terminou o process */
    pthread_mutex_lock(&lock);
    printf("Liberando um processador\n");
    occupied_cores--;
    pthread_mutex_unlock(&lock); 
    
    trace->finished = 1;

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
