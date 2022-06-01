#include "monitor.h"
#include "consumer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// function prototypes
void logConsumerRemoved (char* czConsumerName, int iConsumeSize);
void logConsumerSleep (char* czConsumerName);

void* runConsumer (void* param)
{
	// open the configuration file
	// read the configuration material from the file
	// consume when we should, sleep when we need to consume but can't
}

/* Adds a log line that the consumer removed a unit from the machine
	Parameters:
	theMonitor - a Monitor struct
	czConsumerName - the name of the consumer
	iConsumeSize - the number of units consumed
*/
void logConsumerRemoved (char* czConsumerName, int iConsumeSize)
{
	// print a log line about consuming
}

/* Adds a log line that the consumer is going to sleep
	Parameters:
	czConsumerName - the name of the consumer
*/
void logConsumerSleep (char* czConsumerName)
{
	// print a log line about going to sleep
}
