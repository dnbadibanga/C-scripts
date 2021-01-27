#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*define message size, the reading end and writing end of the pipes*/
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main()
{
    /*instantiate the message to be sent*/
    char write_msg[BUFFER_SIZE] = "Hi There";
    char read_msg[BUFFER_SIZE];
    /*create the pipe*/
    int fdmama[2];
    int fdbaby[2];
    pid_t pid;

    /* create the pipe */
    if (pipe(fdmama)==-1){
        fprintf(stderr, "Pipe failed");
        return 1;}
    if (pipe(fdbaby)==-1){
        fprintf(stderr, "Pipe failed");
        return 1;}

    /* fork a child process */
    pid = fork();

    if (pid<0){ /* error occured */
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    if (pid>0){ /* parent process */
        /* close the reading end of the pipe the parent process writes into */
        close(fdmama[READ_END]);

        /* send the message to the child process */
        write(fdmama[WRITE_END], write_msg, strlen(write_msg)+1);
        /* close the writing end of the pipe */
        close(fdmama[WRITE_END]);

        /* wait for the child to die */
        wait(NULL);

        /* close the end of the tube the child process writes into */
        close(fdbaby[WRITE_END]);

        /* read and print the message sent by the child */
        read(fdbaby[READ_END], read_msg, BUFFER_SIZE);
        printf("%s\n", read_msg);
        /* close the end of the tube the parent process reads from */
        close(fdbaby[READ_END]);
    }

    if (pid==0) { /* child process */
        /* close the end of the pipe the parent writes into */
        close(fdmama[WRITE_END]);

        /* read the message from the parent process */
        read(fdmama[READ_END], read_msg, BUFFER_SIZE);

        /* flip the message */
        for (int i=0; i<strlen(read_msg); i++){
            if (read_msg[i]>64 && read_msg[i]<91){
                read_msg[i] = read_msg[i]+32;
            }
            else if (read_msg[i]>96 && read_msg[i]<123){
                read_msg[i] = read_msg[i]-32;
            }
        }

        /* close the ends of the pipe both process read from */
        close(fdmama[READ_END]);
        close(fdbaby[READ_END]);

        /* send the modified message to the parent process */
        write(fdbaby[WRITE_END], read_msg, strlen(read_msg)+1);
        /* close the end of the pipe the child writes into */
        close(fdbaby[WRITE_END]);

        /* kill the child */
        exit(0);
    }

    return 0; /* end the program */
}