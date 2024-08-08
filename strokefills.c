/* An exercise in stroke and fills.
 * In fact it's inconclusive. Best thing is just to close each path and don't try to save function calls */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cairo/cairo.h>

int main (int argc, char *argv[])
{
    cairo_surface_t *surface;
    cairo_t *cr;

    int  i, w=480, h=480;
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);
    cr = cairo_create (surface);
    /* Examples are in 1.0 x 1.0 coordinate space */
//     cairo_scale (cr, w, h);
    cairo_rectangle (cr, 0, 0, w, h); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* Drawing code goes here */
    cairo_set_line_width (cr, 5);
    cairo_set_source_rgb (cr, 1, 0.4, 0.6);

    cairo_move_to (cr, w*.25, h*.33);
    cairo_line_to (cr, w*.55, h*.33);
    cairo_line_to (cr, w*.55, h*.66);
    cairo_line_to (cr, w*.25, h*.66);
    cairo_close_path (cr);
    // cairo_line_to (cr, w*.25, h*.33);
    cairo_stroke_preserve(cr);

    cairo_set_source_rgb (cr, 0.3, 0.2, 0.3);
    cairo_fill(cr);
    cairo_set_source_rgb (cr, 1, 0.4, 0.6);

    cairo_move_to (cr, w*.55, h*.33);
    cairo_line_to (cr, w*.65, h*.33);
    cairo_line_to (cr, w*.65, h*.66);
    cairo_line_to (cr, w*.55, h*.66);
    cairo_close_path (cr);
    cairo_stroke_preserve(cr);

    cairo_set_source_rgb (cr, 0.2, 0.3, 0.3);
    cairo_fill(cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "pa2.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    return 0;
}

