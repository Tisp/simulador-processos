#ifndef _THREAD_H
#define _THREAD_H

extern int occupied_cores;

void *worker(void *args);
int finished(Tracefile *tracefile);

#endif
