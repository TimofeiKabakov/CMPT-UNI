#include <stdio.h>
#include <rtthreads.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <RttCommon.h>
#include <time.h>

#include "list.h"

#define BACKLOG 10
#define MAXSLEEPTIME 2
#define MAXBUFLEN 100

RttThreadId keyInputThread, netSendThread, printThread, receiverFunctThread;
RttSem printQueueSem, sendMessageSem, mutexSend, mutexReceive;
RttSchAttr attributes;
RttTimeValue rttTimeVar;
fd_set in, out;

int port1, port2, outSock, inSock, testin, ioctlOutPut, var = 1;
int a, b, c, d;
int status;
int yes = 1;
struct addrinfo hints;
struct addrinfo *servinfo, *p;
size_t testlen;

char *portString, *serverPortString;
char *name1;

/* sockets */
int sockfd, numbytes, sendResult;
struct sockaddr_storage *destination_addr;
struct sockaddr_storage their_addr;
socklen_t their_addr_len, destination_addr_len;

LIST *printQueue, *sendMessage;

/* Checks if provided argument is a number */
bool checkIfNumber(char* arg, int index) {
    int i, n = strlen(arg);
    /* if it's the last argument, 
    disregard the escape character */
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

/* sets up the socket for the LOCAL MACHINE */
void setUpSocket(void *arg) {
  portString = (char *) arg;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  /* port number here has to be a string, so I just pass argv[1] (MYPORT) */
  if ((status = getaddrinfo(NULL, portString, &hints, &servinfo)) != 0){
    fprintf(stderr, "getaddrinfo error: %s \n", gai_strerror(status));
    exit(1);
  }

  /* go through all the results in servinfo*/    
  for(p = servinfo; p != NULL; p = p -> ai_next) {
    if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, 
    servinfo->ai_protocol)) == -1) {
      perror("receiver: socket");
      continue;
    }

    if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("receiver: bind");
      continue;
    }

    break;
  }
  freeaddrinfo(servinfo);

  if(p == NULL) {
    fprintf(stderr, "receiver: failed to bind \n");
    exit(1);
  }
}

RTTTHREAD senderFunct(void *arg){
  int sockfdServ;
  int statusServ;
  struct addrinfo hints2;
  struct addrinfo *servinfo2, *iter;
  char *rMessage;
  serverPortString = (char *) arg;

  memset(&hints2, 0, sizeof hints2);
  hints2.ai_family = AF_INET;
  hints2.ai_socktype = SOCK_DGRAM;
  /* port number here has to be a string, so I just pass argv[1] (MYPORT) */
  if ((statusServ = getaddrinfo(name1, serverPortString, 
  &hints2, &servinfo2)) != 0){
    fprintf(stderr, "getaddrinfo error in senderFunct: %s \n", 
    gai_strerror(statusServ));
    exit(1);
  }

  for(iter = servinfo2; iter != NULL; iter = iter -> ai_next) {
    if((sockfdServ = socket(servinfo2->ai_family, servinfo2->ai_socktype,
    servinfo2->ai_protocol)) == -1) {
      perror("talker: socket");
      continue;
    }

    break;
  }

  if(iter == NULL) {
    fprintf(stderr, "talker: failed to create a socket \n");
    exit(1);
  }

  while(1) {

    RttP(sendMessageSem);
    RttP(mutexSend);

    ListFirst(sendMessage);
    rMessage = (char*) ListRemove(sendMessage);

    /*send to the second user */
    sendResult = sendto(sockfdServ, (const void*) rMessage, 
    strlen(rMessage), 0, iter->ai_addr, iter->ai_addrlen);
    if(sendResult == -1) {
      perror("talker: sendTo");
      exit(1);
    }

    RttV(mutexSend);

  }
}

RTTTHREAD receiverFunct(void *arg){
  char *buffer, *newMessage;

  setUpSocket(arg);

  their_addr_len = sizeof(their_addr);

  while(1) {
    /* make a thread sleep for a random amount of time to make it 
    non-blocking andlet other threads execute */
    RttUSleep(4000);

    buffer = malloc(sizeof(char) * MAXBUFLEN);
    numbytes = recvfrom(sockfd, buffer, MAXBUFLEN, 0, 
    (struct sockaddr*) &their_addr, &their_addr_len);

    if (numbytes <= 0) {
        /* if received nothing, continue and do recvfrom again */
        continue;
    } else {
      /* add the received message to the buffer list, 
      dont forget about mutex */
      RttP(mutexReceive);

      newMessage = malloc(sizeof(char) * MAXBUFLEN);
      memcpy(newMessage, buffer, MAXBUFLEN);

      ListAdd(printQueue, (void *) newMessage);

      RttV(mutexReceive);
      RttV(printQueueSem);
    }
    free(buffer);
  }

}

RTTTHREAD keyInputFunct(){
  char *buffer, *newMessage;
  int readBytes;

  fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

  while(1) {
    buffer = malloc(sizeof(char) * MAXBUFLEN);
    while((readBytes = read(0, buffer, MAXBUFLEN)) < 0) {
      /* make a thread sleep for a random amount of time to make 
      it non-blocking andlet other threads execute */
      RttUSleep(4000);
    }

    newMessage = malloc(sizeof(char) * MAXBUFLEN);
    memcpy(newMessage, buffer, MAXBUFLEN);

    RttP(mutexSend);

    ListAdd(sendMessage, (void *) newMessage);

    RttV(mutexSend);
    RttV(sendMessageSem);
    
    readBytes = -1;
    free(buffer);
  }
}

RTTTHREAD printFunct(){
  char *message;
  while(1) {
    RttP(printQueueSem);
    RttP(mutexReceive);

    while(ListCount(printQueue) != 0) {
      ListFirst(printQueue);
      message = (char*) ListRemove(printQueue);
      printf("%s", message);
    }

    RttV(mutexReceive);
  }
}

void mainp(int argc, char *argv[]){
  /* Check for the right number of arguments */
  if (argc != 4) {
      printf("Not enough arguments: there should be 4 arguments \n");
      exit(1);
  }

  /* Check for invalid input (if arguments are all numbers)*/
  if(checkIfNumber(argv[1], 1) == false || 
  checkIfNumber(argv[3], 3) == false ) {
      printf("Invalid arguments: must specify 2 port numbers \n");
      exit(1);
  }

  /*Convert to numbers*/
  port1 = atoi(argv[1]);
  name1 = argv[2];
  port2 = atoi(argv[3]);

  /*Check if the port numbers are within range*/
  if(!((port1 >= 30001 && port1 <= 40000) && 
  (port2 >= 30001 && port2 <= 40000))){
    printf("Invalid port numbers, must be between 30001 and 40000\n");
    exit(1);
  }

  /*Creating lists*/
  printQueue = ListCreate();
  sendMessage = ListCreate();

  /*Creating semaphores and mutex*/
  RttAllocSem(&mutexSend, 1, RTTFCFS);
  RttAllocSem(&mutexReceive, 1, RTTFCFS);
  RttAllocSem(&printQueueSem, 0, RTTFCFS);
  RttAllocSem(&sendMessageSem, 0, RTTFCFS);

  /*Creating threads*/
  rttTimeVar.seconds = 1;
  rttTimeVar.microseconds = 1000;
  attributes.startingtime = rttTimeVar;
  attributes.deadline = rttTimeVar;
  attributes.priority = RTTHIGH;

  a = RttCreate(&keyInputThread, keyInputFunct, 16000, "keyInput", 
(void *)1, attributes, RTTUSR );
  if(a < 0){printf("thread a failed to create\n");}

  b = RttCreate(&netSendThread, senderFunct, 16000, "netSend", 
(void *) argv[3], attributes, RTTUSR );
  if(b < 0){printf("thread b failed to create\n");}

  c = RttCreate(&printThread, printFunct, 16000, "printThread", 
(void *)1, attributes, RTTUSR );
  if(c < 0){printf("thread c failed to create\n");}

  d = RttCreate(&receiverFunctThread, receiverFunct, 
  16000, "receiverFunctThread", 
(void *) argv[1], attributes, RTTUSR );
  if(d < 0){printf("thread d failed to create\n");}

  printf("This is s-chat\n");

}
