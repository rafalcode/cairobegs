#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{

    unsigned int RMX=RAND_MAX;
    RMX++;
    int i, j, *rint;
    float *rarr;
    rarr=malloc(4*4*sizeof(float));
    rint=malloc(4*4*sizeof(int));
    for(i=0; i<4; ++i)
    for(j=0; j<4; ++j) {
        rint[4*i+j]=rand();
        rarr[4*i+j]=(float)rint[4*i+j]/RMX;
        rarr[4*i+j] *=M_PI*(i+1)/4;
    }

   free(rarr);
   return 0;
}
