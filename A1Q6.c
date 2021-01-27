#include <stdio.h>

int main() 
{ 

/*This loop prints all even numbers less than 10, 
starting with 0, in ascending order*/
int i = 0;

for ( i=0; i<10; i=i+2)
{
    printf("%d\n", i);
}
printf("\n");

/*This loop prints, in descending order, 
all integers greater than 0, starting at 100 with intervals of 7*/ 
for (i=100; i>=0; i=i-7)
{
    printf("%d\n", i);
}
printf("\n");

/*This loop prints, in ascending order, all integers less than 10
starting from 1*/
for (i=1; i<=10; i=i+1)
{
    printf("%d\n", i);
}
printf("\n");


/*This loop prints, in ascending order, a sequence of integers
less than 100, starting with 2 and doubling from the previous integer*/
for (i=2; i<100; i=i*2)
{
    printf("%d\n", i);
}
printf("\n");

return 0;
}

/**Divine Ndaya Badibanga - 201765203*/