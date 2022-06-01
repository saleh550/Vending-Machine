#include "monitor.h"
#include "supplier.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include<time.h>

// function prototypes
void logSupplierAdded (char* czSupplierName, int iSupplySize);
void logSupplierSleep (char* czSupplierName);

void* runSupplier (void* param)
{
  
    char *line=malloc(20);
    int line_number=1;
    char Name[1024];// the supplier's name 
    int Supply_Interval;//how many seconds it will wait after successfuly supply
    int Repetitions;// how many times the supplier will supply unis.
    int Supply_Size;//how many units the supplier will supply at time .

	// open the configuration file
	// read the configuration material from the file
	// supply when we should, sleep when we need to supply but can't
    FILE *newfile;
    char *path= (char *) param;
    newfile=fopen(path,"r");
    char c;
  
    while (fgets(line,20,newfile))//take the data from a files
{



    switch(line_number)
    {
    case 1:
       
    strcpy(Name,line);
    Name[strlen(Name)-1]='\0'; 
        break;
    case 2:Supply_Interval=atoi(line);
        break;
    case 3:Repetitions=atoi(line);
        break;
    case 4:Supply_Size=atoi(line);
        break;
    }  
    line_number++;

   strcpy(line,"");
  


}
    fclose(newfile);    
    line_number=1;
  

     
    while(Repetitions>0)//how many times it is working
    { 
    pthread_mutex_lock(&theMonitor -> lock);// lock itself 
    while((theMonitor->current_units + Supply_Size)>theMonitor->max_units)// if the sum smaller at the max
        {
        logSupplierSleep(Name);// call a function that print a message about sleeping 
        pthread_cond_wait(&theMonitor->cond,&theMonitor->lock);//go tp sleep until return  signal
        }
  
    
    theMonitor->current_units+=Supply_Size;// add specifice size to current units
    logSupplierAdded(Name,Supply_Size);//call a function that print a message about added.
    pthread_cond_signal(&theMonitor->cond); // sending signal to condition that is sleeping
    
    pthread_mutex_unlock(&theMonitor -> lock);//unlock it self
    sleep(0);// go to sleep "supply_interval" socends
    Repetitions--;
    
    } 
   
     
}

/* Adds a log line that the supplier added new units to the machine
	Parameters:
	theMonitor - a Monitor struct
	czSupplierName - the name of the supplier
	iSupplySize - the number of units supplied
*/
void logSupplierAdded (char* czSupplierName, int iSupplySize)
{
	// print a log line about supplying
    time_t t=time(NULL);
    time(&t);
    char *fullT=ctime(&t);
    if(fullT[strlen(fullT)-1]=='\n')fullT[strlen(fullT)-1]='\0';
   // printf("%s",fullT);
    printf("%s %s supplied %d units . Stock after = %d.\n",fullT,czSupplierName,iSupplySize,theMonitor->current_units);
}

/* Adds a log line that the supplier is going to sleep
	Parameters:
	czSupplierName - the name of the supplier
*/
void logSupplierSleep (char* czSupplierName)
{
	time_t t=time(NULL);
    time(&t);
    char *fullT=ctime(&t);
    fullT[strlen(fullT)-1]='\0';
    printf("%s %s going to sleep .\n",fullT,czSupplierName);
}
