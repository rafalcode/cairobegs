/* Cairo has a simple bezier (path, I ithink is also has a colour gradient)
 * and it's not called bezier at all, but curve_to() 
 * this zero version of bez, is the eample in
 * https://www.cairographics.org/samples/
*/
#include <cairo/cairo.h>
#include <math.h>

#define IW 640 // image/canvas width
#define IH 480 // height
#define LMAR 20
#define RMAR 20
#define TMAR 30
#define BMAR 30

#define FT0 20 // frame thickness

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);

    float x1=LMAR;
    float y1=TMAR;
    float y2=TMAR;
    float x2=LMAR+IW-LMAR-RMAR; // drawable space

    cairo_move_to (cr, x1, y1);
    cairo_line_to (cr, x2, y2);

    float x3=x2-FT0;
    float y3=y2+FT0;
    cairo_line_to (cr, x3, y3);
    float x4=x1+FT0;
    float y4=y3;
    cairo_line_to (cr, x4, y4);

    // let's try a rotation:
    // cairo_translate(cr, x2+1.5*LMAR, .5*TMAR);
    cairo_translate(cr, x2+LMAR+10, IH-BMAR);
    // cairo_translate(cr, x2, y2);
    // cairo_rotate(cr,1.5707);
    cairo_rotate(cr,2*1.5707);

    cairo_move_to (cr, x1, y1);
    cairo_line_to (cr, x2, y2);
    cairo_line_to (cr, x3, y3);
    cairo_line_to (cr, x4, y4);
    // hopefully all that's taken place
    //
    //
    // let's see matrix
    // cairo_matrix_t *m=malloc
    // printf("xx=%4.4f, yx=%4.4f, xy=%4.4f, yy=%4.4f, x0=%4.4f, y-=%4.4f\n", xx, yx, xy, yy, x0, y0);

    cairo_set_line_width (cr, 1.0);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);
    
    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "fr0.png");
    cairo_surface_destroy (surface);
    return 0;
}
