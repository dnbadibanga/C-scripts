/**
 * @Divine Ndaya Badibanga (201765203)
 * This program imitates a process id manager (PID), which assigns processes
 * a unique PID. When the process completes, the PID is returned and will be 
 * reassigned to a new process.
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>

/**
 * PID values will be between 300 and 5000
*/
#define MIN_PID 300
#define MAX_PID 5000
#define no_of_threads 100

/**
 * Create data structure to represent the availability of process identifiers
*/
int size = MAX_PID-MIN_PID+1;
int pid_manager[MAX_PID-MIN_PID+1];

/**
 * Semaphores to protect pid data structure from race conditions
*/
sem_t lock;

/**
 * This method assigns a 0 to indicate availability
 * Returns 1 for succesful assignment and -1 for unsuccesful assignment
*/
int allocate_map(void) {
    int i = 0;
    for (i; i<size; i++){
        pid_manager[i] = 0;
    }
    for (i; i<size; i++){
        if (pid_manager[i] != 0){
            return -1;
        }
    }
    return 1;
}

/**
 * This method allocates a process a unique PID.
 * Once a process is assigned a PID, the PID manager sets the value of the memory
 * space to 1 to indicate an unavailable PID.
 * Returns a PID within the range 300-5000. If no PID is available, returns -1
*/
int allocate_pid(void){
    int i = 0;
    sem_wait(&lock);
    for (i; i<size; i++){
        if (pid_manager[i] == 0){
            pid_manager[i] = 1;
            sem_post(&lock);
            return i+300;
        }
    }
    sem_post(&lock);
    return -1;
}

/**
 * This method receives a PID from a completed process so the PID may be reassigned
 * to a future process.
 * @param process id 
*/
void release_pid(int pid){
    int assigned_pid = pid-300;
    pid_manager[assigned_pid] = 0;
}

/**
 * This method simulates a thread: gets a pid, sleeps for a certain amount
 * of time and returns the pid when it is done.
*/
void* sleeps(void * args)
{
    int random = rand()%60;

    //sem_wait(&lock);
    int pid = allocate_pid();
    //sem_post(&lock);
    
    sleep(random);
    release_pid(pid);
    printf("I AM THREAD: %d", pid);
    printf( " AND I SLEPT FOR %d", random);
    printf( " SECONDS!\n");
}

int main() 
{
    //initialize pids
    allocate_map();

    //initialize semaphore
    sem_init(&lock,0,1);

    int i;
    //create 300 threads
    pthread_t tid[no_of_threads];
    //thread attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    //create 300 threads
    for (i = 0; i <no_of_threads; i++)
        pthread_create(&(tid[i]), &attr, &sleeps, NULL);

    //wait for 300 threads to finish execution
    for (i=0; i< no_of_threads; i++)
        pthread_join(tid[i], NULL);

    //kill semaphore
    sem_destroy(&lock);

return 0;
}