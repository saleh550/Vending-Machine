#ifndef MONITOR_H
#define MONITOR_H

#include <pthread.h>

typedef struct {
	// define the parts of the monitor here
    int current_units;
    int consumed_units;
    int max_units;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} monitor_t;

monitor_t *theMonitor;
#endif
