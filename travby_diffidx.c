/*  Travelling a matrix using differential indices (i..e via delta changes to current index) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DM 8
int main(int argc, char *argv[])
{

   int i, j;
   i=0;
   while (i<16) {
       j = ( (1-2*((i/4)%2)) & 0x80000003);
       printf("%i ", j); 
       ++i;
   }
   printf("\n");
   printf("%i ", (4 & 3));
   printf("\n");
   int f, g;
   i=0;
   while (i<32) {
       f = (i%DM+(DM-1))/DM;
       g = 1-((i/DM)%2)*2;
       printf("%2i ", f*g); 
       ++i;
   }
   printf("\n");
   i=0;
   while (i<32) {
       printf("%2i ", (1 - (i%DM)+DM-1)/DM);
       ++i;
   }
   printf("\n");
   return 0;
}
