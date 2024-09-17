/* What this progrwam rot0.c proves is that the rotate starts at (0,0 - topleft)
 * if your component does not start there, then the rotation will be uncontrolled.
 * And you almost alway have to use translate with it
*/
#include <cairo/cairo.h>
#include <math.h>

#define IW 640 // image/canvas width
#define IH 480 // height

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);
    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, .9, .9, .9, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    double x0=IW/2-IW*.2;
    double x=IW/2+IW*.2;
    double y0=IH/2;
    
    cairo_set_line_width (cr, 20);

    cairo_translate(cr, IW/2, IH/2);

    cairo_move_to(cr, 0, 0);
    cairo_line_to (cr, x0, 0);
    cairo_set_source_rgba (cr, .6, .7, .9, 0.3); /*  final number is alpha, 1.0 is opaque */
    cairo_stroke(cr);

    cairo_rotate(cr, .25);
    cairo_move_to(cr, 0, 0);
    cairo_line_to (cr, x0, 0);
    cairo_set_source_rgba (cr, .8, .3, .5, 0.3); /*  final number is alpha, 1.0 is opaque */
    
    cairo_stroke(cr);
    
    cairo_destroy(cr);
    cairo_surface_write_to_png(surface, "rot0.png");
    cairo_surface_destroy (surface);
    return 0;
}
