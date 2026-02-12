/* this would need cairo 1.18, bookworm only has 1.16, the pdf create won't work */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    int w=640, h=480;

    cairo_surface_t *image;

    // cairo_arc (cr, 128.0, 128.0, 76.8, 0, 2*M_PI);
    // cairo_clip (cr);
    // cairo_new_path (cr); /* path not consumed by clip()*/

    // unfort, no such thang:1
    // image = cairo_image_surface_create_from_jpg("marspopm.jpg");
    // // so you must convert to png ...
    image = cairo_image_surface_create_from_png("marspopm.png");
    w = cairo_image_surface_get_width (image);
    h = cairo_image_surface_get_height (image);
    printf("w=%i,h=%i\n", w, h); 

    cairo_surface_t *pdfsurf= cairo_pdf_surface_create ("cl3a.pdf", 842, 595); // landscape
    cairo_t *cr = cairo_create(pdfsurf);
    cairo_scale(cr, .15, .15);
    cairo_set_source_surface (cr, image, 0, 0);
    cairo_paint(cr);

    cairo_destroy(cr);
    cairo_surface_destroy (pdfsurf);
    cairo_surface_destroy (image);

    return 0;
}
