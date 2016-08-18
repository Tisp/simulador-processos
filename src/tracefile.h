#ifndef _TRACEFILE_H
#define _TRACEFILE_H

/* Tamanho do buffer */
#define BUFFER 256

/* Estrutura que armazena linhas do tracefile */
typedef struct {
	float t0;
	char *nome;
	float dt;
	float deadline;
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
