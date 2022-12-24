#include <stdio.h>
#include "threads.h"

unsigned int arrayInd;

int Fib(int lpParam) {
    
    /* Determine thread's index in the number_of_invocations array*/
    arrayInd = threadArrayIndex(getThreadId()); 

    /* printf("Array index is %u \n", arrayInd); */

    /* Check if the returned value is inside the bounds*/ 
    if(arrayInd <= 20) {
        number_of_invocations[arrayInd]++;
    }

    if(lpParam == 0) {
        return 0;
    } else if(lpParam == 1){
        return 1;
    }

    
    return Fib(lpParam - 1) + Fib(lpParam - 2);
}
