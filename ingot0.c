/* fr for frams */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>

#define IW 640 // image/canvas width
#define IH 480 // height
#define LMAR 40
#define RMAR 40
#define TMAR 40
#define BMAR 20

#define RSEED 34 // 34 got "chip off the old block"

#define LINEWID 4. // can't have .5 of this go over margins, then whole frame will overflow

typedef struct /* dpt_t: drawable point type */
{
    float x1, y1, x2, y2;
} dpt_t; 

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);

    /* now set background of he canvas */
    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba(cr, .15, .15, .15, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    int i, j;

    /* our drawable are is smaller than canvas as define by the MAR values (i.e. margins) */
    float x1=LMAR;
    float y1=TMAR;
    float xspace=IW-LMAR-RMAR; // drawable space x-wise
    float x2=LMAR+xspace; // right most point in drawable
    float yspace=IH-TMAR-BMAR; // drawable space y-wise
    float y2=TMAR+yspace; // lowest point

    int nybars=4;
    float ybarsz=yspace/nybars; //size of each ybar
    float ybfrac=.75;

    int nxbars=6;
    float xbarsz=xspace/nxbars; //size of each xbar

    int nabars=nybars*nxbars; // numbar of ALL bars.
    dpt_t *dpts=calloc(nabars,sizeof(dpt_t));
    for(i=0;i<nybars;++i) {
        for(j=0;j<nxbars;++j) {
            dpts[i*nxbars+j].x1=x1+xbarsz*j;
            dpts[i*nxbars+j].y1=y1+ i*ybarsz + ybarsz*ybfrac;
            dpts[i*nxbars+j].x2=x1+xbarsz*(j+1);
            dpts[i*nxbars+j].y2=y1 + (i+1)*ybarsz; // use full ybarsz
        }
    }

    for(i=0;i<nabars;++i) {
        cairo_move_to(cr, dpts[i].x1, dpts[i].y1);
        cairo_line_to(cr, dpts[i].x2, dpts[i].y1);
        cairo_line_to(cr, dpts[i].x2, dpts[i].y2);
        cairo_line_to(cr, dpts[i].x1, dpts[i].y2);
        cairo_close_path(cr);
    }

    cairo_set_line_width (cr, LINEWID);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke(cr);

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "ingot0.png");
    cairo_surface_destroy (surface);
    free(dpts);
    return 0;
}
