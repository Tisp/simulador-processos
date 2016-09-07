#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include "tracefile.h"
#include "prime.h"
#include "util.h"
#include "output.h"

int debug = 0;
pthread_mutex_t lock;
int *occupied_cores;


int find_free_core() {
    
    int i;
    int max_cores = n_cores();

    for(i = 0; i < max_cores; i++) {
        if(occupied_cores[i] == 0)
            return i;
    }

    return -1;
}

void *worker(void *args) {

    pthread_mutex_lock(&lock);

    Trace *trace = args;
    float diff;
    int my_core = 0;
    clock_t t = clock();


    /* Espera para ser marcada para rodar */
    LOOP:while(trace->to_run == 0) {
            usleep(10000);
    }

    /* Inicio do processamento */
     my_core = find_free_core();

     /* Espera liberar cpu */
     if(my_core == -1) goto LOOP;

     occupied_cores[my_core] = 1;

    if(debug) 
        fprintf(stderr, "Processo %s usando CPU %d\n", trace->nome, my_core);
    
    while(trace->runtime <= trace->dt) {

        if(trace->to_run == 0) {
            occupied_cores[my_core] = 0;
            goto LOOP;
        }

       //printf("Processo %s [%lf, %lf] falta: %lf\n", trace->nome, trace->dt, trace->runtime,(trace->dt - trace->runtime));
        is_prime(11587); /* Gasta processamento */
        diff = diff_time_s(clock(), t);
        trace->runtime = diff;
    }

    if(debug)
        fprintf(stderr, "Processo %s finalizado, liberando CPU %d\n", trace->nome, my_core);
    

  // pthread_mutex_lock(&lock);
   occupied_cores[my_core] = 0;

   diff = diff_time_s(clock(), trace->init_time);
   write_output(trace->nome, diff, (diff - trace->t0));
   
   trace->finished = 1;
   pthread_exit(&trace->thread);
   
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
