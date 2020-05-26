/* a more advanced version of image block example */

#include <cairo/cairo.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

    float *rarr, xco1, yco1, xco2, yco2; /* mne: center offsets */
    rarr=malloc(4*40*sizeof(float));
    for(i=0; i<4*40; ++i) 
        rarr[i]=(float)rand()/(RAND_MAX+1);

    for (j=0; j<3; j+=2) {
        for (k=0; k<3; k+=2) {
            cairo_set_source_rgba(cr, cs1[2*j+k][0]/255.0, cs1[2*j+k][1]/255.0, cs1[2*j+k][2]/255.0, .8);
            cairo_move_to(cr, xc*(j+1), yc*(k+1));
            for (i=0; i<STEPRAD; i++) {
//                 xco1 = xc*(j+1)+i*cos(rarr[i]*M_PI);
//                 yco1 = yc*(k+1)+i*sin(rarr[i]*M_PI);
                xco2 = xc*(j+1)+(i+1)*cos(rarr[(i+1)]*M_PI);
                yco2 = yc*(k+1)+(i+1)*sin(rarr[(i+1)]*M_PI);
//                 cairo_move_to (cr, xco1, yco1);
                cairo_line_to (cr, xco2, yco2);
                cairo_stroke (cr);
            }
        }
    }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "rw1.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(rarr);

    return 0;
}
