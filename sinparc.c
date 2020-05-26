/* CPROG Filename:  sinparc.c
 * Description:  GG
 *
 * Version:  1.0
 * Created:  02/25/2010 05:25:09 PM
 * Revision:  none
 * Compiler:  gcc
 *
 * Author:  YOUR NAME (), 
 * Company:   */

double xc = 0.5;
double yc = 0.5;
double radius = 0.4;
double angle1 = 45.0  * (M_PI/180.0);  /*  angles are specified */
double angle2 = 180.0 * (M_PI/180.0);  /*  in radians           */

snippet_normalize (cr, width, height);

cairo_arc (cr, xc, yc, radius, angle1, angle2);
cairo_stroke (cr);

/*  draw helping lines */
cairo_set_source_rgba (cr, 1,0.2,0.2,0.6);
cairo_arc (cr, xc, yc, 0.05, 0, 2*M_PI);
cairo_fill (cr);
cairo_set_line_width (cr, 0.03);
cairo_arc (cr, xc, yc, radius, angle1, angle1);
cairo_line_to (cr, xc, yc);
cairo_arc (cr, xc, yc, radius, angle2, angle2);
cairo_line_to (cr, xc, yc);
cairo_stroke (cr);
