/* uses gri0.c from cairims to repupose grid code trndot.c ibut to do to do a simple grid */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CW 800 // canvas width
#define CH 600 // canvas height
#define TMAR 50 // top maring ... usually this will be biggest
#define BMAR 10
#define LMAR 20
#define RMAR 20
#define LWID 5

#define HBARNUMS 10
#define VBARNUMS 9

typedef struct /* pos_t */
{
    float x, y;
} pos_t;

int main (int argc, char *argv[])
{
    int i, j;

    // we start with the canvas. Set up surface, set bg etc.
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, CW, CH);
    cairo_t *cr = cairo_create (surface);
    cairo_rectangle (cr, 0, 0, CW, CH);
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    // now the drawable
    pos_t dtl;
    dtl.x=LMAR; // dtl: drawable top left
    dtl.y=TMAR;
    float dw=CW-LMAR-RMAR; // drawable width extent
    float dh=CH-TMAR-BMAR; // drawable height extent
    // just for show
    cairo_rectangle (cr, dtl.x, dtl.y, dw, dh); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
    cairo_fill (cr);

    /* vertical divider how ar ewe going to section off the screen vertically */
    float vbarsz=dw/VBARNUMS; // size of steps in x direction
    float hbarsz=dh/HBARNUMS; // y direction.
    float radi=hbarsz/2.; //radiu os connecting half circles.
    int totpoints = HBARNUMS*VBARNUMS;
    pos_t *lb=calloc(totpoints, sizeof(pos_t)); /* ori: origin, lb, last bar, */

    // first point, top left
    lb[0].x= dtl.x + vbarsz/2.;
    lb[0].y = dtl.y + hbarsz/2.;
    // first row, only x changes
    for(i=1;i<VBARNUMS;i++) {
         lb[i].x= lb[i-1].x + vbarsz;
         lb[i].y= lb[i-1].y;
    }
    // first column
    for(i=1;i<HBARNUMS;i++) {
        lb[i*VBARNUMS].x= lb[(i-1)*VBARNUMS].x;
        lb[i*VBARNUMS].y= lb[(i-1)*VBARNUMS].y + hbarsz;
    }

    for(i=1;i<HBARNUMS;i++)
        for(j=1;j<VBARNUMS;j++) {
            lb[i*VBARNUMS+j].x= lb[i*VBARNUMS+j-1].x + vbarsz;
            lb[i*VBARNUMS+j].y= lb[i*VBARNUMS+j-1].y;
        }

    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);

    // trhis is a quick way to
    //     cairo_move_to(cr, lb[VBARNUMS*i].x, lb[VBARNUMS*i].y);
    cairo_move_to(cr, lb[0].x, lb[0].y);
    // for(i=0;i<HBARNUMS-1;i++) {
    for(i=0;i<HBARNUMS-1;i++) {
        // beware a tricky aspect of cairo_arc() it *does* move point forward to where it ends, so no need to move_to's
        // however, you need to get start and end angle right. For this case I invoked the negarc version and it worked. be careful!
        if(i%2==1) {
            cairo_line_to(cr, lb[VBARNUMS*i].x, lb[VBARNUMS*i].y);
            cairo_arc_negative(cr, lb[VBARNUMS*i].x, lb[VBARNUMS*i].y+radi, radi, -M_PI_2, M_PI_2);
        } else {
            cairo_line_to(cr, lb[VBARNUMS*i+VBARNUMS-1].x, lb[VBARNUMS*i+VBARNUMS-1].y);
            cairo_arc(cr, lb[VBARNUMS*i+VBARNUMS-1].x, lb[VBARNUMS*i+VBARNUMS-1].y+radi, radi, -M_PI_2, M_PI_2);
        }
    }
    // final line: we're depnding on i's final value!
    if(i%2==1) {
        cairo_line_to(cr, lb[VBARNUMS*i].x, lb[VBARNUMS*i].y);
    } else {
        cairo_line_to(cr, lb[VBARNUMS*i+VBARNUMS-1].x, lb[VBARNUMS*i+VBARNUMS-1].y);
    }
    cairo_set_line_width (cr, LWID);
    cairo_stroke(cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "grill.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(lb);

    return 0;
}
