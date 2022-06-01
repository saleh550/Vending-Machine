#include "monitor.h"
#include "consumer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include<time.h>

// function prototypes
void logConsumerRemoved (char* czConsumerName, int iConsumeSize);
void logConsumerSleep (char* czConsumerName);

void* runConsumer (void* param)
{
    char Name[1024];
    int Consumption_Interval;
    int Repetitions;
    int Consume_Size;
    char *line=malloc(20);
    int line_number=1;
	// open the configuration file
	// read the configuration material from the file
	// consume when we should, sleep when we need to consume but can't
      FILE *newfile;
    char *path= (char *) param;
    newfile=fopen(path,"r");
    char c;
 
    while (fgets(line,20,newfile))
{



    switch(line_number)
    {
    case 1:strcpy(Name,line);
    Name[strlen(Name)-1]='\0'; 
        break;
    case 2:Consumption_Interval=atoi(line);
        break;
    case 3:Repetitions=atoi(line);
        break;
    case 4:Consume_Size=atoi(line);
        break;
    }  
    line_number++;

   strcpy(line,"");
  


}
    fclose(newfile);    
    line_number=1;
   // printf("name=%s \n inerval= %d \n rep=%d \n size=%d \n",Name,Consumption_Interval, Repetitions,Consume_Size);
   
    while(Repetitions>0)
    {
     pthread_mutex_lock(&theMonitor -> lock);
        while((theMonitor->current_units-Consume_Size)<0)
        {
        logConsumerSleep(Name);
        pthread_cond_wait(&theMonitor->cond,&theMonitor->lock);
        }
        
        theMonitor->current_units-=Consume_Size;
        theMonitor-> consumed_units+=Consume_Size;
        logConsumerRemoved(Name,Consume_Size);
        pthread_cond_signal(&theMonitor->cond);
      
        pthread_mutex_unlock(&theMonitor -> lock);
        sleep(0);
        Repetitions--;
    }
   
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
    time_t t=time(NULL);
    time(&t);
    char *fullT=ctime(&t);
    if(fullT[strlen(fullT)-1]=='\n')fullT[strlen(fullT)-1]='\0';
    printf("%s",fullT);
    printf(" %s removed %d units Total consumed = %d. Stock after = %d.\n",czConsumerName,iConsumeSize,theMonitor->consumed_units,theMonitor->current_units);
    
}

/* Adds a log line that the consumer is going to sleep
	Parameters:
	czConsumerName - the name of the consumer
*/
void logConsumerSleep (char* czConsumerName)
{
	time_t t=time(NULL);
    time(&t);
    char *fullT=ctime(&t);
    if(fullT[strlen(fullT)-1]=='\n')fullT[strlen(fullT)-1]='\0';
    printf("%s %s going to sleep .\n",fullT,czConsumerName);
    
}
