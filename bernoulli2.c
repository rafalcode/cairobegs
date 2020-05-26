/* follow-up of bernoulli trials hthis time with a matrix of walks
 * note how only one call tp rand() per 32 steps is needed. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASZ 32
#define STEP 10
#define RSEED 3
#define NUMWALKS 20

int main(int argc, char *argv[])
{

    int **carr; /*  this will be the array which holds our random walk, the prefix "c" is for cumulative, see below as we build it */
    unsigned int i, j, rhold;
    carr=malloc(NUMWALKS*sizeof(int *));
    for(i=0; i<NUMWALKS; ++i) 
        carr[i]=calloc(ASZ,sizeof(int));

    srand(RSEED);

    for(j=0; j<NUMWALKS; ++j) {
        rhold=rand(); /* only one random number required (as they fgo up to RAND_MAX */

        for(i=1; i<ASZ; ++i) { /* we start on the second entry ... note how the first entry is already zero due to the previous calloc */
            carr[j][i] = STEP - (rhold>>i & 1)*STEP*2 + carr[j][i-1]; /* 1's and 0's rendered into -STEP and +STEP (respectively) */
            printf("%i ", carr[j][i]);
        }

        printf("\n"); 
    }

    /* now free stuff */
    for(i=0; i<NUMWALKS; ++i) 
        free(carr[i]);
    free(carr);

    return 0;
}
