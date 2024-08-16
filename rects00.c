/* a 9 by nine matrix of rectangles 
 * the first in a series exploring heatmap colors*/
/* another case of coming back to something and it not working at all */
#include <cairo/cairo.h>
#include <stdio.h>

#define GW 640 /* grid width */
#define GH 480 /* grid height */
#define BW 120 /* grid width */
#define BH 100 /* grid height */
#define BPx 40 /* starting pt of block in xdir */
#define BPy 200 /* starting pt of block in ydir */

int main (int argc, char *argv[])
{

    cairo_surface_t *surface;
    cairo_t *cr;
    const int howm=2;

    int y0=90;
    int h0=GH-2*y0;
    int w0=h0; // because square
    int howm2= GW/w0;
    printf("howm2: %i\n", howm2); 
    float howm3= (float)(GW%w0)/(1+howm2);
    printf("howm3: %2.2f\n", howm3); 

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, GW, GH);
    cr = cairo_create (surface);
    /* Examples are in 1.0 x 1.0 coordinate space */
    cairo_rectangle (cr, 0, 0, GW, GH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    int i;
    for(i=1;i<=howm2;++i)  {

        cairo_set_source_rgb(cr, 0.2, 0.8, 0.9);
        cairo_rectangle (cr, i*howm3+(i-1)*w0, y0, w0, h0);
        cairo_fill (cr);
     }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "rects00.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}

