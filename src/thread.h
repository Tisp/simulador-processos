#ifndef _THREAD_H
#define _THREAD_H

extern int occupied_cores;
extern int degub;

void *worker(void *args);
int finished(Tracefile *tracefile);

#endif
