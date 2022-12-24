#define MAX_THREADS 20

extern int number_of_invocations[MAX_THREADS];
int threadArrayIndex(unsigned int threadId);
unsigned int getThreadId();
int Fib(int lpParam);