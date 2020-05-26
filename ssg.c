#include <cairo/cairo.h>

int main (int argc, char *argv[])
{
    cairo_surface_t *surface;
    cairo_t *cr;
	cairo_pattern_t *radpat;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 480, 480);
    cr = cairo_create (surface);

    /* Drawing code goes here */
    radpat = cairo_pattern_create_radial (50, 50, 50,  250, 250, 100);
    cairo_pattern_add_color_stop_rgb (radpat, 100,  1.0, 0.8, 0.8);
    cairo_pattern_add_color_stop_rgb (radpat, 20,  0.9, 0.0, 0.0);

    int i, j;
    for (i=1; i<10; i++)
        for (j=1; j<10; j++)
            cairo_rectangle (cr, i/10.0 - 0.04, j/10.0 - 0.04, 0.08, 0.08);
    cairo_set_source (cr, radpat);
    cairo_fill (cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "ssg.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}

