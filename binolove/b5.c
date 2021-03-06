/* just generating an index file from vbars[] */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VBARNUMS 4
#define SQBLX 4
#define SQWD 320 
#define SQHE 240 

int *crearvarr(int *arr, int sz)
{
    int i, j=0, *rvarr;
    rvarr=calloc(sz, sizeof(int));
    for(i=sz-1;i>=0;--i)
        rvarr[j++] = arr[i];
    return rvarr;
}

int main (int argc, char *argv[])
{
    int canvw= SQWD*SQBLX/2, canvh=SQHE*SQBLX/2;
    int i, j, m, k, *vind, *rvind, *vpos, *rvpos, *totvpos, widthoffset, heightoffset;
    /* vertical divider how ar ewe going to section off the screen vertically */

    totvpos=calloc(num_vpos*SQBLX, sizeof(int));
    vpos=calloc((1<<VBARNUMS)-1, sizeof(int));
    rvpos=calloc((1<<VBARNUMS)-1, sizeof(int));
    vind=calloc(VBARNUMS+1, sizeof(int));

    for(k=0;k<SQBLX;++k) {
        heightoffset=SQHE*(k%2 + k/2)%2; /*  very awkward yes, that's true. */
        num_vpos=(1<<VBARNUMS)-1;

        /* arrange array of positions */
        vind[0]=0;

        for(i=0;i<VBARNUMS;i++) {
            vind[i+1] = (1<<(i+1))-1;
            m=0;
            for(j=vind[i]; j<vind[i+1]; ++j) 
                vpos[j] = SQHE/(2<<i) + (m++) * SQHE/(1<<i)i + heightoffset;
        }

        for(i=0;i<=VBARNUMS;i++)
            printf("%i ", vind[i]);
        printf("\n"); 

        for(i=0;i<(1<<VBARNUMS)-1;i++)
            printf("%i ", vpos[i]);
        printf("\n"); 
        printf("Or:\n"); 
        for(i=0;i<VBARNUMS;i++) {
            for(j=vind[i]; j<vind[i+1]; ++j) 
                printf("%i ", vpos[j]);
            printf("\n"); 
        }

        printf("\nNow parse it in reverse 2nt att:\n"); 
        rvind=crearvarr(vind, VBARNUMS+1);

        for(i=0;i<=VBARNUMS;i++)
            printf("%i ", rvind[i]);
        printf("\n"); 

        m=0;
        for(i=0;i<VBARNUMS;i++) {
            for(j=rvind[i]-1; j>=rvind[i+1]; --j) {
                printf("%i ", vpos[j]+heightoffset);
                rvpos[m++] = vpos[j]+heightoffset;
            /*  here I'm adding an offset to the vpos, so they all get pushed down, as well as reversed */
            }
            printf("\n"); 
        }
        /*  inject vpos into totvpos at right index */
        if((k/2)==0)
            memcpy(totvpos+k*num_vpos, vpos, sizeof(int)*num_vpos);
        else
            memcpy(totvpos+k*num_vpos, rvpos, sizeof(int)*num_vpos);
    }

    printf("TOTVPOS:\n"); 
    for(i=0;i<(1<<VBARNUMS)*4;++i)
        printf("%i ", totvpos[i]); 
    printf("\n"); 

    free(vpos);
    free(rvpos);
    free(totvpos);
    free(vind);
    free(rvind);

    return 0;
}
