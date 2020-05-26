/*  trying to get four spirals in to 4 sublocks, this took quite while
 *  mainly because I ran into the cairo_translate() being affine (remebering its last pos.
 *  It now works. */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXREPROS 8  /* number of reproductions of the core shape */
#define NUMCOLS 4 /* number of colors to use */
#define SUBDIV 4

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
    int width=640, height=480;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    int i, ci=0, j, blockw=width/(SUBDIV/2), blockh=height/(SUBDIV/2);
//     printf("%i %i\n", blockw, blockh);
    int curcentx=blockw/2, curcenty=blockh/2;

    /*  build up the rgb color array */
    colr **col;
    col=malloc(sizeof(colr *) * NUMCOLS*4);
    for(i=0;i<NUMCOLS*4;i++) {
        col[i]= malloc(sizeof(colr));
        pullcol(col[i], 118+3*i);
    }

         cairo_translate(cr, curcentx, curcenty);

    for(j=0;j<SUBDIV;j++) {

        curcentx = (j==0)? 0 : (-1 + 2*(j%2)) * blockw;
        curcenty = (j==0)? 0 : (1 - j%2)*blockh;

        cairo_set_line_width(cr, 0.5+j);
        cairo_translate(cr, curcentx, curcenty);

        cairo_save(cr);
        for ( i = 0; i < MAXREPROS; i++) {
            ci =i%NUMCOLS;
            /* Must get the rotate and scale commands in that order, vital */
            cairo_rotate(cr, i*M_PI/MAXREPROS);
            cairo_scale(cr, 0.3, 1);
            cairo_arc(cr, 0, 0, 60, 0, 2 * M_PI);
            cairo_restore(cr);
            cairo_set_source_rgb (cr, (float)col[j*NUMCOLS+ci]->num[0]/255.0, (float)col[j*NUMCOLS+ci]->num[1]/255.0, (float)col[j*NUMCOLS+ci]->num[2]/255.0);
            cairo_stroke(cr);
            cairo_save(cr);
        }
    }

    cairo_destroy(cr);
    cairo_surface_write_to_png (surface, "cl.png");
    cairo_surface_destroy (surface);

    for(i=0;i<NUMCOLS;i++)
        free(col[i]);
    free(col);

    return 0;
}
