/* fr for frams */
#include <cairo/cairo.h>
#include <math.h>

#define IW 640 // image/canvas width
#define IH 480 // height
#define LMAR 20
#define RMAR 20
#define TMAR 60
#define BMAR 30

#define FT0 40 // frame thickness

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);

    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, .9, .9, .9, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    float x1=LMAR;
    float y1=TMAR;
    float y2=TMAR;
    float xspace=IW-LMAR-RMAR; // drawable space
    float x2=LMAR+xspace; // drawable space
    float yspace=IH-TMAR-BMAR; // drawable space

    cairo_set_line_width (cr, 1.0);

    cairo_move_to (cr, x1, y1);
    cairo_line_to (cr, x2, y2);
    // cairo_move_to (cr, x2, y2);  // checked .. this is not part of the path, you need a line_to().

    float x3=x2-FT0;
    float y3=y2+FT0;
    cairo_line_to (cr, x3, y3);
    float x4=x1+FT0;
    float y4=y3;
    cairo_line_to (cr, x4, y4);
    cairo_close_path(cr);
    // cairo_stroke_preserve(cr);
    // cairo_set_source_rgb(cr, .8, 0.1, 0.4);
    // cairo_fill(cr);

    float yy1=y1+yspace;
    float yy2=yy1-FT0;
    cairo_line_to (cr, x1, yy1);
    cairo_line_to (cr, x4, yy2);
    cairo_line_to (cr, x4, y4);
    cairo_close_path(cr);

    cairo_move_to (cr, x1, yy1);
    cairo_line_to (cr, x2, yy1);
    cairo_line_to (cr, x3, yy2);
    cairo_line_to (cr, x4, yy2);
    cairo_close_path(cr);

    cairo_move_to (cr, x2, yy1);
    cairo_line_to (cr, x2, y2);
    cairo_line_to (cr, x3, y3);
    cairo_line_to (cr, x3, yy2);
    cairo_close_path(cr);
    // cairo_move_to (cr, x1, yy1);
    // cairo_line_to (cr, x2, yy1);
    // cairo_line_to (cr, x3, yy2);
    // cairo_line_to (cr, x4, yy2);
    // cairo_close_path(cr);

    // cairo_line_to (cr, x1, y1);
    // cairo_move_to (cr, x2, y2);
    // cairo_line_to (cr, x2, yy1);
    // cairo_move_to (cr, x3, yy2);
    // cairo_line_to (cr, x3, y3);
    // cairo_move_to (cr, x4, yy2);
    // cairo_line_to (cr, x4, y4);
    // hopefully all that's taken place
    //
    //
    // let's see matrix
    // cairo_matrix_t *m=malloc
    // printf("xx=%4.4f, yx=%4.4f, xy=%4.4f, yy=%4.4f, x0=%4.4f, y-=%4.4f\n", xx, yx, xy, yy, x0, y0);

    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);
    
    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "fr0.png");
    cairo_surface_destroy (surface);
    return 0;
}
