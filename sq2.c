#include <cairo/cairo.h>
#include <math.h>

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 640, 480);

    /*  then a cario_type is created from this surface */
    cairo_t *cr = cairo_create (surface);

    /*  set some values first */
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_move_to (cr, 20, 20);
    cairo_line_to (cr, 420, 420);
    cairo_move_to (cr, 420, 0);
    cairo_line_to (cr, 0, 420);
    cairo_set_line_width (cr, 15);
    cairo_stroke (cr);

    cairo_rectangle (cr, 20, 20, 210, 210);
    cairo_set_source_rgba (cr, 1, 0, 0, 0.80);
    cairo_fill (cr);

    cairo_rectangle (cr, 0, 210, 210, 210);
    cairo_set_source_rgba (cr, 0, 1, 0, 0.60);
    cairo_fill (cr);

    cairo_rectangle (cr, 210, 0, 210, 210);
    cairo_set_source_rgba (cr, 0, 0, 1, 0.40);
    cairo_fill (cr);

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "arc.png");
    cairo_surface_destroy (surface);
    return 0;
}
