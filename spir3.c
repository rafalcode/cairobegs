/*  spir3.c ready. FInally I managed to 100 spiral-type thingies (not really spirals of course
 *  working. 256 seems too much */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define IMWIDTH 640
#define IMHEIGHT IMWIDTH
#define DM 16 /* blockdim */
#define MAXREPROS 8  /* number of reproductions of the core shape */
#define NUMCOLS 2 /* number of colors to use */

typedef struct {
    int num[3];
    char colnam[64];
} colr;

void pullcol(colr *col, int rgblnum) /* pull a colour from rgb.txt held in standard place */
{
    FILE *fcol;
    char c;
    fcol=fopen("/usr/share/X11/rgb.txt","r");
    if(fcol == NULL) {
        printf("Error. rgb.txt is not in usual place on you system. Program will not run.\n");
        exit(EXIT_FAILURE);
    }

    int nlnum=0;
    while((c=fgetc(fcol)) !=EOF) {
        if(c=='\n') nlnum++;
        if(nlnum==rgblnum) break;
    }

    fscanf(fcol, "%i %i %i %s", &col->num[0], &col->num[1], &col->num[2], col->colnam);
    fclose(fcol);
}

int main (int argc, char *argv[])
{
    if((IMWIDTH%DM != 0) | (IMHEIGHT%DM != 0)) {
        printf("Error: Image size must be evenly dvidied by subdivision dimensions\n"); 
        return(EXIT_FAILURE);
    }
    int DM2 = pow(DM,2);
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMWIDTH, IMHEIGHT);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, IMWIDTH, IMHEIGHT); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    int i, ci=0, j, blockw=IMWIDTH/DM, blockh=IMHEIGHT/DM;
    int curcentx=blockw/2, curcenty= - blockh/2; /*  note that negative: I want to start outside of the image! */

    /*  build up the rgb color array */
    colr **col;
    col=malloc(sizeof(colr *) * (DM2)*NUMCOLS);
    for(i=0;i<(DM2*NUMCOLS);i++) {
        col[i]= malloc(sizeof(colr));
        pullcol(col[i], 18+i);
    }

    cairo_translate(cr, curcentx, curcenty);

    for(j=0;j<(DM2);j++) {

        curcentx = blockw * ((j%DM+(DM-1))/DM * (1-((j/DM)%2)*2)); // don't ask .. look at trav by indexprogram 
        curcenty = blockh * ((1 - (j%DM)+DM-1)/DM);

        cairo_set_line_width(cr, 1);
        cairo_translate(cr, curcentx, curcenty);

        cairo_save(cr);

        for ( i = 0; i < MAXREPROS; i++) {
            ci =i%NUMCOLS;
            /* Must get the rotate and scale commands in that order, vital */
            cairo_rotate(cr, i*M_PI/MAXREPROS);
            cairo_scale(cr, 0.3, 1);
            cairo_arc(cr, 0, 0, 15, 0, 2 * M_PI);
            cairo_restore(cr);
            cairo_set_source_rgb (cr, (float)col[j*NUMCOLS+ci]->num[0]/255.0, (float)col[j*NUMCOLS+ci]->num[1]/255.0, (float)col[j*NUMCOLS+ci]->num[2]/255.0);
            cairo_stroke(cr);
            cairo_save(cr);
        }
    }

    cairo_destroy(cr);
    cairo_surface_write_to_png (surface, "spir3.png");
    cairo_surface_destroy (surface);

    for(i=0;i<(DM2*NUMCOLS);i++)
        free(col[i]);
    free(col);

    return 0;
}
