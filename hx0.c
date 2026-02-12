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

const float pid6=M_PI/6.;
const int notrad=50; // notional radius

int main (int argc, char *argv[])
{
	if(argc!=1) {
		printf("Error. No args.\n");
		exit(EXIT_FAILURE);
	}
    float segl=180.;

    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);
    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    float x=IW/2.,  y=IH/2.;
    printf("pid6 %4.4f\n", pid6); 

    cairo_set_source_rgba(cr, 0.95, 0.4, 0., 0.3);
    cairo_arc(cr, x, y-notrad, 3, 0, 2*M_PI);
    cairo_fill(cr);

    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    cairo_move_to (cr, x, y-notrad);
    cairo_rel_line_to(cr, segl*cos(1*pid6), segl*sin(1*pid6));
    cairo_rel_line_to(cr, segl*cos(3*pid6), segl*sin(3*pid6));
    cairo_rel_line_to(cr, segl*cos(5*pid6), segl*sin(5*pid6));
    cairo_rel_line_to(cr, segl*cos(7*pid6), segl*sin(7*pid6));
    cairo_rel_line_to(cr, segl*cos(9*pid6), segl*sin(9*pid6));
    // Cairo itself takes care of the final line.
    cairo_close_path(cr);
    cairo_stroke(cr);

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "hx0.png");
    cairo_surface_destroy (surface);
    return 0;
}
