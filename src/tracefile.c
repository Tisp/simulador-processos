#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracefile.h"


/* Formato padrao do arquivo de entrada */
const char *format = "%f %s %f %f";

Tracefile *read_tracefile(const char *filename) {

	FILE *fp;
	fp = fopen(filename, "r+");

	if(!fp) {
		printf("Erro ao abrir o arquivo");
		exit(-1);
	}

	Tracefile *tracefile;
	int length = countlines(fp);
	int i = 0;
	float t0, dt, deadline;
	char nome[BUFFER];

	tracefile = (Tracefile *) malloc(sizeof(Tracefile));
	tracefile->length = length;
	tracefile->trace  = (Trace **) malloc(sizeof(Trace **) * length);

	for(i = 0; i < length; i++) 
		tracefile->trace[i] = (Trace *) malloc(sizeof(Trace));
		 
	
	i = 0;
	
	while(fscanf(fp, format, &t0, &nome, &dt, &deadline) == 4) {

		tracefile->trace[i]->t0 = t0;
		tracefile->trace[i]->nome = strdup(nome);
		tracefile->trace[i]->dt = dt;
		tracefile->trace[i]->deadline = deadline;
		tracefile->trace[i]->finished = 0;
		tracefile->trace[i]->to_run = 0;
		tracefile->trace[i]->thread = NULL;
		tracefile->trace[i]->runtime = 0;
		
		i++;
	}

	fclose(fp);
	return tracefile;
}

int countlines(FILE *stream) {
	
	int lines = 0;
	int t0, dt, deadline;
	char nome[256];

	while(fscanf(stream, format, &t0, &nome, &dt, &deadline) == 4) {
		lines++;
	}

	/* Retorna o ponteiro para comeco do arquivo */
	fseek(stream, 0, SEEK_SET);

	/* Retorna o ponteiro para o comeco do arquivo */
	return lines;	
}


/* Libera memoria */
void tracefile_destroy(Tracefile *tracefile) {

	int i;

	for(i = 0; i < tracefile->length; i++) {
		free(tracefile->trace[i]->nome);
		free(tracefile->trace[i]);
	}

	free(tracefile->trace);
	free(tracefile);
}
