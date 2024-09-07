/* Lessons: Cairo does not handlethis will take a round clip of a png file */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define wha 60
#define wha2 20
#define ANG0 M_PI*1.07
#define ANG1 M_PI*1.07+M_PI_2

int main (int argc, char *argv[])
{
    int w=640, h=480;

    cairo_surface_t *surf2 = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h); //twice as wide
    cairo_t *cr = cairo_create (surf2);
    cairo_rectangle (cr, 0, 0, w, h); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, .9, .9, .9, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    //arrow
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_set_line_width (cr, 5.0);

    float x1=w/4, y1=h/4;
    float x2=x1+300, y2=y1+200;
    float slo=(y2-y1)/(x2-x1);
    printf("atan=%2.6f\n", atan(slo)); 
    printf("perp atan=%2.6f\n", atan(-1/slo));  // yes this is how
    float atn= atan(slo); 
    cairo_move_to (cr, x1, y1);
    cairo_line_to(cr, x2, y2);
 // ref. https://stackoverflow.com/questions/10316180/how-to-calculate-the-coordinates-of-a-arrowhead-based-on-the-arrow
    // backward direction vector:
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

    printf("P1=%2.2f,%2.2f\n", px1, py1); 
    printf("P2=%2.2f,%2.2f\n", px2, py2); 
    cairo_move_to (cr, px1, py1);
    cairo_line_to (cr, x2, y2);
    cairo_line_to (cr, px2, py2);

    cairo_stroke (cr);

    cairo_move_to (cr, x1+80, y1);
    cairo_line_to(cr, x2+80, y2);
    cairo_rel_line_to(cr, 50*cos(ANG0), 50*sin(ANG0));
    cairo_rel_line_to(cr, 50*cos(ANG1), 50*sin(ANG1));
    cairo_stroke (cr);


    cairo_destroy (cr);

    cairo_surface_write_to_png (surf2, "arro3.png");
    cairo_surface_destroy (surf2);

    return 0;
}
