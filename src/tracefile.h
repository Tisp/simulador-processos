#ifndef _TRACEFILE_H
#define _TRACEFILE_H

/* Tamanho do buffer */
#define BUFFER 256

#include <pthread.h>

#include "util.h"

/* Estrutura que armazena linhas do tracefile */
typedef struct {
	int finished; /* Verifica se o processo ja terminou */
	int to_run; /* Verifica se a thread precisa ser executada */
	float runtime; /* tempo rodado da thread */
	pthread_t thread; /* Thread */
	float t0; /* Instante de tempo que o processo chega ao sistema */
	char *nome; /* Nome do processo */
	float dt; /* Tempo real de processamento */
	float deadline; /* Tempo limite do processo */
	Timer init_time; /* Guarda o timer inicial */
	float quantum;
} Trace;

/* Estrutura que armazena do tracefile */
typedef struct {
	/* Total de traces */
	int length; 
	/* Array que armazena cada trace */
	Trace **trace;
} Tracefile;

int countlines(FILE *stream);
Tracefile *read_tracefile(const char *filename);
void tracefile_destroy(Tracefile *tracefile);

#endif
