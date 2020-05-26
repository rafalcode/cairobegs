/* spirograpgh attempt with points. */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>

#define MAXITS 2048

int main (int argc, char *argv[])
{
    int i, width=640, height=640;
    int xcentre=width/2, ycentre=height/2;

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    float radb=200,rads=10, pencil=50, t=0;
    float *xsta, *ysta;
    xsta = calloc(MAXITS,sizeof(float));
    ysta = calloc(MAXITS,sizeof(float));
    /*  initial positioning */
    int x0 = xcentre;
    int y0 = ycentre;
    // cairo_move_to(cr, x0, y0);
    cairo_translate(cr, x0, y0);
//    cairo_set_source_rgba (cr, .9, 0.4, 0.4, 0.95); /*  final number is alpha, 1.0 is opaque */
//        cairo_arc(cr, x0, y0, 5, 0, 2 * M_PI);
    cairo_set_source_rgba (cr, .4, 0.8, 0.6, 0.65); /*  final number is alpha, 1.0 is opaque */
    /*  allocation of the pt. arrays */
    for(i=0; i<MAXITS; ++i) {
        t=i*2*M_PI/MAXITS;
        xsta[i] =(radb-rads)*cos(t) + pencil*cos((radb-rads)*t/rads);
        ysta[i]=(radb-rads)*sin(t) - pencil*sin((radb-rads)*t/rads);
        // cairo_line_to(cr, xsta[i], ysta[i]);
        // cairo_move_to(cr, xsta[i], ysta[i]);
        cairo_arc(cr, xsta[i], ysta[i], 1, 0, 2 * M_PI);
        cairo_fill(cr);
    }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "hypdots.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    free(xsta);
    free(ysta);

    return 0;
}
