#include <stdio.h>
#include <windows.h>
#include "threads.h"

int number_of_invocations[MAX_THREADS];
int keepRunning = 1, currentThreadsInProcess = 0;

/* an array where each element represents an id of the i'th created thread */
unsigned int IdThreadArray[MAX_THREADS]; 

/* Basing on the id of the thread assigned by CreateThread function, 
determines its index in the IdThreadArray*/
int threadArrayIndex(unsigned int threadId) {
    int i;
    for(i = 0; i < MAX_THREADS; i++) {
        if(IdThreadArray[i] == threadId) {
            return i;
        }
    }
    return -1;
}

/* Checks if provided argument is a number */
boolean checkIfNumber(char* arg, int index) {
    int i, n = strlen(arg);
    /* if it's the last argument, disregard the escape character */
    if(index == 3) {
        n--;
    }

    for(i = 0; i < n; i++) {
        if (arg[i] < '0' || arg[i] > '9') {
            return FALSE;
        }
    }
    return TRUE;
}

/* A function that is going to check for keepRunning variable 
and call Fib function*/
DWORD WINAPI myFunct(LPVOID Param){
    LPINT numFib = (LPINT) Param; /* cast LPVOID to LPINT type */
    SYSTEMTIME systemTimeBefore, systemTimeAfter;
    int ind, resultingTime;

    /* add 1 to the global number of running processes */
    currentThreadsInProcess = currentThreadsInProcess + 1;
    GetSystemTime(&systemTimeBefore);

    for(ind = 1; ind <= *numFib; ind++) {
        Fib(ind);

        /* if the main thread set keepRunning to zero, stop computing 
        fibonacci numbers by exiting the for loop*/
        if(keepRunning == 0) {
            break;
        }
    }  

    GetSystemTime(&systemTimeAfter);
resultingTime = systemTimeAfter.wMilliseconds - systemTimeBefore.wMilliseconds;
    /* Check if the time in milliseconds was 
 * negative because of the switch of the seconds*/
    if(resultingTime < 0) {
        resultingTime = resultingTime * -1;
    }

    if(!keepRunning) {
        printf("Thread was terminated. It ran for %d milliseconds "
" and invoked Fib() %d times \n",
        resultingTime, number_of_invocations[threadArrayIndex(getThreadId())]);
    } else {
        printf("Thread ran for %d milliseconds and invoked Fib() %d times \n", 
        resultingTime, number_of_invocations[threadArrayIndex(getThreadId())]);
    }
    
    /* subtract 1 from the global number of running processes */
    currentThreadsInProcess = currentThreadsInProcess - 1;
    return 0;
}

/* get the id of the current thread*/
unsigned int getThreadId() {
    return GetCurrentThreadId();
}

int main(int argc, char** argv){
    HANDLE HandleT[MAX_THREADS]; /* an array of thread handles  */
    int threadsNum, deadline, fibMax, i;

    /* Check for the right number of arguments */
    if (argc != 4) {
        printf("Not enough arguments: there should be 3 arguments \n");
        exit(1);
    }

    /*printf("partA1 file opened and arguments are: %d %d %d \n", 
 * threadsNum, deadline, fibMax);*/

    /* Check for invalid input (if arguments are all numbers)*/
    if(checkIfNumber(argv[1], 1) == FALSE || 
checkIfNumber(argv[2], 2) == FALSE || 
checkIfNumber(argv[3], 3) == FALSE) {
        printf("Invalid argument: All the arguments have to be numbers \n");
        exit(1);
    }

    threadsNum = atol(argv[1]);  /* number of threads */
    deadline = atol(argv[2]); /* the deadline in seconds */
    fibMax = atol(argv[3]); /* the fibonacci number we need 
to compute in each thread */
    
    /* Check for invalid input of the Fibonacci number*/
    if(fibMax < 0 || fibMax > 200) {
        printf("Invalid argument: third Fibonacci number"
"  argument has to be between 0 and 200 \n");
        exit(1);
    }

    /* Check for invalid input of the Fibonacci number*/
    if(MAX_THREADS < threadsNum) {
        printf("Invalid argument: the number of threads can not exceed the "
" maximum number of threads allowed, which is %d \n", (int) MAX_THREADS);
        exit(1);
    }

    /* Create the requested number of threads (
    * they will run right away since dwCreationFlags = 0) */
    for(i = 0; i < threadsNum; i++) {
        HandleT[i] = CreateThread(NULL, 0, myFunct, (LPVOID) &fibMax, 0, (LPDWORD) &IdThreadArray[i]);
    }

    /* the deadline provided ny the user * is in seconds -> convert to milliseconds*/
    Sleep(deadline * 1000);
    keepRunning = 0;

    /* wait for child threads to exit*/
    while(currentThreadsInProcess != 0){}; 

    /* Close all the Handles for the initiated threads */
    for(i = 0; i < threadsNum; i++) {
        CloseHandle(HandleT[i]);
    }

    return 0;
}
