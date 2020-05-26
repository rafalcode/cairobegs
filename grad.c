/*  Mondrianesque effort which is pretty useless really */
#include <cairo/cairo.h>

int main (int argc, char *argv[])
{
    cairo_surface_t *surface;
    cairo_t *cr;
	cairo_pattern_t *radpat;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 480, 480);
    cr = cairo_create (surface);

    cairo_rectangle (cr, 0, 0, 480, 480); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);


    /* Drawing code goes here */
    radpat = cairo_pattern_create_radial (0.25, 0.25, 0.1,  0.5, 0.5, 0.5);
    cairo_pattern_add_color_stop_rgb (radpat, 0,  1.0, 0.8, 0.8);
    cairo_pattern_add_color_stop_rgb (radpat, 1,  0.9, 0.0, 0.0);
    cairo_set_line_width (cr, 10);

    cairo_rectangle (cr, 120, 120, 80, 80); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source (cr, radpat);
    cairo_fill (cr);

    cairo_move_to(cr, 240 -50, 240);
    cairo_line_to(cr, 240 +50, 240);
    cairo_set_source (cr, radpat);
    cairo_stroke (cr);


    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "grad.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}

