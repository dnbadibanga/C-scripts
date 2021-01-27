/**
 * This program creates two types of threads:
 *    North farmers (farmers from North Tunbridge who want to go south)
 *    South farmers (farmers from South Tunbridge who want to go north)
 * farmers from both Tunbridges take turns to go across the bridge as
 * not more than one farmer can use the bridge at any given time.
 * @author Divine Ndaya Badibanga (201765023)
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>

#define EMPTY 0 //bridge is free to use
#define FULL 1  //bridge is being used
int bridge;     //the bridge
//i called him Simon because Simon gets to say who can cross the bridge
int simon;      //the lock, 
void *northCrossings(void * param); //function north farmers use to cross
void *southCrossings(void * param); //function south farmers use to cross

int main(){
    pthread_t farmer[20]; //create some threads
    //thread attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (int i = 0; i<20; i++){
        if (i%2 == 0){
            //some north Tunbridge farmers
            pthread_create(&farmer[i], &attr, northCrossings, NULL);}
        else {
            //some south Tunbridge farmers
            pthread_create(&farmer[i], &attr, southCrossings, NULL);
        }}

    for (int i = 0; i<20; i++){
        pthread_join(farmer[i], NULL); //wait for threads to finish
    }

    return 0;
}

void *northCrossings(void * param){
    while (simon == FULL){
        //wait for bridge to free up
    }
    //get Simon to say north farmer can cross
    if (simon == EMPTY){
        //while crossing, no one else can cross
        simon = FULL;
        printf("North farmer coming through!\n");
        int random = rand()%10;
        sleep(random);
        //Simon says the bridge is free to use again
        simon = EMPTY;}
}

void *southCrossings(void * param){
    while (simon == FULL){
        //wait for bridge to free up
    }
    //get Simon to say South farmer can cross
    if (simon == EMPTY){
        //no one else can cross while im crossing
        simon = FULL;
        printf("South farmer, look out!\n");
        int random = rand()%10;
        sleep(random);
        //Simon says the bridge is free to use again
        simon = EMPTY;}
}