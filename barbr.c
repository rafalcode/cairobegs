/* cahnign colors within liens using a start stop pattern */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUML 12
#define NAMBUF 32 /* string buffer for color names */
#define CS_SZ 18 /* the size (number of colours) that our colorscheme has */
#define FFASP 29 /* ffmpeg's aspects ratios */
#define MYASP 1 /* any speicals I happen to put in */
#define SZASP (FFASP+MYASP)

/*  here is the aspect ratio datastruct, "aspstruct" */
typedef struct
{
    char nasp[7];
    int awd, aht;
} aspstruct;

/*  and here is the array itself */
const aspstruct aspff[SZASP]= { \
{"sqcif", 128, 96}, \
{"qcif", 176, 144}, \
{"cif", 352, 288}, \
{"4cif", 704, 576}, \
{"16cif", 1408, 1152}, \
{"qqvga", 160, 120}, \
{"qvga", 320, 240}, \
{"vga", 640, 480}, \
{"svga", 800, 600}, \
{"xga", 1024, 768}, \
{"uxga", 1600, 1200}, \
{"qxga", 2048, 1536}, \
{"sxga", 1280, 1024}, \
{"qsxga", 2560, 2048}, \
{"hsxga", 5120, 4096}, \
{"wvga", 852, 480}, \
{"wxga", 1366, 768}, \
{"wxgamod", 1400, 900}, \ /* special one */
{"wsxga", 1600, 1024}, \
{"wuxga", 1920, 1200}, \
{"woxga", 2560, 1600}, \
{"wqsxga", 3200, 2048}, \
{"wquxga", 3840, 2400}, \
{"whsxga", 6400, 4096}, \
{"whuxga", 7680, 4800}, \
{"cga", 320,200}, \
{"ega", 640, 350}, \
{"hd480", 852, 480}, \
{"hd720", 1280, 720}, \
{"hd1080", 1920, 1080} };

typedef struct /* colstru_i */
{
    char nam[NAMBUF];
    int rgb[3];
} colstru_i;

typedef struct /* colstru_f */
{
    char *nam;
    float *rgb;
} colstru_f;

colstru_f *initcf(int n)
{
    int i;
    colstru_f *cfarr=malloc(n * sizeof(colstru_f));
    for(i=0;i<n;++i) {
        cfarr[i].nam = calloc(NAMBUF, sizeof(char));
        cfarr[i].rgb=malloc(3 * sizeof(float));
    }
    return cfarr;
}

void freecf(colstru_f *cfarr, int n)
{
    int i;
    for(i=0;i<n;++i) {
        free(cfarr[i].nam);
        free(cfarr[i].rgb);
    }
    free(cfarr);
}

void printmecols(colstru_f *colsf, int n)
{
    int i;
    for(i=0;i<n;++i) 
        printf("%s\t", colsf[i].nam);
    printf("\n"); 
    for(i=0;i<n;++i) 
        printf("%3.4f\t", colsf[i].rgb[0]);
    printf("\n"); 
    for(i=0;i<n;++i) 
        printf("%3.4f\t", colsf[i].rgb[1]);
    printf("\n"); 
    for(i=0;i<n;++i) 
        printf("%3.4f\t", colsf[i].rgb[2]);
    printf("\n"); 
}

void norfloatify(colstru_i *schcol, colstru_f *colsf, int sz)
{
    int i;
    for(i=0;i<sz;++i) {
        strncpy(colsf[i].nam, schcol[i].nam, NAMBUF-1);
        colsf[i].rgb[0] = (float)schcol[i].rgb[0]/255.0;
        colsf[i].rgb[1] = (float)schcol[i].rgb[1]/255.0;
        colsf[i].rgb[2] = (float)schcol[i].rgb[2]/255.0;
    }
}

colstru_f *makecbands(colstru_f from, colstru_f to, int n)
{
    int i, j;
    char *tnam=calloc(NAMBUF, sizeof(char));
    colstru_f *retstru=initcf(n);
    float *slopes=calloc(3, sizeof(float));
    for(i=0;i<3;++i) 
        slopes[i] = to.rgb[i] - from.rgb[i];
    float divs=(float)1/(n-1);

    /* the first */
    strcpy(retstru[0].nam, from.nam);
    sprintf(tnam, "_%02i", 0);
    strcat(retstru[0].nam, tnam);
    for(i=0;i<3;++i) 
        retstru[0].rgb[i] = from.rgb[i];

    for(i=1;i<n;++i) {
        strcpy(retstru[i].nam, from.nam);
        sprintf(tnam, "_%02i", i);
        strcat(retstru[i].nam, tnam);
        for(j=0;j<3;++j) 
            retstru[i].rgb[j] = from.rgb[j] + i*divs*slopes[j];
    }
    free(slopes);
    free(tnam);
    return retstru;
}

int main (int argc, char *argv[])
{
    int i, width=480, height=480;
    // colstru_i scheme[4] = { {"ddbrown", {40, 23, 11} }, {"dbrown", {80, 45, 22} }, {"bbrown", {120, 68, 33} }, {"nbrown", {160, 90, 44} } };
    colstru_i scheme[4] = { {"ddbrown", {40, 23, 11} }, {"dbrown", {80, 45, 22} }, {"dmag", {82, 0, 82} }, {"nbrown", {160, 90, 44} } };
    colstru_f *colsf=initcf(4);
    norfloatify(scheme, colsf, 4);

    printmecols(colsf, 4);
    colstru_f *bands=makecbands(colsf[0], colsf[2], NUML);
    printmecols(bands, NUML);

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the banded background */
    float wband=(float)width/NUML;
    float *xpos=calloc(NUML, sizeof(float));
    xpos[0]=.0;
    for(i=1;i<NUML;++i) 
        xpos[i] = xpos[i-1]+wband;

    for(i=0;i<NUML;++i) {
        cairo_set_source_rgb(cr, bands[i].rgb[0],  bands[i].rgb[1],  bands[i].rgb[2]);
        cairo_rectangle (cr, xpos[i], 0, wband, height);
        cairo_fill (cr);
    }

    /* Write output and clean up */
    cairo_surface_write_to_png(surface, "browb.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(xpos);
    freecf(bands, NUML);
    freecf(colsf, 4);

    return 0;
}
