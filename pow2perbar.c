/* interesting exercise whereby we advance in the normal manner horizontally
 * but place power of two dot verticially for each step
 * the curious things is that the identity number of the last dots is not 64
 * ... ok,  you were expecting that cos it's zero indexing ... but the thing is
 * .. it0s not 63 either, it's 62!  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i, j;

        /* print stuff out */
        for(i=0; i<6; ++i) {
            for(j=(1<<i)-1; j<((1<<(i+1))-1); ++j) 
                printf("%i,%i | ", i, j);

            printf("\n"); 
        }
    return 0;
}
