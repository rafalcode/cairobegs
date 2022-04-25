/* this will take a round clip of a png file */
#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>
#include <math.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    cairo_surface_t *surface = cairo_pdf_surface_create ("pdf0.pdf", 597.276, 841.89);
    cairo_t *cr = cairo_create (surface);

    cairo_surface_t *image = cairo_image_surface_create_from_png("dpg2.png");

    cairo_set_source_surface(cr, image, 1, 1);
    cairo_paint(cr);

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    cairo_surface_destroy(image);

    return 0;
}
