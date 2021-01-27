/**
 * This program gets user input uses threads to
 * calculate the average, find the highest and lowest
 * integer from user requested input
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//number of threads needed for this program
#define no_of_threads 3

//initialize the array where the user requested 
//integers will be stored and its length
int *arr;
int length = 0;
//initialize variables to store the average, 
//max and min
int average;
int maxVal;
int minVal;

/**
 * This method finds the average in a list of
 * user requested integers and prints the result
*/
void* threadAverage(void * arg)
{
    int sum=0;
    for (int i=0; i<length; i++)
        sum = sum + arr[i];
    average = sum / length;
    printf("Average is: %d\n", average);
}

/**
 * This method finds the lowest integer in 
 * a list of user requested integers and
 * prints the result
*/
void* threadMin(void * arg)
{
    //calculate min value
    minVal = arr[0];
    for (int i=1; i<length; i++)
    {
        if (arr[i] < minVal)
            minVal = arr[i];
    }
    printf("Minimum is: %d\n", minVal);
}

/**
 * This method finds the highest integer
 * in a list of user requested integers and
 * prints the result
*/
void* threadMax(void * arg)
{
    //calculate max value
    maxVal = arr[0];
    for (int i=1; i<length; i++)
    {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }
    printf("Max is: %d\n", maxVal);
}

int main(int argc, char *argv[])
{
    //define the length of the list
    length = argc-1;
    //get list of integers from the user
    arr = (int*)malloc(sizeof(int)*(argc-1));
    for (int i=1; i<argc; i++) {
        arr[i-1] = atoi(argv[i]);
    }

    //create three separate threads
    pthread_t threadboy;
    pthread_t threadgirl;
    pthread_t threadbaby;
    //create thread attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    //initialize threads
    pthread_create (&threadboy, &attr, threadAverage, NULL);
    pthread_create (&threadgirl, &attr, threadMin, NULL);
    pthread_create (&threadbaby, &attr, threadMax, NULL);
    
    //wait for all threads to finish
    pthread_join(threadboy, NULL);
    pthread_join(threadgirl, NULL);
    pthread_join(threadbaby, NULL);

    return 0;
}