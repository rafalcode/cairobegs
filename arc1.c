#include <cairo/cairo.h>
#include <math.h>

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 640, 480);

    /*  then a cario_type is created from this surface */
    cairo_t *cr = cairo_create (surface);

    /*  set some values first */
    double xc = 364.0, yc = 264.0; /* center of first arc */
    double radius = 150.0;
    double angle1 = 45.0  * (M_PI/180.0);  /* angles are specified */
    double angle2 = 180.0 * (M_PI/180.0);  /* in radians           */

    cairo_set_line_width (cr, 15.0);
    cairo_arc (cr, xc, yc, radius, angle1, angle2);
    cairo_stroke (cr);

    /* draw helping lines */
    cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
    cairo_set_line_width (cr, 6.0);

    cairo_arc (cr, xc, yc, 10.0, 0, 2*M_PI);
    cairo_fill (cr);

    cairo_arc (cr, xc, yc, radius, angle1, angle1);
    cairo_line_to (cr, xc, yc);
    cairo_arc (cr, xc, yc, radius, angle2, angle2);
    cairo_line_to (cr, xc, yc);
    cairo_stroke (cr);

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "arc.png");
    cairo_surface_destroy (surface);
    return 0;
}
