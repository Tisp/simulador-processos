#ifndef _THREAD_H
#define _THREAD_H

extern int degub;

void *worker(void *args);
int finished(Tracefile *tracefile);

#endif
