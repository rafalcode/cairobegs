/* very worthwhile exercise, advancing step by step horizontally
 * and then by powers of two vertically. In this way a binomial pattern can be drawn with cairo
 * it's critical to see how those forloop indices are built up */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define HBARNUMS 8

typedef struct
{
    int h, v;
} pos;

int main (int argc, char *argv[])
{
    int i, width=480, height=480;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* vertical divider how ar ewe going to section off the screen vertically */
    float hbar=(float)width/HBARNUMS; /* answer is: equally */
    float vbar=(float)height/HBARNUMS; /* answer is: equally */
    pos ori, *lb=calloc(HBARNUMS, sizeof(pos)); /* ori: origin, lb, last bar, */
    /* arrange array of positions */
    ori.h=hbar/2.;
    ori.v=height/2.;

    lb[0].h= width-hbar/2.;
    lb[0].v = vbar/2.;
    for(i=1;i<HBARNUMS;i++) {
        lb[i].h= width-hbar/2.;
        lb[i].v = lb[i-1].v + vbar;
    }

    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    for(i=0;i<HBARNUMS;i++){
        cairo_arc(cr, lb[i].h, lb[i].v, 1, 0, 2 * M_PI);
        cairo_fill(cr);

        cairo_move_to(cr,ori.h,ori.v);
        cairo_line_to(cr,lb[i].h, lb[i].v);
        cairo_stroke(cr);
    }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "trndot.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(lb);

    return 0;
}
