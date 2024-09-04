/* Cairo has a simple bezier (path, I ithink is also has a colour gradient)
 * and it's not called bezier at all, but curve_to() 
 * this zero version of bez, is the eample in
 * https://www.cairographics.org/samples/
 *
 * How to get a sine wave with beziers? I thought 0,3/8,5/8,1 woud do it
 * I calcualted that from teh examples
 * but I actuqally don't think it does.
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
    double x1=3*xdist/8., y1=0;
    double x2=5*xdist/8., y2=IH;
    cairo_arc(cr, x1, y1, 10, 0, 2 * M_PI);
    cairo_fill(cr);
    cairo_arc(cr, x2, y2, 10, 0, 2 * M_PI);
    cairo_fill(cr);
    
    cairo_move_to (cr, x, y);
    cairo_curve_to (cr, x1, y1, x2, y2, x3, y3);
    
    cairo_set_line_width (cr, 3.0);
    cairo_stroke (cr);
    
    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "bez2.png");
    cairo_surface_destroy (surface);
    return 0;
}
