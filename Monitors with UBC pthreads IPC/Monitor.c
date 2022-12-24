#include <stdio.h>
#include <standards.h>
#include <os.h>

#include "list.h"
#include "Monitor.h"

int monOccupied = 0;

PID ServerThreadID;

LIST *enterQList, *urgentQList;
LIST **cvLists;

PROCESS serverFunct(){
    PID pidOriginator;
    PID* threadId;
    int lenMessage;
    char *message;
    int CV;

    char messageEnter[] = "MonEnter";
    char messageWait[] = "MonWait";
    char messageLeave[] = "MonLeave";
    /*char messageSignal[] = "MonSignal";*/

  	while(1) {
      /*asymmetric direct communication*/
      message = (char *) Receive(&pidOriginator, &lenMessage);

      /* if we receive a message that a thread wants to enter the monitor */
      if(strcmp(message, messageEnter) == 0) {
        /* allocate memory for a new thread id which will
         later be put in the list */
        if(monOccupied == 1) {
            threadId = (PID*) malloc(sizeof(PID));
            *threadId = pidOriginator;
            ListAppend(enterQList, threadId);
        } else {
            monOccupied = 1;
            Reply(pidOriginator, NULL, 0);
        }
      } else if (strcmp(message, messageLeave) == 0) {
           /* if we receive a message that a thread wants 
           to leave the monitor */
          Reply(pidOriginator, NULL, 0);

          if(ListCount(urgentQList) != 0) {
              ListFirst(urgentQList);
              threadId = (PID*) ListRemove(urgentQList);
              Reply(*threadId, NULL, 0);
              free(threadId);
          } else if (ListCount(enterQList)  != 0) {
              ListFirst(enterQList);
              threadId = (PID*) ListRemove(enterQList);
              Reply(*threadId, NULL, 0);
              free(threadId);
          } else {
              monOccupied = 0;
          }
      } else if(strcmp(message, messageWait) == 0) {
        /* if we receive a message that a thread wants to 
        wait for a conditional variable */ 
        CV = lenMessage;

        threadId = (PID*) malloc(sizeof(PID));
        *threadId = pidOriginator;
        ListAppend(cvLists[CV], threadId);

        if(ListCount(urgentQList) != 0) {
            ListFirst(urgentQList);
            threadId = (PID*) ListRemove(urgentQList);
            Reply(*threadId, NULL, 0);
            free(threadId);
        } else if (ListCount(enterQList) != 0) {
            ListFirst(enterQList);
            threadId = (PID*) ListRemove(enterQList);
            Reply(*threadId, NULL, 0);
            free(threadId);
        } else {
            monOccupied = 0;
        }

      } else { 
        /* if we receive a message that a thread wants to 
        signal the conditional variable */
        CV = lenMessage;
        if(ListCount(cvLists[CV]) != 0) {
            ListFirst(cvLists[CV]);
            threadId = (PID*) ListRemove(cvLists[CV]);

            Reply(*threadId, NULL, 0);
            free(threadId);

            threadId = (PID*) malloc(sizeof(PID));
            *threadId = pidOriginator;
            ListAppend(urgentQList, threadId);
        } else {
          Reply(pidOriginator, NULL, 0);
        }
      }
    }
}

void MonServer(int numCond){
  int i;

  /* create the server thread */
  ServerThreadID = Create((void(*)()) serverFunct, 16000, 
   "param", NULL, HIGH, USR);
  if (ServerThreadID == PNUL) {
    printf("The server thread was not created");
    return;
  }

  /* initialize the queues (lists) */
  enterQList = ListCreate();
  urgentQList = ListCreate();
  cvLists = (LIST**) malloc(sizeof(LIST*) * numCond);
  for(i = 0; i < numCond; i++) {
      cvLists[i] = ListCreate();
  }
}

void MonEnter(){
  char message[] = "MonEnter";
  int len = 0;
  Send(ServerThreadID, (void *) message, &len);
}

void MonLeave(){
  char message[] = "MonLeave";
  int len = 0;
  Send(ServerThreadID, (void *) message, &len);
}

void MonWait(int CV){
  int len = CV;
  char message[] = "MonWait";
  Send(ServerThreadID, (void *) message, &len);
}

void MonSignal(int CV){
  int len = CV;
  char message[] = "MonSignal"; 
  Send(ServerThreadID, (void *) message, &len);
}
