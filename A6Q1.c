/**
 * This program uses 2 threads; one thread to get input
 * from the user and another to sum the numbers and 
 * print the sum
 * @author Divine Ndaya Badibanga
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int LOCK;
#define EMPTY 0
#define FULL 1
#define bufferindex 3

LOCK = EMPTY;
int sharedmemorynumber = 0; //shared memory variable to share between threads
void *getinput(void *param); //function for thread to get input
void *calculatesum(void *param); //function for thread to sum numbers and print 

int main() {
  pthread_t tid[2]; //create two threads
  pthread_attr_t attr; //attributes for thread

  pthread_attr_init(&attr);
  pthread_create(&tid[0], &attr, getinput, NULL);
  pthread_create(&tid[1], &attr, calculatesum, NULL);

//wait for them to finish executing
  for (int i = 0; i < 2; i++)
    pthread_join(tid[i], NULL);
}

void *getinput(void *param) {
  int inputbuffer;
  int sentinelfound;
  
  FILE *fd = fopen("inputfile.txt", "r");
  while (LOCK = EMPTY && !sentinelfound && (fscanf(fd, "%d", &myinputnumber) != EDF)){
    LOCK = FULL;
    if (myinputnumber < 0) sentinelfound = 1;
    inputbuffer[bufferindex] = myinputnumber;
    bufferindex = (bufferindex + 1) % BUFFERSIZE;
  }
  return NULL
}

void *calculatesum(void *param) {
  int sum = 0;
  while (LOCK = FULL){
    //add the numbers together
    while (sharedmemorynumber>=0) {
      //only add numbers if inputthread sets a new number
      if (sharedmemorynumber !=0){
      sum = sum + sharedmemorynumber;
      //set it back to 0 so inputthread can set a new number
      sharedmemorynumber = 0;}
      LOCK = EMPTY;
    }
    //once sentinel value is set, print the sum and exit the thread
    if (sharedmemorynumber < 0) {
    printf("The sum is: %d\n", sum);
    return NULL;
    }
    }
}



void *solicitor(void *param) {
  int maxdonors = *(int *)param;
  int solicitortotal = 0;

  for (int i = 0; i < maxdonors; i++){
    int donation = srand() % MAXDONATION;
    solicitortotal = solicitortotal + donation;
  }
}