/* from lines to strips
 * random effect of 4 states
 * HOWEVER, values have to be discretised for the visual rendering ... pls bear that in mind.
 * */
#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WID 640
#define LMAR 20
#define RMAR LMAR
#define HEI 480

#define VBARNUMS 6
#define HBARNUMS 32

#define CNAML 32 /*  colour name length */
#define VECMAX 64 /*  maxs size of vector */

typedef struct {
    char nam[CNAML];
    int c[3];
} ctri; /*  our colour triplet together with name */

typedef struct {
    char nam[CNAML];
    float c[3];
} ctrif; /*  our colour triplet together with name */

void c2f(ctri *in, ctrif *out)
{
    int i;
    memcpy(out->nam, in->nam, CNAML);
    for(i=0;i<3;++i) {
        if(in->c[i] == 0)
            out->c[i] = 0.0;
        else
            out->c[i] = in->c[i]/255.0;
    }
}

int int_cmp(const void *a, const void *b) 
{ 
    const int af = *(int *)a; // casting pointer types 
    const int bf = *(int *)b; // casting pointer types 

    if (af < bf)
        return -1;
    else if (af > bf)
        return 1;
    else
        return 0;
}

int main (int argc, char *argv[])
{
    /*  gen decalrations */
    int i, j;

    /*  get our canvas set up with background colour */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, WID, HEI);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, WID, HEI); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* now, deal with our colours */
    ctri cdna[4] = { { "A_blue", {69, 56, 239}}, { "C_green", {0, 121, 7}}, { "G_red", {229, 63, 61}}, { "T_yellow", {254, 242, 0}} };
    ctrif *cdnaf;
    cdnaf=malloc(sizeof(ctrif)*4);
    for(i=0;i<4;++i) 
        c2f(cdna+i, cdnaf+i);

    /*  set up canvas */
    int *hbars;
    hbars=calloc(HBARNUMS, sizeof(int));
    hbars[0] = HEI/HBARNUMS/2;
    for(i=1;i<HBARNUMS;++i)
        hbars[i] = hbars[i-1] + HEI/HBARNUMS;

    /* we are going to geenrate variables size vectors, which will all be included in one big one */
    int rasz, *rarr, racol;
    rarr=malloc(sizeof(int)*10); /* 10 an arbitrary mesize ..we will be using realloc in the loop */

    srand(4);
    cairo_set_line_width (cr, 4);
    for(i=0;i<HBARNUMS;++i) {
        rasz=rand()%VECMAX;
        rarr = realloc(rarr,(rasz+2)*sizeof(int));
        rarr[0]=LMAR;
        rarr[rasz+1]=WID-RMAR;
        /*  first allocate values for the rarr vector */
        for(j=1;j<rasz+2-1;++j)
            rarr[j] = (int) (((float)rand()/RAND_MAX) * (WID-RMAR-LMAR) +LMAR); /* pick a randon position */
        /* now they have to be sorted */
        qsort(&rarr[0], rasz+2, sizeof(float), int_cmp);
        for(j=0;j<rasz+2;++j) 
            printf("%i ",rarr[j]); 
        printf("\n"); 

        /* Drawing code goes here */
        for(j=1;j<rasz+2;++j) {
            racol=rand()%4;
            cairo_set_source_rgba(cr, cdnaf[racol].c[0], cdnaf[racol].c[1], cdnaf[racol].c[2], 0.8);
            cairo_move_to(cr, rarr[j-1], hbars[i]);
            cairo_line_to(cr, rarr[j], hbars[i]); // tried moving to one less than this, but black stripes show up.
            cairo_stroke (cr);
        }
    }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "strips.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(rarr);
    free(cdnaf);
    free(hbars);

    return 0;
}
