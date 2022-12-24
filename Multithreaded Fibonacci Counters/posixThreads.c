#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#include "threads.h"

unsigned int sleep(unsigned int seconds);
int Fib(int lpParam);

int fibMax;
int number_of_invocations[MAX_THREADS];
/* an array where each element represents an id of the i'th created thread */
int IdThreadArray[MAX_THREADS]; 

/* an array of thread id's */
pthread_t pthreads[MAX_THREADS];
int keepRunning = 1, currentThreadsInProcess = 0;


/* Basing on the id of the thread assigned by CreateThread function, 
determines its index in the IdThreadArray*/
int threadArrayIndex(unsigned int threadId) {
    int i;
    for(i = 0; i < MAX_THREADS; i++) {
        if(pthreads[i] == threadId) {
            return i;	
        }
    }
    return -1;
}

/* Checks if provided argument is a number */
bool checkIfNumber(char* arg, int index) {
	int i, n = strlen(arg);
	/* if it's the last argument, disregard the escape character */
	if(index == 3) {
		n--;
	}

	for(i = 0; i < n; i++) {
		if (arg[i] < '0' || arg[i] > '9') {
			return false;
		}
	}
	return true;
}

void* myThread(void* param){
	int ind;
	int index;
	struct timeval systemTimeBefore, systemTimeAfter;
	int resultingTime, timeMilliAfter, timeMilliBefore;

	index = *((int*) param);
	pthreads[index] = getThreadId();

	currentThreadsInProcess = currentThreadsInProcess + 1;

	gettimeofday(&systemTimeBefore, NULL);
	timeMilliBefore = systemTimeBefore.tv_sec * 1000 + 
systemTimeBefore.tv_usec / 1000;



	for(ind = 1; ind <= fibMax; ind++) {
		Fib(ind);

		/* if the main thread set keepRunning to zero, stop computing 
        fibonacci numbers by exiting the for loop*/
        if(keepRunning == 0) {
            break;
        }
	}

	gettimeofday(&systemTimeAfter, NULL);
	timeMilliAfter = systemTimeAfter.tv_sec * 1000 + 
systemTimeAfter.tv_usec / 1000;
	resultingTime =  timeMilliAfter - timeMilliBefore;


    if(!keepRunning) {
        printf("Thread was terminated. It ran for %d milliseconds"
"  and invoked Fib() %d times \n",
        resultingTime, number_of_invocations[index]);
    } else {
        printf("Thread ran for %d milliseconds and invoked Fib() %d times \n", 
        resultingTime, number_of_invocations[index]);
    }
	
	/* subtract 1 from the global number of running processes */
    currentThreadsInProcess = currentThreadsInProcess - 1;

	pthread_exit(NULL);
}

/* get the id of the current thread*/
unsigned int getThreadId() {
    return pthread_self();
}

int main(int argc, char** argv) {
	int threadsNum, deadline, i, returnCode, *ind;
	
	/* Check for the right number of arguments */
   	if (argc != 4) {
		printf("Not enough arguments: there should be 3 arguments \n");
		exit(1);
    	}

	/* Check for invalid input (if arguments are all numbers)*/
	if(checkIfNumber(argv[1], 1) == false || 
checkIfNumber(argv[2], 2) == false || checkIfNumber(argv[3], 3) == false) {
	printf("Invalid argument: All the arguments have to be numbers \n");
		exit(1);
	}

	threadsNum = atol(argv[1]);  /* number of threads */
    deadline = atol(argv[2]); /* the deadline in seconds */
	fibMax = atol(argv[3]); /* the fibonacci number 
we need to compute in each thread */
	    
	/* printf("partA3 file opened and arguments are: %d %d %d \n",
 * threadsNum, deadline, fibMax); */

	/* Check for invalid input of the Fibonacci number*/
	if(fibMax < 0 || fibMax > 200) {
		printf("Invalid argument: third Fibonacci number"
"  argument has to be between 0 and 200 \n");
		exit(1);
	}

	if(threadsNum > MAX_THREADS) {
	printf("Invalid argument: exceeded the maximum number of threads \n");
		exit(1);
	}

	/* Create the requested number of threads (they 
 * will run right away since dwCreationFlags = 0) */
	for(i = 0; i < threadsNum; i++) {
		ind = malloc(1 * sizeof *ind);
		*ind = i;
	returnCode = pthread_create(&pthreads[i], NULL, myThread, (void*) ind); 
		if(returnCode) {
			printf("ERROR: thread was not created \n");
		}
	}

	sleep(deadline);
	keepRunning = 0;

	/* wait for child threads to exit*/
    while(currentThreadsInProcess != 0){}; 

	pthread_exit(NULL);
}
