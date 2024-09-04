/* Cairo has a simple bezier (path, I ithink is also has a colour gradient)
 * and it's not called bezier at all, but curve_to() 
 * this zero version of bez, is the eample in
 * https://www.cairographics.org/samples/
*/
#include <cairo/cairo.h>
#include <math.h>

#define IW 640. // image/canvas width
#define IH 480. // height

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);
    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    double x=40,  y=IH/2.;
    double x3=IW-80,  y3=IH/2.;
    double xdist=x3-x;

    double radi=IH/4.;

    cairo_set_line_width (cr, 3.0);
    cairo_move_to (cr, x, y);
    cairo_line_to (cr, x3, y3);

    // try with slope or angle
    printf("cos pi/4=%2.4f\n", sin(M_PI/6.));
    double x2=radi*cos(M_PI_4);
    double y2=radi*sin(M_PI_4);
    cairo_move_to (cr, x, y);
    cairo_line_to (cr, x2, y2);
    
    cairo_move_to (cr, x, y);
    cairo_line_to (cr, x2, y2);
    
    // try with slope or angle
    double x4=radi*cos(M_PI/6.);
    double y4=radi*sin(M_PI/6.);
    cairo_move_to (cr, x, y);
    cairo_line_to (cr, x4, y4);
    
    cairo_stroke (cr);
    
    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "sl0.png");
    cairo_surface_destroy (surface);
    return 0;
}
