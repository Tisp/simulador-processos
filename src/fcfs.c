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
    int num_cores = n_cores();
           
    /* Comeca a simulacao de fcfs */
    clock_t t1 = clock();
    
    while(1) {
        
        float diff = diff_time_ms(clock(), t1);
        i = i % tracefile->length;

        if(diff >= tracefile->trace[i]->t0 && occupied_cores <= num_cores) {
            tracefile->trace[i]->to_run = 1;
            pthread_create(&tracefile->trace[i]->thread, NULL, worker, tracefile->trace[i]);   
            i++;
        }

        /* Todos os processos foram terminados */
        if(finished(tracefile) == 1) break;
    }
}

