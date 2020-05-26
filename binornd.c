/* very worthwhile exercise, advancing step by step horizontally
 * and then by powers of two vertically. In this way a binomial pattern can be drawn with cairo
 * it's critical to see how those forloop indices are built up */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define HBARNUMS 8

int main (int argc, char *argv[])
{
    int i, j, m, width=480, height=480;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* vertical divider how ar ewe going to section off the screen vertically */
    float hbar=width/HBARNUMS; /* answer is: equally */
    float *vpos, *hpos;
    vpos=calloc((1<<HBARNUMS), sizeof(float));
    hpos=calloc((HBARNUMS), sizeof(float));
    /* et the first position of hor and ver pos */
    hpos[0]=hbar/2; 
    vpos[0]=height/2;
    /* arrange array of positions */
    for(i=1;i<HBARNUMS;i++) {
        hpos[i] = hpos[i-1] + hbar;
        m=0;
        for(j=(1<<i)-1; j<((2<<i)-1); ++j) 
            vpos[j] = height/(2<<i) + (m++) * height/(1<<i);
    }

    /* Drawing code goes here */
    cairo_set_source_rgba(cr, 0.2, 0.2, 0.2, 0.8);
    cairo_arc(cr, hpos[0], vpos[0], 1, 0, 2 * M_PI);
    cairo_fill(cr);
    for(i=1;i<HBARNUMS;i++){
        for(j=(1<<i)-1; j<((2<<i)-1); ++j) {
            cairo_arc(cr, hpos[i], vpos[j], 1, 0, 2 * M_PI);
            cairo_fill(cr);

            cairo_move_to(cr,hpos[i],vpos[j]);
            /* bit of skill this: line to the previous position */
            cairo_line_to(cr,hpos[i-1],vpos[(j-1)>>1]);
            cairo_stroke(cr);
        }
    }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "binornd.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(hpos);
    free(vpos);


    return 0;
}
