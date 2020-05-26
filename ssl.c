#include <cairo/cairo.h>

#define width 480
#define height 480

int main (int argc, char *argv[])
{
    cairo_surface_t *surface;
    cairo_t *cr;
    cairo_pattern_t *linpat;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create (surface);
    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    linpat = cairo_pattern_create_linear (width/8, height/4, 7*width/8, height/4);
    /* the first arg after the linpat is the relative position */
    cairo_pattern_add_color_stop_rgba (linpat, 0.00,  0, .3, 0, 0);
    cairo_pattern_add_color_stop_rgba (linpat, 0.5,  0, 1, 0, 0.5);
    cairo_pattern_add_color_stop_rgba (linpat, 1,  1, 1, 1, 0);

//    cairo_rectangle (cr, width/4, height/4, width/2, height/4);
    cairo_move_to(cr, width/4, height/4);
    cairo_line_to(cr, width/2, height/4);
     cairo_set_line_width (cr, 10);
    cairo_set_source (cr, linpat);
//     cairo_set_source_rgba(cr, 0.2, 0.7, 0.3, .5);
    cairo_stroke (cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "ssl.png");
    cairo_pattern_destroy (linpat);
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}
