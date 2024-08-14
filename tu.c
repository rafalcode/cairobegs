/* this is the cairo tute. Short, but the points are fundamental
ref: 
https://www.cairographics.org/tutorial/
*/
#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[])
{

    int  w=480, h=480;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);
    cairo_t *cr = cairo_create (surface);
    cairo_rectangle (cr, 0, 0, w, h); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    cairo_move_to (cr, 50, 50);
    // Whether with absolute coordinates cairo_line_to() (extend the path from the reference to this point), or relative coordinates cairo_rel_line_to() (extend the path from the reference this far in this direction), the path connection will be a straight line. The new reference point will be at the other end of the line.
    cairo_line_to (cr, 150, 95);
    cairo_rel_line_to (cr, 50, -45);

    // Arcs are parts of the outside of a circle. Unlike straight lines, the point you directly specify is not on the path. Instead it is the center of the circle that makes up the addition to the path. Both a starting and ending point on the circle must be specified, and these points are connected either clockwise by cairo_arc() or counter-clockwise by cairo_arc_negative(). If the previous reference point is not on this new curve, a straight line is added from it to where the arc begins. The reference point is then updated to where the arc ends. There are only absolute versions.

    cairo_arc (cr, 150, 100, 50 * sqrt(2), -.25 * M_PI, .25 * M_PI);

    //x/ Curves in cairo are cubic Bézier splines. They start at the current reference point and smoothly follow the direction of two other points (without going through them) to get to a third specified point. Like lines, there are both absolute (cairo_curve_to()) and relative (cairo_rel_curve_to()) versions. Note that the relative variant specifies all points relative to the previous reference point, rather than each relative to the preceding control point of the curve.

    // note here: dx1 == dx2 this is xcoord of first sn second control point.
    // the hird xcoord --- is not really a control in bezier sense but actually just the endpoint.
    // it#s rel and ycoord3 is 0, so y will be the same as starpoint.
    cairo_rel_curve_to (cr, -75, -45, -75, 45, -150, 0);
    // dx1, dy1, dx2, dy2, dx3, dy3

    // Cairo can also close the path by drawing a straight line to the beginning of the current sub-path. This straight line can be useful for the last edge of a polygon, but is not directly useful for curve-based shapes. A closed path is fundamentally different from an open path: it's one continuous path and has no start or end. A closed path has no line caps for there is no place to put them.
    cairo_close_path (cr);
    cairo_set_source_rgb (cr, 0.3, 0.2, 0.3);
    cairo_stroke(cr);
    cairo_destroy(cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "tu.png");
    cairo_surface_destroy (surface);

    return 0;
}
