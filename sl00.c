/* Exercises in slope
 *
 * A major mistake you can make is to send a line to the rad*sin(angle) just like that.
 * NO, it must be done relative to the point you moved to.
*/
#include<cairo/cairo.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define IW 640. // image/canvas width
#define IH 480. // height
#define T_PI 2*M_PI // twice pi.

int main (int argc, char *argv[])
{
	if(argc!=2) {
		printf("Error. Pls supply argument angle degrees.\n");
		exit(EXIT_FAILURE);
	}
    float rads=T_PI*atof(argv[1])/360.; // our submitted angle in radians.
    // give info:
    printf("sin pi/6=%2.4f\n", sin(M_PI/6.));
    printf("cos pi/6=%2.4f\n", cos(M_PI/6.));
    printf("rads=%2.4f\n", rads);
    printf("sin rads=%2.4f\n", sin(rads));
    printf("cos rads=%2.4f\n", cos(rads));

    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);
    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    double x=40,  y=IH/2.;
    double x3=IW-80,  y3=IH/2.;
    double xdist=x3-x;
    double xo=x+xdist/2.;
    double xo2=x+3*xdist/4.;

    double seglen=IH/4.;

    // straight line:
    cairo_set_line_width (cr, 1.0);
    cairo_set_source_rgb(cr, 0.85, 0.8, .0);
    cairo_move_to (cr, x, y);
    cairo_line_to (cr, x3, y3);
    cairo_stroke (cr);

    // try with slope or angle
    cairo_set_source_rgb(cr, 0.95, 0.1, 0.15);
    double x4=seglen*cos(rads);
    double y4=seglen*sin(rads);
    cairo_move_to (cr, xo, y);
    cairo_line_to (cr, xo+x4, y-y4);
    // cairo_stroke_preserve (cr); // will hold the last point.
    cairo_stroke (cr);
    
    cairo_set_source_rgb(cr, 0.25, 0.8, 0.4);
    float tn=tan(rads);
    printf("tan rads=%2.4f\n", tn);
    cairo_move_to (cr, xo, y);
    cairo_line_to (cr, xo, y-y4);
    cairo_stroke (cr);

    // the perpendicular to the tangent, "take away from x that you previously added to y, what you previously added to x, now add to y"
    cairo_set_source_rgb(cr, 0.35, 0.2, 0.85);
    // cairo_move_to(cr, x, y+20);
    cairo_line_to(cr, x-tn*60, y);
    cairo_stroke (cr);
    
    cairo_destroy(cr);
    cairo_surface_write_to_png (surface, "sl00.png");
    cairo_surface_destroy (surface);
    return 0;
}
