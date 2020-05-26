/* a more advanced version of image block example */

#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMBUF 32 /* string buffer for color names */
#define CS_SZ 18 /* the size (number of colours) that our colorscheme has */

typedef struct {
    char nam[NAMBUF];
    int rgb[3];
} colstru_i;

typedef struct {
    char nam[NAMBUF];
    float rgb[3];
} colstru_f;

colstru_i scheme[CS_SZ] = { {"foreground", {0xdd, 0xdd, 0xdd} }, {"background", {0x11, 0x11, 0x11} }, {"color0", {0x19, 0x19, 0x19} }, {"color8", {0xa0, 0x52, 0x2d} }, {"color1", {0x80, 0x32, 0x32} }, {"color9", {0x98, 0x2b, 0x2b} }, {"color2", {0x5b, 0x76, 0x2f} }, {"color10", {0x89, 0xb8, 0x3f} }, {"color3", {0xaa, 0x99, 0x43} }, {"color11", {0xef, 0xef, 0x60} }, {"color4", {0x32, 0x4c, 0x80} }, {"color12", {0x2b, 0x4f, 0x98} }, {"color5", {0x70, 0x6c, 0x9a} }, {"color13", {0x82, 0x6a, 0xb1} }, {"color6", {0x92, 0xb1, 0x9e} }, {"color14", {0xa1, 0xcd, 0xcd} }, {"color7", {0xff, 0xff, 0xff} }, {"color15", {0xdd, 0xdd, 0xdd} } };

/* this not only converts an int member to a float, but also normalise it for the cairo [0->1] colourscheme */
int main ()
{
    char ct[NAMBUF]="hello";
    colstru_f *colsf;
   colsf = malloc(sizeof(colstru_f));

     strncpy(colsf->nam, ct, NAMBUF);
//     colsf.nam[NAMBUF]="letsee";
    printf("%s\n",colsf->nam); 
//     colsf->nam[0] = malloc(sizeof(char)*NAMBUF);
//     strncpy(colsf->nam, ct, NAMBUF);
//     // strncpy( &colsf->nam[0], &schcol->nam[0], NAMBUF);
//     colsf->rgb[0] = (float)schcol->rgb[0]/255.0;
//     colsf->rgb[1] = (float)schcol->rgb[1]/255.0;
//     colsf->rgb[2] = (float)schcol->rgb[2]/255.0;
    return 0;
}

