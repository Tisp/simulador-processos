#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include "tracefile.h"
#include "prime.h"
#include "util.h"
#include "thread.h"


/* First-Come First-Served */
/**
Criar cada thread, e ficar em loop se esta precisa ser rodada


*/
void fcfs(Tracefile *tracefile) {

    int i = 0;
    int max_cores = n_cores();
    extern int occupied_cores;

    /* Inicia as threads */
    printf("Iniciando as threads...\n");
    for(i = 0; i < tracefile->length; i++) 
          pthread_create(&tracefile->trace[i]->thread, NULL, worker, tracefile->trace[i]);
   printf("Threads iniciadas\n");



    /* Comeca a simulacao de fcfs */
    clock_t t1 = clock();
    
    while(1) {
        
        float diff = diff_time_ms(clock(), t1);

        printf("Time %lf -> cores:%d\n",diff, occupied_cores);
        if(diff >= tracefile->trace[i]->t0 && occupied_cores <= max_cores) {
            tracefile->trace[i]->to_run = 1;
        }

        /* Todos os processos foram terminados */
        if(finished(tracefile)) break;
    }
}

