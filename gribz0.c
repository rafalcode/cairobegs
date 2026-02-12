/* uses gri0.c from cairims to repupose grid code trndot.c ibut to do to do a simple grid */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define HBARNUMS 3
#define VBARNUMS 9

typedef struct
{
    float x, y;
} pos_t;

int main (int argc, char *argv[])
{
    int i, j, width=640, height=480;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* vertical divider how ar ewe going to section off the screen vertically */
    float vbarsz=(float)width/VBARNUMS; // basis for x
    float hbarsz=(float)height/HBARNUMS; // basis for y
    int totpoints = HBARNUMS*VBARNUMS;
    pos_t *lb=calloc(totpoints, sizeof(pos_t)); /* ori: origin, lb, last bar, */

    // first point, top left
    lb[0].x= vbarsz/2.;
    lb[0].y = hbarsz/2.;
    // first column, left side downwards x is the same. I..e we are going columnwise.
    for(j=1;j<HBARNUMS;j++) {
         lb[j].x= lb[j-1].x;
         lb[j].y= lb[j-1].y + hbarsz;
    }
    // first row top, y inmutable here
    for(i=1;i<VBARNUMS;i++) {
        lb[i*HBARNUMS].x= lb[(i-1)*HBARNUMS].x + vbarsz;
        lb[i*HBARNUMS].y= lb[(i-1)*HBARNUMS].y;
    }

    for(i=1;i<VBARNUMS;i++)
        for(j=1;j<HBARNUMS;j++) {
            lb[i*HBARNUMS+j].x= lb[i*HBARNUMS+j-1].x;
            lb[i*HBARNUMS+j].y= lb[i*HBARNUMS+j-1].y + hbarsz;
        }

    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    for(i=0;i<totpoints;i++){
        // printf("%4.4f %4.4f\n", lb[i].x, lb[i].y);
        cairo_arc(cr, lb[i].x, lb[i].y, 2, 0, 2 * M_PI);
        cairo_fill(cr);

        // cairo_move_to(cr,ori.h,ori.v);
        // cairo_line_to(cr,lb[i].h, lb[i].v);
        cairo_stroke(cr);
    }

    cairo_set_source_rgb(cr, 0.8, 0.45, 0.55);
    // cairo_curve_to(cr, lb[1*HBARNUMS].x, lb[1*HBARNUMS].y+100, lb[2*HBARNUMS].x, lb[2*HBARNUMS].y-100, lb[3*HBARNUMS].x, lb[3*HBARNUMS].y+100);
    // inert a bezier top row .. trying to get a sine wave .. but it's not sine!
    cairo_set_source_rgb(cr, 0.45, 0.8, 0.85);
    cairo_move_to(cr, lb[0].x, lb[0].y);
    // cairo_curve_to(cr, lb[1*HBARNUMS].x, lb[1*HBARNUMS].y+50, lb[1*HBARNUMS].x, lb[2*HBARNUMS].y-50, lb[3*HBARNUMS].x, lb[3*HBARNUMS].y); // not right .. i have an error there, spot it!
    // cairo_curve_to(cr, lb[1*HBARNUMS].x, lb[1*HBARNUMS].y+100, lb[2*HBARNUMS].x, lb[2*HBARNUMS].y-100, lb[3*HBARNUMS].x, lb[3*HBARNUMS].y);
    // cairo_curve_to(cr, lb[4*HBARNUMS].x, lb[4*HBARNUMS].y+100, lb[5*HBARNUMS].x, lb[5*HBARNUMS].y-100, lb[6*HBARNUMS].x, lb[6*HBARNUMS].y);
    // cairo_curve_to(cr, lb[1*HBARNUMS].x, lb[1*HBARNUMS].y+100, lb[2*HBARNUMS].x, lb[2*HBARNUMS].y-100, lb[3*HBARNUMS].x, lb[3*HBARNUMS].y+100);
    // cairo_curve_to(cr, lb[4*HBARNUMS].x, lb[4*HBARNUMS].y+100, lb[5*HBARNUMS].x, lb[5*HBARNUMS].y-100, lb[6*HBARNUMS].x, lb[6*HBARNUMS].y+100);

    float tvb= (float)vbarsz/3; // a third of vbarsz.
    float hvb= (float)vbarsz/2; // a third of vbarsz.
    cairo_curve_to(cr, lb[1*HBARNUMS].x - hvb, lb[1*HBARNUMS].y+100, lb[2*HBARNUMS].x+hvb, lb[2*HBARNUMS].y-100, lb[3*HBARNUMS].x, lb[3*HBARNUMS].y);
    // cairo_curve_to(cr, lb[4*HBARNUMS].x, lb[4*HBARNUMS].y+100, lb[5*HBARNUMS].x, lb[5*HBARNUMS].y-100, lb[6*HBARNUMS].x, lb[6*HBARNUMS].y+100);
    // cairo_curve_to(cr, lb[0].x, lb[0].y, lb[1*HBARNUMS].x, lb[2*HBARNUMS].y-50, lb[3*HBARNUMS].x, lb[3*HBARNUMS].y);
    cairo_stroke(cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "gribz0.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(lb);

    return 0;
}
