// Exercise in array handling and printing.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void rightshift(int *array, int N)
{
  int i;
  for (i=N-1;i>=0;i--)
    array[i+1]=array[i];
}

void cumsum(int array[], int cumarray[], int N)
{
  int cumsum;
  int tmp;
  int i;
  cumsum=array[0];cumarray[0]=0;
  for (i=1;i<=N;i++) {
      tmp=array[i];
      cumarray[i]=cumsum;
      cumsum += tmp;
    }
}
      
int main (int argc, char *argv[])
{

  int *rowsOnProcessor, *cumRowsOnProcessor, *cumROPtrunc;
  int *indx;
  int i;
	int numProcs=4;
	int N=16;
	int part[]= {3, 2 ,3 ,2 , 1,0 , 0, 3, 2, 1, 3,2, 3, 1, 0,0};

  /* 1. Find out how many rows are to be sent to each processor */
  rowsOnProcessor=(int *)calloc(numProcs, sizeof(int));
  for(i=0;i<N;i++)
    rowsOnProcessor[part[i]] ++;
	for(i=0;i<numProcs;i++) { 
		 printf(" %i ",rowsOnProcessor[i]);
	}
	printf("\n");

  cumRowsOnProcessor=(int *)calloc(numProcs+1, sizeof(int));
  cumsum(rowsOnProcessor, cumRowsOnProcessor, numProcs);
	printf("Here now, cumulative ROP:\n");
	for(i=0;i<numProcs+1;i++) { 
		 printf(" %i ",cumRowsOnProcessor[i]);
	}
	printf("\n");
     
  indx = (int *)malloc(sizeof(int)*N);
  for (i=0;i<N;i++) {
    indx[cumRowsOnProcessor[part[i]]++]=i;
  }
	for(i=0;i<numProcs+1;i++) { 
		 printf(" %i ",cumRowsOnProcessor[i]);
	}
	printf("\n");
	printf("And copied into a truncated-by-one array:\n");
   cumROPtrunc=(int *)calloc(numProcs, sizeof(int));
	memcpy(cumROPtrunc,cumRowsOnProcessor,sizeof(int)*numProcs);
	for(i=0;i<numProcs;i++) { 
		 printf(" %i ",cumROPtrunc[i]);
	}
	printf("\n");
	printf("Now the right shift operator:\n");
	rightshift(cumRowsOnProcessor, numProcs);
	for(i=0;i<numProcs+1;i++) { 
		 printf(" %i ",cumRowsOnProcessor[i]);
	}
	printf("\n");

	cumRowsOnProcessor[0]=0;

	for(i=0;i<numProcs+1;i++) { 
		 printf(" %i ",cumRowsOnProcessor[i]);
	}
	printf("\n");

// 
	for(i=0;i<N;i++)
		 (i==N-1)? printf("%i\n", indx[i]) :  printf(" %i ",indx[i]);
	exit (0);
}
