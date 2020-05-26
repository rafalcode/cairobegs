#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXREPROS 18  /* number of reproductions of the core shape */
#define NUMCOLS 18 /* number of colors to use */

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

    cairo_set_line_width(cr, 1.0);
    /*  critical sets the centre point for our activities */
    cairo_translate(cr, width/2, height/2);

    int i;
    colr **col;
    col=malloc(sizeof(colr *) * NUMCOLS);
    for(i=0;i<NUMCOLS;i++) {
        col[i]= malloc(sizeof(colr));
        pullcol(col[i], 28+3*i);
    }

    printf("col is %s and rcol is %3.4f\n", col[1]->colnam, (float)col[0]->num[0]/255.0);
    int ci;

    cairo_save(cr);
    for ( i = 0; i < MAXREPROS; i++) {
        ci =i%NUMCOLS;
        /* Must get the rotate and scale commadns in that order, vital */
        cairo_rotate(cr, i*M_PI/MAXREPROS);
        cairo_scale(cr, 0.3, 1);
        cairo_arc(cr, 0, 0, 120, 0, 2 * M_PI);
        cairo_restore(cr);
        cairo_set_source_rgb (cr, (float)col[ci]->num[0]/255.0, (float)col[ci]->num[1]/255.0, (float)col[ci]->num[2]/255.0);
        cairo_stroke(cr);
        cairo_save(cr);
    }

    cairo_destroy(cr);
    cairo_surface_write_to_png (surface, "cl.png");
    cairo_surface_destroy (surface);

    for(i=0;i<NUMCOLS;i++)
        free(col[i]);
    free(col);

    return 0;
}
