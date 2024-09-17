/* Cairo has a simple bezier (path, I ithink is also has a colour gradient)
 * and it's not called bezier at all, but curve_to() 
 * this zero version of bez, is the eample in
 * https://www.cairographics.org/samples/
*/
#include<cairo/cairo.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

#define IW 640 // image/canvas width
#define IH 480 // height

void prtmat(cairo_matrix_t *mat)
{
    printf("xx=%4.4f xy=%4.4f x0=%4.4f\n", mat->xx, mat->xy, mat->x0);
    printf("yx=%4.4f yy=%4.4f y0=%4.4f\n", mat->yx, mat->yy, mat->y0);
}

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);
    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, .9, .9, .9, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    double x0=IW/2-IW*.2;
    double x=IW/2+IW*.2;
    double y0=IH/2;
    
    cairo_set_line_width (cr, 20);

    cairo_translate(cr, IW/2, IH/2);

    cairo_matrix_t *mat=malloc(sizeof(cairo_matrix_t));
    cairo_get_matrix(cr, mat);
    prtmat(mat);

    cairo_move_to(cr, 0, 0);
    cairo_line_to (cr, x0, 0);
    cairo_set_source_rgba (cr, .6, .7, .9, 0.3); /*  final number is alpha, 1.0 is opaque */
    cairo_stroke(cr);

    cairo_rotate(cr, .1);
    cairo_move_to(cr, 0, 0);
    cairo_line_to (cr, x0, 0);
    cairo_set_source_rgba (cr, .8, .3, .5, 0.3); /*  final number is alpha, 1.0 is opaque */
    
    cairo_stroke(cr);
    
    cairo_get_matrix(cr, mat);
    prtmat(mat);

    free(mat);
    cairo_destroy(cr);
    cairo_surface_write_to_png(surface, "rot1.png");
    cairo_surface_destroy (surface);
    return 0;
}
