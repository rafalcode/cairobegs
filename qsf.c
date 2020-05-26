#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int flo_cmp(const void *a, const void *b) 
{ 
    const float af = *(float *)a; // casting pointer types 
    const float bf = *(float *)b; // casting pointer types 

    if (af < bf)
        return -1;
    else if (af > bf)
        return 1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    int i, j;
    float *fa;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <sequence of floating point numbers>...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    fa=malloc(sizeof(float)*(argc-1));
    for(i=1;i<argc;++i) 
        fa[i-1] = atof(argv[i]); 

    qsort(&fa[0], argc-1, sizeof(float), flo_cmp);

    for (j = 0; j < argc-1; j++)
        printf("%3.6f ",fa[j]);
    printf("\n"); 

    exit(EXIT_SUCCESS);

    free(fa);
}
