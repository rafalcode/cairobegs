/* Cairo has a simple bezier (path, I ithink is also has a colour gradient)
 * and it's not called bezier at all, but curve_to() 
 * this zero version of bez, is the eample in
 * https://www.cairographics.org/samples/
*/
#include <cairo/cairo.h>
#include <math.h>

#define IW 640 // image/canvas width
#define IH 480 // height

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);

    double x=25.6,  y=128.0;
    double x1=102.4, y1=230.4,
           x2=153.6, y2=25.6,
           x3=230.4, y3=128.0;
    
    cairo_move_to (cr, x, y);
    cairo_curve_to (cr, x1, y1, x2, y2, x3, y3);
    
    cairo_set_line_width (cr, 10.0);
    cairo_stroke (cr);
    
    cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
    cairo_set_line_width (cr, 6.0);
    cairo_move_to (cr,x,y);   cairo_line_to (cr,x1,y1);
    cairo_move_to (cr,x2,y2); cairo_line_to (cr,x3,y3);
    cairo_stroke (cr);


    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "bez0.png");
    cairo_surface_destroy (surface);
    return 0;
}
