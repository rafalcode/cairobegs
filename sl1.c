/* Exercises in slope
 *
 * A major mistake you can make is to send a line to the rad*sin(angle) just like that.
 * NO, it must be done relative to the point you moved to.
*/
#include <cairo/cairo.h>
#include <stdio.h>
#include <math.h>

#define IW 800. // image/canvas width
#define IH 600. // height

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
    double x0=IW/2.;

    double radi=IH/4.;

    cairo_set_line_width (cr, 3.0);
    cairo_move_to (cr, x, y);
    cairo_line_to (cr, x3, y3);
    cairo_stroke(cr);

    // try with slope or angle
    printf("sin pi/4=%2.4f\n", sin(M_PI_4));
    printf("cos pi/4=%2.4f\n", cos(M_PI_4));
    double x2=radi*cos(M_PI_4);
    double y2=radi*sin(M_PI_4);
    cairo_arc(cr, x0, y, 200, -M_PI_2, M_PI_2);
    cairo_stroke (cr);

    /// Two ticks inside a circle, tick 1 easy at top, straight line down
    cairo_move_to (cr, x0, y-200);
    cairo_rel_line_to (cr, 0, 50);
    cairo_stroke (cr);

    // tick 2, a tenth of an angle along side.
    double xx, x5, y5, x6, y6;
    int i;
    for(i=2;i<20;++i) {
        xx=.1*i;

        if(i<10) {
            x5=50*cos(M_PI_2*xx);
            x6=150*cos(M_PI_2*xx);
            y5=-50*sin(M_PI_2*xx);
            y6=-150*sin(M_PI_2*xx);
        } else {
            x5=-50*cos(M_PI_2*xx);
            x6=-150*cos(M_PI_2*xx);
            y5=50*sin(M_PI_2*xx);
            y6=150*sin(M_PI_2*xx);
        }
        cairo_move_to (cr, x0, y); // first we go to our center point
        cairo_rel_move_to (cr, x6, y6); // for a tick we need to go a certain distance before the circle. note rel_move!
        cairo_rel_line_to (cr, x5, y5); // now we can draw it up to the circle's circumference
        cairo_stroke (cr);
    }



    cairo_arc(cr, x0, y, 100, 0, 2*M_PI);
    cairo_stroke (cr);


    cairo_move_to (cr, x0, y);
    printf("tan pi/6=%2.4f\n", tan(M_PI/6.));
    float tn=tan(M_PI/6.);
    cairo_line_to (cr, x+60, y+20+tn*60);
    cairo_stroke (cr);

    // the perpendicular to the tangent, "take away from x that you previously added to y, what you previously added to x, now add to y"
    cairo_move_to (cr, x0, y);
    cairo_line_to (cr, x-tn*60, y+20+60);
    cairo_set_source_rgba(cr, 0.85, 0.8, 0.25, 0.6);
    cairo_set_source_rgba(cr, 0.85, 0.8, 0.25, 0.6);
    cairo_stroke (cr);

    cairo_move_to (cr, x0, y);
    cairo_line_to (cr, x0+100*cos(M_PI_4), y+100*sin(M_PI_4));
    tn=tan(M_PI_4);

    // ok here is the tangent in action, fully enough I use it as perpendicular here
    cairo_rel_line_to (cr, -tn*60, 60);
    cairo_set_source_rgba(cr, 0.85, 0.3, 0.65, 1);
    cairo_stroke (cr);

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "sl1.png");
    cairo_surface_destroy (surface);
    return 0;
}
