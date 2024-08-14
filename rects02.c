/* a 9 by nine matrix of rectangles 
 * the first in a series exploring heatmap colors*/
/* another case of coming back to something and it not working at all */
#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{

	if(argc!=4) {
		printf("Error. Pls supply argument (name of file).\n");
		exit(EXIT_FAILURE);
	}
    int gw=atoi(argv[1]);
    int gh=atoi(argv[2]);
    int numsq=atoi(argv[3]);

    cairo_surface_t *surface;
    cairo_t *cr;

    int minb=10; /// minimum border
    int wsq0=(gw-(numsq+1)*minb)/numsq;
    int h0=wsq0; // because square
    float y0=(gh-h0)/2;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, gw, gh);
    cr = cairo_create(surface);

    cairo_rectangle (cr, 0, 0, gw, gh); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    int i;
    for(i=1;i<=numsq;++i)  {
        cairo_set_source_rgb(cr, 0.2, 0.8, 0.9);
        cairo_rectangle (cr, i*minb+(i-1)*wsq0, y0, wsq0, h0);
        cairo_fill (cr);
     }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "rects01.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}

