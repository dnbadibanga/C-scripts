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
    for (i; i<size; i++){
        if (pid_manager[i] == 0){
            pid_manager[i] = 1;
            return i+300;
        }
    }
    return -1;
}

/**
 * This method receives a PID from a completed process so the PID may be reassigned
 * to a future process.
*/
void release_pid(int pid){
    int assigned_pid = pid-300;
    pid_manager[assigned_pid] = 0;
}

void* sleeps(void * args)
{
    //int random = rand();
    int pid = allocate_pid();
    printf("Thread: %d\n", pid);
    sleep(10);
    release_pid(pid);
}

int main() 
{
    printf("i work so far\n");
    allocate_map();
    int i;
    pthread_t tid[no_of_threads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (i = 0; i <no_of_threads; i++)
        pthread_create(&(tid[i]), &attr, &sleeps, NULL);

    for (i=0; i< no_of_threads; i++)
        pthread_join(tid[i], NULL);

return 0;
}