/* this is the cairo tute. Short, but the points are fundamental
ref: 
https://www.cairographics.org/tutorial/
*/
#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[])
{

    int  w=480, h=480;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);
    cairo_t *cr = cairo_create (surface);
    cairo_rectangle (cr, 0, 0, w, h); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    cairo_move_to (cr, w*.2, h*.2);
    cairo_rel_curve_to (cr, w*.4, -h*.05, w*.6, h*.05, w*.6, 0);
    cairo_rel_line_to (cr, 0, h*.1);
    cairo_rel_curve_to (cr, 0, h*.05, -w*.4, -h*.05, -w*.6, 0);
    cairo_set_source_rgb(cr, .9, .9, .9); /*  final number is alpha, 1.0 is opaque */
    cairo_close_path (cr);
    cairo_stroke(cr);

    cairo_save(cr);

    cairo_translate(cr, 0, 100);
    cairo_scale(cr, .7, .7);
    cairo_move_to (cr, w*.2, h*.2);
    cairo_rel_curve_to (cr, w*.4, -h*.05, w*.6, h*.05, w*.6, 0);
    cairo_rel_line_to (cr, 0, h*.1);
    cairo_rel_curve_to (cr, 0, h*.05, -w*.4, -h*.05, -w*.6, 0);
    cairo_set_source_rgb(cr, .9, .9, .9); /*  final number is alpha, 1.0 is opaque */
    cairo_close_path (cr);
    cairo_stroke(cr);

    cairo_restore(cr);

    cairo_move_to (cr, w*.2, h*.8);
    cairo_rel_curve_to (cr, w*.4, -h*.05, w*.6, h*.05, w*.6, 0);
    cairo_rel_line_to (cr, 0, h*.1);
    cairo_rel_curve_to (cr, 0, h*.05, -w*.4, -h*.05, -w*.6, 0);
    cairo_set_source_rgb(cr, .9, .9, .9); /*  final number is alpha, 1.0 is opaque */
    cairo_close_path (cr);
    cairo_stroke(cr);


    cairo_destroy(cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "tu2.png");
    cairo_surface_destroy (surface);

    return 0;
}
