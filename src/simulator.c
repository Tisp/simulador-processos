#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#include "tracefile.h"
#include "output.h"
#include "prime.h"
#include "util.h"
#include "fcfs.h"

int debug;

int main(int argc, char **argv) {


	/* Verifica se o numero de argumentos e o correto */
	if(argc < 4) {
		printf("Este simulador aceita no minimo 3 argumentos e no maximo 4 argumetos \n");
		exit(-1);
	}


	/* Numero do escalonador */
	int scheduling = atoi(argv[1]);

	/* Nome do arquivo de trace */
	const char *input_file = argv[2];

	/* Nome do arquivo de output*/
	const char *output_file = argv[3];

	/* Verifica se foi passado numero do escalonador correto */
	if(scheduling < 0 || scheduling > 3) {
		printf("Valores incompativeis para tipo de escalonador, utilize [1, 2, 3] \n");
		exit(-1);
	}
	
	/* Habilitando modo debug */
	if(argc > 4 && strcmp("d", argv[4]) == 0) {
		debug = 1;
	}
		

	/* Le o arquivo e cria uma estrutura de tracefile */
	Tracefile *tracefile = read_tracefile(input_file);

	/* Inicia o arquivo de output */
	new_output_file(output_file);


	switch(scheduling) {
		case 1: fcfs(tracefile); break;
		case 2: printf("Ainda em faze de implementacao"); break;
		case 3: printf("Ainda em faze de implementacao"); break; 
	}
	

	

	// /* Guarda os valores do relogio */
	// clock_t t1, t2;

	// int i  = 0;

	// /* Numero de cores no computador */
	// int ncores = n_cores();

	// /* Uma thread para cada core */
	// pthread_t thread[ncores];

	// /* Um lock para cada thread */
	// pthread_mutex_t locks[ncores];	

	// /* Captura primeiro time */
	// t1 = clock();
	// t2 = clock();

	// while(i < tracefile->length) {
		
	// 	float diff_t = diff_time_s(t2, t1);

	// 	//Verifica se precisa iniciar o processo
	// 	if(tracefile->trace[i]->t0 <= diff_t) {
			
	// 		printf("ja perdi :%f s\n", diff_t); 
	// 		printf("%f ", tracefile->trace[i]->t0);
	// 		printf("%s ", tracefile->trace[i]->nome);
	// 		printf("%f ", tracefile->trace[i]->dt);
	// 		printf("%f\n", tracefile->trace[i]->deadline);
	// 		i++;
	// 	}

	// 	t2 = clock();
	// }

	/* Libera memoria do tracefile */
	tracefile_destroy(tracefile);
	
	return 0;

}
