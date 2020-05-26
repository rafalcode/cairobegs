/* simplest experiment to divide a screen out and draw lines */
#include <cairo/cairo.h>

#define VBARNUMS 6
#define HBARNUMS 6

int main (int argc, char *argv[])
{
    int i, width=480, height=480;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* use the scale command to normalise all subsequent dimensions */
    // cairo_scale (cr, 240, 240);
    /* vertical divider how ar ewe going to section off the screen vertically */
    int vbar=height/VBARNUMS;
    int vpos[VBARNUMS];
    /* arrange array of positions */
    vpos[0]=vbar/2;
    for(i=1;i<VBARNUMS;i++)
        vpos[i] = vpos[i-1] + vbar;


    /* Drawing code goes here */
    cairo_set_line_width (cr, 4);
    cairo_set_source_rgba(cr, 0.25, 0.8, 0.25, 0.6);
    for(i=0;i<VBARNUMS;i++) {
        cairo_move_to(cr, width/2 -50, vpos[i]);
        cairo_line_to(cr, width/2 +50, vpos[i]);
        cairo_stroke (cr);
        cairo_new_path(cr);
    }


    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "lines.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}
