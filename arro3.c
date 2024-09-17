/* Lessons: Cairo does not handlethis will take a round clip of a png file */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define wha 60
#define wha2 20
#define ANG0 M_PI*1.07
#define ANG1 M_PI*1.07+M_PI_2
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

    float x1=w/4, y1=h/4;
    float x2=x1+300, y2=y1+200;
    float slo=(y2-y1)/(x2-x1);
    printf("atan=%2.6f\n", atan(slo)); 
    printf("perp atan=%2.6f\n", atan(-1/slo));  // yes this is how the angle of the perpendicular is worked out.
    float atn= atan(slo); 
    float atp= atan(-1/slo); 
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
    // cairo_line_to (cr, px2, py2);

    cairo_stroke (cr);

    cairo_move_to (cr, x1+80, y1);
    cairo_line_to(cr, x2+80, y2);
    cairo_rel_line_to(cr, 50*cos(ANG0), 50*sin(ANG0));
    cairo_rel_line_to(cr, 50*cos(ANG1), 50*sin(ANG1));
    cairo_stroke (cr);


    // first line x-wise
    cairo_move_to (cr, x1-80, y1);
    cairo_line_to(cr, x2-80, y2);
    cairo_rel_line_to(cr, 50*cos(atp), 50*sin(atp));
    cairo_stroke (cr);

    // fourth: this is the way to generate a line with the same slop as another one:
    // the problem I have is that I don't a pointy arrow but rather a blunt one.
    // so, to get the point you need to NOT start at the point of arrow 
    // but on one of the two tails, then line to point and then line to other tail.
    // traight line of a certain slope:
    cairo_move_to (cr, x1+240, y1);
    cairo_rel_line_to(cr, +80*cos(atn), +80*sin(atn));

    // so how to get the arrowhead now?

    // upper part of arrowhead:
    // cairo_move_to (cr, x1+240+80*cos(atn), y1+80*sin(atn));
    // cairo_rel_line_to(cr, 40*cos(atn-M_PI+.3), 40*sin(atn-M_PI+.3));
    //back to point
    // cairo_move_to (cr, x1+240+80*cos(atn), y1+80*sin(atn));
    // cairo_rel_line_to(cr, 40*cos(atn+M_PI-.3), 40*sin(atn+M_PI-.3));

    // or:
    float qx1=x1+240+80*cos(atn), qy1=y1+80*sin(atn);
    float qx2=qx1+ 40*cos(atn-M_PI+.5), qy2= qy1 +40*sin(atn-M_PI+.5);
    float qx3=qx1+ 40*cos(atn+M_PI-.3), qy3= qy1 +40*sin(atn+M_PI-.3);
    cairo_move_to(cr,qx2,qy2);
    cairo_line_to(cr,qx1,qy1);
    cairo_line_to(cr,qx3,qy3);
    //


    cairo_stroke (cr);

    cairo_destroy (cr);

    cairo_surface_write_to_png (surf2, "arro3.png");
    cairo_surface_destroy (surf2);

    return 0;
}
