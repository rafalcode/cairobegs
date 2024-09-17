/* Lessons: Cairo does not handlethis will take a round clip of a png file */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define LWID 3

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
    cairo_set_line_width (cr, LWID);

    // we choose two points:
    float x1=w/4, y1=h/4;
    float x2=x1+300, y2=y1+200;
    // slope of a lien through these two?
    float slo=(y2-y1)/(x2-x1);

    // arctan of slope gives the angle
    float atn= atan(slo); 
    float atp= atan(-1/slo);  // this is angle of the perpendicular though 90 degs would also do it.

    cairo_move_to (cr, x1+240, y1); // move to start
    cairo_rel_line_to(cr, +80*cos(atn), +80*sin(atn)); // use slope to generate a segment.
    cairo_stroke(cr);                                     

    float qx0=x1+240+60*cos(atn), qy0=y1+60*sin(atn);
    float qx1=x1+240+80*cos(atn), qy1=y1+80*sin(atn);
    float qx2=qx1+ 40*cos(atn-M_PI+.5), qy2= qy1 +40*sin(atn-M_PI+.5); // this is lower point.
    float qx3=qx1+ 40*cos(atn+M_PI-.5), qy3= qy1 +40*sin(atn+M_PI-.5);
    cairo_move_to(cr,qx2,qy2);
    cairo_line_to(cr,qx1,qy1);
    cairo_line_to(cr,qx3,qy3);
    cairo_line_to(cr,qx0,qy0);
    cairo_line_to(cr,qx2,qy2);
    cairo_close_path(cr);

    cairo_stroke_preserve(cr);                                     
    cairo_fill(cr);

    cairo_destroy (cr);

    cairo_surface_write_to_png (surf2, "arrow3.png");
    cairo_surface_destroy (surf2);

    return 0;
}
