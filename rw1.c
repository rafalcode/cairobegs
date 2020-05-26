/* a more advanced version of image block example */

#include <cairo/cairo.h>
#include <stdio.h>
#include <math.h>

/* principal image and block settings */
#define IMWIDTH 640
#define IMHEIGHT IMWIDTH

#define STEPRAD 20 /*  mne: step radius */

int cs1[16][3] = { {0x33, 0x66, 0xFF}, {0x66, 0x33, 0xFF}, {0xCC, 0x33, 0xFF}, {0xFF, 0x33, 0xCC}, {0xFF, 0x33, 0x66}, {0xFF, 0x66, 0x33}, {0xFF, 0xCC, 0x33}, {0xCC, 0xFF, 0x33}, {0x66, 0xFF, 0x33}, {0x33, 0xFF, 0x66}, {0x33, 0xFF, 0xCC}, {0x33, 0xCC, 0xFF}, {0x00, 0x3D, 0xF5}, {0x00, 0x2E, 0xB8}, {0xF5, 0xB8, 0x00}, {0xB8, 0x8A, 0x00} };

int main (int argc, char *argv[])
{
    cairo_surface_t *surface;
    cairo_t *cr;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMWIDTH, IMHEIGHT);
    cr = cairo_create (surface);
    /* First we set our general background */
    cairo_rectangle (cr, 0, 0, IMWIDTH, IMHEIGHT); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    int xc=IMWIDTH/4;
    int yc=IMHEIGHT/4;

    cairo_set_line_width(cr, .5);

    int i, j, k;
    for (i=0; i<STEPRAD; i++) {
        for (j=0; j<3; j+=2) {
            for (k=0; k<3; k+=2) {
                cairo_set_source_rgba(cr, cs1[2*j+k][0]/255.0, cs1[2*j+k][1]/255.0, cs1[2*j+k][2]/255.0, .8);
                cairo_arc (cr, xc*(j+1), yc*(k+1), i*5, 0, 2*M_PI);
                //     cairo_line_to (cr, xc, yc);
                cairo_stroke (cr);

            }
        }
    }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "rw1.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}
