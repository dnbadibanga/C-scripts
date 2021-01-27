#include <stdio.h>

int main() 
{ 
    printf("Hello, world!\n");


/*This loop prints all even numbers less than 10, 
starting with 0, in ascending order*/
int i = 0;

for ( i=0; i<10; i=i+2)

    printf("%d\n", i);


/*This loop prints, in descending order, 
all integers greater than 0, starting at 100 with intervals of 7*/ 
for (i=100; i>=0; i=i-7)

    printf("%d\n", i);


/*This loop prints, in ascending order, all integers less than 10
starting from 1*/
for (i=1; i<=10; i=i+1)

    printf("%d\n", i);



/*This loop prints, in ascending order, a sequence of integers
less than 100, starting with 2 and doubling from the previous integer*/
for (i=2; i<100; i=i*2)

    printf("%d\n", i);


/*This loop prints integers 1 through 11, inclusive, and their squares*/
for (i=1; i<=11; i=i+1)
    printf("%d%s%3d\n", i, " ", (i*i));


/*This loop prints a triangle made of asterisks (left aligned)*/
for (i=1; i<=11; i=i+1){
    for (int j=1; j=i; j=j+1){
        printf("%s", "*");
    }
    printf("\n");

}

return 0;
}