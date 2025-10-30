/* Exercises in slope
 *
 * A major mistake you can make is to send a line to the rad*sin(angle) just like that.
 * NO, it must be done relative to the point you moved to.
*/
#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define IW 800. // image/canvas width
#define IH 600. // height
#define T_PI 2*M_PI // twice pi.

int main (int argc, char *argv[])
{
	if(argc!=3) {
		printf("Error. Pls supply 2 arguments: 1) angle degrees <90 2) segment length (10,20 .. 200).\n");
		exit(EXIT_FAILURE);
	}
    float rads=T_PI*atof(argv[1])/360.; // our submitted angle in radians.
    float segl=atof(argv[2]); // our submitted angle in radians.
    float sl2=segl/2.; // half segment length
    float mkl=segl/6.; // mark length
    float mk2=mkl/2.; // half segment length

    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);
    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    float x=IW/2.,  y=IH/2.;

    cairo_set_source_rgba(cr, 0.95, 0.4, 0., 0.3);
    cairo_arc(cr, x, y, 3, 0, 2*M_PI);
    cairo_fill(cr);

    float cs=cos(rads);
    float sn=sin(rads);
    printf("cos, sin, tan rads=%2.4f %2.4f %2.4f\n", cs, sn, tn);

    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    cairo_move_to (cr, x-sl2*cs, y+sl2*sn);
    cairo_rel_line_to (cr, segl*cs, -segl*sn);
    cairo_stroke (cr);

    // the perpendicular to the tangent, "take away from x that you previously added to y, what you previously added to x, now add to y"
    cairo_move_to (cr, x-sl2*cs+mk2*sn, y+sl2*sn+mk2*cs);
    cairo_rel_line_to (cr, -mkl*sn, -mkl*cs);
    cairo_stroke (cr);

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "sl10.png");
    cairo_surface_destroy (surface);
    return 0;
}
