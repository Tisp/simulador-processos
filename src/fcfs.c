#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


#include "tracefile.h"
#include "prime.h"
#include "util.h"
#include "thread.h"
#include "output.h"

int debug;

/* First-Come First-Served */

void fcfs(Tracefile *tracefile) {

    int i = 0;
    float diff;

    /* Comeca a simulacao de fcfs */
    Timer start, finish;
    get_time(&start);
    
    while(1) {
        
        get_time(&finish);
        diff = diff_time_s(finish, start);
	    
        i = i % tracefile->length;
	    //printf("%lf, %lf %d \n", diff, tracefile->trace[i]->t0, (diff >= tracefile->trace[i]->t0));
        
        if(diff >= tracefile->trace[i]->t0 && tracefile->trace[i]->to_run == 0 && find_free_core() >= 0) {
            tracefile->trace[i]->to_run = 1;
            tracefile->trace[i]->init_time = start;
            pthread_create(&tracefile->trace[i]->thread, NULL, worker, (void *)tracefile->trace[i]);   
            i++;
        }

        usleep(1000);

        /* Todos os processos foram terminados */
        if(finished(tracefile) == 1) break;
    }

    write_contexts(0);

}

