#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int j, x, y, DM=8;
    int blockw=480/DM, blockh = 480/DM;
    /* print stuff out */
    for(j=0;j<DM*DM;++j) {
        x =  blockw * ((j%DM+(DM-1))/DM * (1-((j/DM)%2)*2)); // don't ask .. look at trav by indexprogram 
        y =  blockh * ((1 - (j%DM)+DM-1)/DM);
        printf("%i %i \n", x,y);
    }
    printf("\n");

    return 0;
}
