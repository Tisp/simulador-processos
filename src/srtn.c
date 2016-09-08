#include <stdio.h>
#include <pthread.h>
#include <time.h>


#include "tracefile.h"
#include "prime.h"
#include "util.h"
#include "thread.h"
#include "output.h"


/* Percorre a lista de trace, verifica qual esta rodando e compara o tempo */
int shortest(Tracefile *tracefile, int id, float runtime) {

    int candidate = -1;
    int i;

    for(i = 0; i < tracefile->length; i++) {
        
        if(i == id) continue; /* Nao compara com ele mesmo  */

        /* Verifica se esta rodando  e se ainda nao terminou */
        if(tracefile->trace[i]->to_run == 1 && tracefile->trace[i]->finished == 0) {
            if((tracefile->trace[i]->dt - tracefile->trace[i]->runtime) > runtime) {
                candidate = i; /* Possivel candidato a ser substituido */
            }
        }
    }

    return candidate;
}


/* Shortest Remaining Time Next */
void srtn(Tracefile *tracefile) {

    int i = 0;
    int preemption = 0;
    float diff;
           
    /* Comeca a simulacao de fcfs */
    Timer start, finish;
    get_time(&start);
    
    while(1) {
        
  
        get_time(&finish);
        diff = diff_time_s(finish, start);
        i = i % tracefile->length;

        if(diff >= tracefile->trace[i]->t0 && tracefile->trace[i]->to_run == 0) {

            /* Se ainda tiver cores livres pode rodar */
            if(find_free_core() != -1) {

                tracefile->trace[i]->to_run = 1;
                tracefile->trace[i]->init_time = start;
                if(!tracefile->trace[i]->thread)
                    pthread_create(&tracefile->trace[i]->thread, NULL, worker, tracefile->trace[i]); 

            } else {
                
                 int sh = shortest(tracefile, i, tracefile->trace[i]->dt);
                // printf("Achei o candidado %d, total de cores %d \n", sh, find_free_core());    
                /* Nao achou candidatos */
                if(sh < 0) {
                    continue;

                } else {
               //     printf("Me falaram para parar de rodar agora");
                    preemption++; /* houve preepcao */
                    tracefile->trace[sh]->to_run = 0; /* Para o candidado mais demorado */
                    tracefile->trace[i]->to_run = 1; /* Coloca o novo para rodar */
                    tracefile->trace[i]->init_time = start;
                    
                    if(!tracefile->trace[i]->thread)
                        pthread_create(&tracefile->trace[i]->thread, NULL, worker, tracefile->trace[i]);  
                }
            }
  
        }

        i++;
        usleep(1000);

        /* Todos os processos foram terminados */
        if(finished(tracefile) == 1) break;
       
    }

    write_contexts(preemption);
}

