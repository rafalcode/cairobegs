/* Lessons: Cairo does not handlethis will take a round clip of a png file */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define wha 40
int main (int argc, char *argv[])
{
    // int w=640, h=480;
    int w, h;

    // cairo_arc (cr, 128.0, 128.0, 76.8, 0, 2*M_PI);
    // cairo_clip (cr);
    // cairo_new_path (cr); /* path not consumed by clip()*/

    cairo_surface_t *surf = cairo_image_surface_create_from_png("Third_folio.png");
    w = cairo_image_surface_get_width (surf);
    h = cairo_image_surface_get_height (surf);
    printf("w=%i,h=%i\n", w, h); 

    cairo_surface_t *surf2 = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 2*w, h); //twice as wide
    cairo_t *cr = cairo_create (surf2);
    cairo_rectangle (cr, 0, 0, 2*w, h); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, .9, .9, .9, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    cairo_set_source_surface (cr, surf, 0, 0);
    cairo_paint (cr);
    //arrow
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_set_line_width (cr, 5.0);

    float x1=w+w/2;
    float y1=h/4;
    float x2=w/2;
    float y2=h/2;

    cairo_move_to (cr, x1, y1);
    cairo_line_to (cr, x2, y2);

    //arrow head
   float dx=x2-x1;
   float dy=y2-y1;
   float norm=sqrt(dx*dx+dy*dy);
   float udx=dx/norm;
   float udy=dy/norm;

   float sqr32=sqrt(3)*.5;
   float ax = udx * sqr32 - udy * .5;
    float ay = udx * .5 + udy * sqr32;
    float bx = udx * sqr32 + udy * .5;
    float by = -udx *.5 + udy*sqr32;

    float px1= x2 - wha * ax;
    float py1= y2 - wha * ay;
    float px2=x2 - wha * bx;
    float py2= y2 - wha * by;

    cairo_move_to (cr, px1, py1);
    cairo_line_to (cr, x2, y2);
    cairo_line_to (cr, px2, py2);

    cairo_stroke (cr);

    cairo_destroy (cr);

    cairo_surface_write_to_png (surf2, "cl4.png");
    cairo_surface_destroy (surf2);
    cairo_surface_destroy (surf);

    return 0;
}
