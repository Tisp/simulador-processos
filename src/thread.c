#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include "tracefile.h"
#include "prime.h"
#include "util.h"
#include "output.h"

int debug = 0;
int occupied_cores = 0;
pthread_mutex_t lock;


void *worker(void *args) {
    pthread_mutex_lock(&lock);

    Trace *trace = args;
    int max_cores = n_cores();
    float diff;
    int my_core = 0;

    /* Espera para ser marcada para rodar */
    while(occupied_cores > max_cores) {
            usleep(10000);
    }
    

    /* Inicio do processamento */
    occupied_cores++;
    my_core = occupied_cores;
  //  pthread_mutex_unlock(&lock); 


    if(debug) 
        fprintf(stderr, "Processo %s usando CPU %d\n", trace->nome, my_core);
    

    clock_t t = clock();

    while(trace->runtime <= trace->dt) {
        //printf("Processo %s [%lf, %lf] falta: %lf\n", trace->nome, trace->dt, trace->runtime,(trace->dt - trace->runtime));
        is_prime(11587); /* Gasta processamento */
        diff = diff_time_s(clock(), t);
        trace->runtime = diff;
    }

    if(debug)
        fprintf(stderr, "Processo %s finalizado, liberando CPU %d\n", trace->nome, my_core);
    

  // pthread_mutex_lock(&lock);
   occupied_cores--;
   diff = diff_time_s(clock(), trace->init_time);
   write_output(trace->nome, diff, (diff - trace->t0));
   
   trace->finished = 1;
   pthread_exit(trace->thread);
   
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
