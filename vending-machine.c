#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <ctype.h>
#include "monitor.h"
#include "supplier.h"
#include "consumer.h"
#include<time.h>
#include<string.h>

struct thread_info {
	pthread_t thread_id;
	int thread_num;
	char *argv_string;
};

// initialize the monitor with the standard parameters
int monitor_init (monitor_t *monitor, int maxCount)
{
	// setup the monitor with the values needed
    monitor->current_units=0;
    monitor->max_units=maxCount;
    monitor->consumed_units=0;
    pthread_mutex_init(&monitor -> lock,0);
	pthread_cond_init(&monitor -> cond,NULL);
    
	
	// all good
	return 0;
}

// print out how to use the program
void showUsage()
{
	printf("Usage: vending maxUnits Supplier1file Supplier2file Supplier3file Consumer1file Consumer2file Consumer3file\n");
}

int main(int argc, char* args[])
{
	int maxCount = 0;

	// check that we have the parameters we need
	if (argc < 8)
	{
		showUsage();
		return -1;
	}
	
	// parse the parameters
	maxCount = atoi(args[1]);
	char* supplier1Config = args[2];
	char* supplier2Config = args[3];
	char* supplier3Config = args[4];
	char* consumer1Config = args[5];
	char* consumer2Config = args[6];
	char* consumer3Config = args[7];	
	
	// initiate the monitor with malloc
    theMonitor = (monitor_t*) malloc(sizeof(monitor_t));
	monitor_init(theMonitor,maxCount);

	// create one thread for each of the six elements - 3 suppliers, 3 consumers
    struct thread_info *threadInfo;
	threadInfo = calloc(6, sizeof(struct thread_info));
	// run them
	pthread_create(&threadInfo[0].thread_id, NULL, &runSupplier, supplier1Config);
	pthread_create(&threadInfo[1].thread_id, NULL, &runSupplier, supplier2Config);
	pthread_create(&threadInfo[2].thread_id, NULL, &runSupplier, supplier3Config);
	pthread_create(&threadInfo[3].thread_id, NULL, &runConsumer, consumer1Config);
    pthread_create(&threadInfo[4].thread_id, NULL, &runConsumer, consumer2Config);
    pthread_create(&threadInfo[5].thread_id, NULL, &runConsumer, consumer3Config);

    void *result; // the thread execution result
	pthread_join(threadInfo[0].thread_id, &result); // wait for the children
	pthread_join(threadInfo[1].thread_id, &result); // wait for the children
	pthread_join(threadInfo[2].thread_id, &result); // wait for the children
	pthread_join(threadInfo[3].thread_id, &result); // wait for the children
	pthread_join(threadInfo[4].thread_id, &result); // wait for the children
    pthread_join(threadInfo[5].thread_id, &result); // wait for the children
	
    
    time_t t=time(NULL);
    time(&t);
    char *fullT=ctime(&t);
    if(fullT[strlen(fullT)-1]=='\n')fullT[strlen(fullT)-1]='\0';
    printf("%s all threads completed Total consumed =%d final stock=%d .\n",fullT,theMonitor->consumed_units,theMonitor->current_units);
    free(theMonitor);
    free(threadInfo);
	exit(0);
}


