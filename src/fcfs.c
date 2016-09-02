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

    /* Inicia as threads */
  //  for(i = 0; i < tracefile->length; i++) 
        pthread_create(&tracefile->trace[i]->thread, NULL, worker, tracefile->trace[i]);   

           
    /* Comeca a simulacao de fcfs */
    clock_t t1 = clock();
    
    while(1) {
        
        float diff = diff_time_ms(clock(), t1);
        i = i % tracefile->length;

        if(diff >= tracefile->trace[i]->t0) {
            tracefile->trace[i]->to_run = 1;
            pthread_create(&tracefile->trace[i]->thread, NULL, worker, tracefile->trace[i]);   

        }
        
        i++;

        /* Todos os processos foram terminados */
        if(finished(tracefile) == 1) break;
    }
}

