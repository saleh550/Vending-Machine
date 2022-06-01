#ifndef MONITOR_H
#define MONITOR_H

#include <pthread.h>

typedef struct {
	// define the parts of the monitor here
    int current_amount , max_amount;    //amount to save how many units now in the machine
    pthread_mutex_t lock;
	pthread_cond_t cond;
} monitor_t;

monitor_t *theMonitor;
#endif
