// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
#include<cairo/cairo.h>
#include<math.h>

#define IMWIDTH 640
#define IMHEIGHT IMWIDTH
// #define MYPI 3.141593
// math.h does not define M_PI by default.
// ugh?
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
// so math.h, it's true it has
//  __USE_MISC || defined __USE_XOPEN
//  before M_PI

#define __USE_XOPEN

int main (int argc, char *argv[])
{
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMWIDTH, IMHEIGHT);
    cairo_t *cr = cairo_create (surface);

    /* a custom shape that could be wrapped in a function */
    double x         = 25.6,        /* parameters like cairo_rectangle */
           y         = 25.6,
           width         = 204.8,
           height        = 204.8,
           aspect        = 1.0,     /* aspect ratio */
           corner_radius = height / 10.0;   /* and corner curvature radius */

    double radius = corner_radius / aspect;
    double degrees = M_PI / 180.0; //cluelessas to why M_PI is not being picked up/
    // double degrees = MYPI / 180.0;

    cairo_new_sub_path (cr);
    cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path (cr);

    cairo_set_source_rgb (cr, 0.5, 0.5, 1);
    cairo_fill_preserve (cr);
    cairo_set_source_rgba (cr, 0.5, 0, 0, 0.5);
    cairo_set_line_width (cr, 10.0);
    cairo_stroke (cr);

    cairo_surface_write_to_png (surface, "rour.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    return 0;
}
