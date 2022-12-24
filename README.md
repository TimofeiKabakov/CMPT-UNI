# CMPT-UNI
  Here are some valuable and essential programs I wrote for some of my assignments/projects at the university:

### List Library in C
  This is an implementation of a list library written in C where each list is of homogenous data type. This library does not use any form of dynamic allocation, only static.
  
  **In order to compile the library**, run "make" in the command prompt.

  Refer to the design document for more information and detail.

### Multithreaded Fibonacci Counters
  Launch multiple threads that perform the same function in parallel until a deadline without synchronization between the threads. 

  Parameters to provide to run the program:
    1. number of child threads to launch
    2. the time these threads should run for
    3. the maximum integer

  If the time occurs before child threads are done calculating the Fibonacci sequence, they are signalled to exit.

  I provide two implementations of this program: one with Windows threads and one with Posix threads.
  
  **To run the program:**
  1. run "make" in the command prompt.
  2. 2. create a .txt file where on each line, you indicate the input for one execution of the program.
  3. run "./bh.bash <winThreads/posixThreads> < <path-to-the-txt-input-file>". If you are on Windows, indicate "winThreads." If on Linux, indicate "posixThreads." The bash script will run the appropriate executable with an input read line by line from the .txt file you created.

  Refer to the design document for more information and detail.

### Monitors with UBC pthreads IPC
  Implementation of monitors in C using inter-process communication with the help of UBC pthreads.
  
  Refer to the design document for more information and detail.
  
  /* TODO: switch from UBC pthreads to Posix threads */
  
### Chat program using RT Threads Semaphores
  A chat program that enables someone at one terminal to communicate with another user at another terminal using the UDP transport protocol and the RT threads package.
  
  Refer to the design document for more information and detail.
  
  /* TODO: switch from RT threads to Posix threads */
  

