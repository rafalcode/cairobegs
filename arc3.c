#include <cairo/cairo.h>
#include <math.h>
#include<stdio.h>

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    // cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 640, 480);
    cairo_surface_t *surface = cairo_image_surface_create_from_png (argv[1]);
    printf("PNG IM width = %i, height = %i, offset %i\n", 
    cairo_image_surface_get_width(surface), cairo_image_surface_get_height(surface), cairo_image_surface_get_stride(surface) );

    /*  then a cario_type is created from this surface */
    cairo_t *cr = cairo_create (surface);

    /*  set some values first */
    double xc = 64.0, yc = 64.0; /* center of first arc */
    double radius = 50.0;
    double angle1 = 45.0  * (M_PI/180.0);  /* angles are specified */
    double angle2 = 180.0 * (M_PI/180.0);  /* in radians           */

    cairo_set_line_width (cr, 5.0);
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

    /* now another sort of arc */
    cairo_t *cr1 = cairo_create (surface);
    cairo_arc (cr1, 178.0, 178.0, 76.8, 0, 2 * M_PI);
    cairo_clip (cr1);

    cairo_new_path (cr1);  /*  current path is not
                               consumed by cairo_clip() */
    cairo_rectangle (cr1, 0, 0, 256, 256);
    cairo_fill (cr1);
    cairo_set_source_rgb (cr1, 0, 1, 0);
    cairo_move_to (cr1, 0, 0);
    cairo_line_to (cr, 256, 256);
    cairo_move_to (cr1, 256, 0);
    cairo_line_to (cr1, 0, 256);
    cairo_set_line_width (cr1, 10.0);
    cairo_stroke (cr1);

    /*  OK that's finished */
    cairo_move_to (cr, 50.0, 75.0);
    cairo_line_to (cr, 200.0, 75.0);

    cairo_move_to (cr, 50.0, 125.0);
    cairo_line_to (cr, 200.0, 125.0);

    cairo_move_to (cr, 50.0, 175.0);
    cairo_line_to (cr, 200.0, 175.0);

    cairo_set_line_width (cr, 5.0);
    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_stroke (cr);

    cairo_destroy (cr);
    cairo_destroy (cr1);
    cairo_surface_write_to_png (surface, "arc3.png");
    cairo_surface_destroy (surface);
    return 0;
}
