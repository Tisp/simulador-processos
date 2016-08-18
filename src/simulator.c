#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "tracefile.h"
#include "prime.h"
#include "util.h"

int main(int argc, char **argv) {

	/*
	TODO:
		Verificar quantidas de argumentos
		possiveis de entrada 
	*/

	/* Nome do arquivo de trace */
	const char *file = argv[1];

	/*Le o arquivo e cria uma estrutura de tracefile */
	Tracefile *tracefile = read_tracefile(file);

	clock_t t1, t2;

	int i  = 0;

	/* Captura primeiro time */
	t1 = clock();
	t2 = clock();

	while(i < tracefile->length) {
		
		float diff_t = diff_time_ms(t2, t1);

		//Verifica se precisa iniciar o processo
		if(tracefile->trace[i]->t0 <= diff_t) {
			
			printf("ja perdi :%f s\n", diff_t); 
			printf("%f ", tracefile->trace[i]->t0);
			printf("%s ", tracefile->trace[i]->nome);
			printf("%f ", tracefile->trace[i]->dt);
			printf("%f\n", tracefile->trace[i]->deadline);
			i++;
		}

		t2 = clock();
	}

	/* Libera memoria do tracefile */
	tracefile_destroy(tracefile);
	
	return 0;

}
