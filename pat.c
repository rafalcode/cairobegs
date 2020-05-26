/* pattern rectangles */
#include <cairo/cairo.h>
#include <math.h>

#define IMWIDTH 640
#define IMHEIGHT IMWIDTH
#define DM 2

int main (int argc, char *argv[])
{

    cairo_surface_t *surface1 = cairo_image_surface_create_from_png("wat2.png");
    cairo_surface_t *surface2 = cairo_image_surface_create_from_png("lef2.png");
    cairo_surface_t *surface3 = cairo_image_surface_create_from_png("cr2.png");
    cairo_surface_t *surface4 = cairo_image_surface_create_from_png("ch2.png");

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMWIDTH, IMHEIGHT);
    cairo_t *cr = cairo_create (surface);

    cairo_rectangle (cr, 0, 0, IMWIDTH, IMHEIGHT); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    cairo_pattern_t *pattern1;
    cairo_pattern_t *pattern2;
    cairo_pattern_t *pattern3;
    cairo_pattern_t *pattern4;


    pattern1 = cairo_pattern_create_for_surface(surface1);
    pattern2 = cairo_pattern_create_for_surface(surface2);
    pattern3 = cairo_pattern_create_for_surface(surface3);
    pattern4 = cairo_pattern_create_for_surface(surface4);


    cairo_set_source(cr, pattern1);
    cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
    cairo_rectangle(cr, 20, 20, 100, 100);
    cairo_fill(cr);

    cairo_set_source(cr, pattern2); 
    cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT); 
    cairo_rectangle(cr, 150, 20, 100, 100);
    cairo_fill(cr);

    cairo_set_source(cr, pattern3);
    cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
    cairo_rectangle(cr, 20, 140, 100, 100);
    cairo_fill(cr);

    cairo_set_source(cr, pattern4);
    cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
    cairo_rectangle(cr, 150, 140, 100, 100);
    cairo_fill(cr);

    cairo_pattern_destroy(pattern1);
    cairo_pattern_destroy(pattern2);
    cairo_pattern_destroy(pattern3);
    cairo_pattern_destroy(pattern4);

    cairo_destroy(cr);

    cairo_surface_destroy(surface1);
    cairo_surface_destroy(surface2);
    cairo_surface_destroy(surface3);
    cairo_surface_destroy(surface4);
    cairo_surface_write_to_png (surface, "pat.png");
    cairo_surface_destroy (surface);

    return 0;
}
