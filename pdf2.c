/*  OK, let's see how to creata */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cairo/cairo.h>
/* for PDF you ned to include thie followng header file */
#include <cairo/cairo-pdf.h>

/* principal image and block settings */
#define IMWIDTH 640
#define IMHEIGHT IMWIDTH

#define STEPRAD 20 /*  mne: step radius */
// #define CAIRO_HAS_PDF_SURFACE 1 // actually did not seem to be necessary.

int cs1[16][3] = { {0x33, 0x66, 0xFF}, {0x66, 0x33, 0xFF}, {0xCC, 0x33, 0xFF}, {0xFF, 0x33, 0xCC}, {0xFF, 0x33, 0x66}, {0xFF, 0x66, 0x33}, {0xFF, 0xCC, 0x33}, {0xCC, 0xFF, 0x33}, {0x66, 0xFF, 0x33}, {0x33, 0xFF, 0x66}, {0x33, 0xFF, 0xCC}, {0x33, 0xCC, 0xFF}, {0x00, 0x3D, 0xF5}, {0x00, 0x2E, 0xB8}, {0xF5, 0xB8, 0x00}, {0xB8, 0x8A, 0x00} };

int main(int argc, char *argv[])
{

    /* First Cairo considerations */
    cairo_surface_t *surface = cairo_pdf_surface_create ("teiest.pdf", IMWIDTH, IMHEIGHT);
    cairo_t *cr = cairo_create (surface);
    /* Gen background */
    cairo_rectangle (cr, 0, 0, IMWIDTH, IMHEIGHT); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /*  onto prog */
    unsigned int RMX=RAND_MAX;
    RMX++;
    int i, j, *rint;
    float *rarr;
    rarr=malloc(4*4*sizeof(float));
    rint=malloc(4*4*sizeof(int));
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j) {
            rint[4*i+j]=rand();
            rarr[4*i+j]=(float)rint[4*i+j]/RMX;
            rarr[4*i+j] *=M_PI*(i+1)/4;
        }

    float xco2=IMWIDTH/2, yco2=IMHEIGHT/2;

    cairo_move_to(cr, xco2, yco2);
    for(i=0; i<4; ++i) {
        cairo_set_source_rgba(cr, .2*i, .9, .8, .7);
        xco2 = 20*(i+1)*cos(rarr[(i+1)]*M_PI);
        yco2 = 20*(i+1)+(i+1)*sin(rarr[(i+1)]*M_PI);
        cairo_line_to (cr, xco2, yco2);
        cairo_stroke(cr);
    }

    // cairo_surface_write_to_png (surface, "rw1.png");
    cairo_rectangle (cr, 40, 40, 40, 40); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, .128, 0, .5, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);
    cairo_copy_page(cr);
    cairo_rectangle (cr, 80, 80, 80, 80); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, .528, 0, .8, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);
    cairo_copy_page(cr);
    cairo_rectangle (cr, 120, 120, 120, 120); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, .148, 0.4, .5, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);
    cairo_copy_page(cr);
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(rarr);
    return 0;
}
