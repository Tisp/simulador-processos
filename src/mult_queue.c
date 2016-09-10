#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


#include "tracefile.h"
#include "prime.h"
#include "util.h"
#include "mult_queue.h"
#include "output.h"


int debug;
pthread_mutex_t lock;
int *occupied_cores;
int preemption = 0;


/* Novo worker para mult queue */
void *worker_mult_queue(void *args) {

    Trace *trace = args;
    float diff;
    int my_core = 0;
    Timer start, finish;

    get_time(&start);

    /* Espera para ser marcada para rodar */
    LOOP:while(trace->to_run == 0) {
            usleep(10000);
    }

    /* Inicio do processamento */
     pthread_mutex_lock(&lock);
     my_core = find_free_core();
     pthread_mutex_unlock(&lock);


     /* Espera liberar cpu */
     if(my_core == -1) goto LOOP;
     
     pthread_mutex_lock(&lock);
     occupied_cores[my_core] = 1;
     pthread_mutex_unlock(&lock);
    
    if(debug) 
        fprintf(stderr, "Processo %s usando CPU %d\n", trace->nome, my_core);
    
    while(trace->runtime <= trace->dt) {

        /* Verifica se precisa haver preepcao */
        if(trace->runtime >= trace->quantum) {
            pthread_mutex_lock(&lock);
            preemption++;
            occupied_cores[my_core] = 0;
            trace->to_run = 0;
            trace->quantum += QUANTUM;
            pthread_mutex_unlock(&lock);
            goto LOOP;
        }

       //printf("Processo %s [%lf, %lf] falta: %lf\n", trace->nome, trace->dt, trace->runtime,(trace->dt - trace->runtime));
        is_prime(11587); /* Gasta processamento */
        get_time(&finish);
        diff = diff_time_s(finish, start);
        trace->runtime = diff;
    }

     if(debug)
        fprintf(stderr, "Processo %s finalizado, liberando CPU %d\n", trace->nome, my_core);
    

  // pthread_mutex_lock(&lock);
  pthread_mutex_lock(&lock);
  occupied_cores[my_core] = 0;
  pthread_mutex_unlock(&lock);

  get_time(&finish);
  diff = diff_time_s(finish, trace->init_time);
  write_output(trace->nome, diff, (diff - trace->t0));

  trace->finished = 1;
  float total = (trace->deadline - trace->t0) - trace->runtime;
  if(total < 0.)
	printf("Cumpriu\n");
  
  pthread_exit(&trace->thread);
   

  return NULL;


}

/* Multiplas filas */
void mult_queue(Tracefile *tracefile) {
    
    int i = 0;
    float diff;

    for(i = 0; i < tracefile->length; i++)
        tracefile->trace[i]->quantum = QUANTUM;

    i = 0;

    /* Comeca a simulacao de fcfs */
    Timer start, finish;
    get_time(&start);
    
    while(1) {
        
        get_time(&finish);
        diff = diff_time_s(finish, start);
	    
        i = i % tracefile->length;
        
        if(diff >= tracefile->trace[i]->t0 && tracefile->trace[i]->to_run == 0 && find_free_core() >= 0) {
            tracefile->trace[i]->to_run = 1;
            tracefile->trace[i]->init_time = start;
            if(!tracefile->trace[i]->thread)
                pthread_create(&tracefile->trace[i]->thread, NULL, worker_mult_queue, (void *)tracefile->trace[i]);   
            
        }

        i++;
        usleep(1000);

        /* Todos os processos foram terminados */
        if(finished(tracefile) == 1) break;
    }

    write_contexts(preemption);

}

