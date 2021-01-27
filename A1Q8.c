#include <stdio.h>

int main() {


/*This loop prints a triangle out of asterisks (left-aligned)*/

/*declare index variables*/
int i;
int j;

/*iterate 1 through 11 (11 lines)*/
for (i=1; i<=11; i=i+1){
    /*for each number, n, in the parent loop, print "*" n times */
    for (j=1; j<=i; j=j+1){
        printf("*");
    }
    /*go to next line as we go to the next number*/
    printf("\n");
}

return 0;
}
/**Divine Ndaya Badibanga*/