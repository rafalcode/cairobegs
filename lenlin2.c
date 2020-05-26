/* cahnign colors within liens using a start stop pattern */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NUML 8

int main (int argc, char *argv[])
{
    int i, width=480, height=480;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    float *vpos, *hpos;
    vpos=calloc(NUML, sizeof(float));
    hpos=calloc(NUML, sizeof(float));

        vpos[0] = height/(NUML*2);

    for(i=1;i<NUML;i++)
        /* originally had: vpos[i] = vpos[i-1] + i*height/NUML; how stupid eh? */
        vpos[i] = vpos[i-1] + height/NUML;

    for(i=0;i<NUML;i++)
        hpos[i] = (i%2==0) ? width/4 : width/2;

    cairo_pattern_t *linpat = cairo_pattern_create_linear (width/8, 0, 7*width/8, 0);
    cairo_pattern_add_color_stop_rgba (linpat, 0.0,  0, .1, 0.8, 0.5);
    cairo_pattern_add_color_stop_rgba (linpat, 0.5,  0.8, .5, 0, 0.5);
    cairo_pattern_add_color_stop_rgba (linpat, 1,  .5, .9, .4, .5);
    cairo_set_source(cr, linpat);

    for(i=0;i<NUML;i++) {
            cairo_move_to(cr,width*7/8,vpos[i]);
            cairo_line_to(cr,hpos[i],vpos[i]);
            cairo_stroke(cr);
    }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "lenlin2.png");
    cairo_pattern_destroy (linpat);
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(hpos);
    free(vpos);


    return 0;
}
