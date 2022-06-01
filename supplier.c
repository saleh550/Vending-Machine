#include "monitor.h"
#include "supplier.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// function prototypes
void logSupplierAdded (char* czSupplierName, int iSupplySize);
void logSupplierSleep (char* czSupplierName);

void* runSupplier (void* param)
{
	// open the configuration file
	// read the configuration material from the file
	// supply when we should, sleep when we need to supply but can't
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
}

/* Adds a log line that the supplier is going to sleep
	Parameters:
	czSupplierName - the name of the supplier
*/
void logSupplierSleep (char* czSupplierName)
{
	// print a log line about going to sleep
}
