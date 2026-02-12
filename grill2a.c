/* grill2a.c takes afte grill2.c
 * this is a sort fo snakes and ladders prep. it's a 10x10 grid
 * starting from bottom left and going up, finishing
 * uses gri0.c from cairims to repupose grid code trndot.c ibut to do to do a simple grid */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CW 320 // canvas width
#define CH 240 // canvas height
#define TMAR 50 // top maring ... usually this will be biggest
#define BMAR 10
#define LMAR 20
#define RMAR 20
#define LWID 3

#define OURMAX 100 // i.e. our max 

#define VBARNUMS 3
#define AAGN 5 // arrow aggression nudge
#define AXT 25 // arrow extension
#define AHEI 10 // arrow height

// type of line, depend on end point.
typedef enum {
    NOWT, LINE2R, LINE2L, CURVER, CURVEL, // line rightwards, lineleftwards, curve at right(most), curve at left. First one is nowt, as in nothing. only refers to first
   // so LINE2R will be a line_to() where end.x is greater than start.x
   // and LINE2L will be a line_to() where end.x is less than start.x
   // CURVEL will be ... 
} ltype;

typedef struct /* d_t, draw type line curve or wahteevr */
{
    float p;
    ltype t;
} d_t;

typedef struct /* pos_t */
{
    float x, y;
} pos_t;

void grillit2(cairo_t *cr, pos_t *lb, int vbarnums, int hbarnums, float radi)
{
    // another type of grillit
    int i;
    cairo_move_to(cr, lb[0].x, lb[0].y);
    for(i=0;i<hbarnums-1;i++) {
        // beware a tricky aspect of cairo_arc() it *does* move point forward to where it ends, so no need to move_to's
        // however, you need to get start and end angle right. For this case I invoked the negarc version and it worked. be careful!
        if(i%2==1) {
            cairo_line_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y);
            cairo_arc_negative(cr, lb[vbarnums*i].x, lb[vbarnums*i].y+radi, radi, -M_PI_2, M_PI_2);
        } else {
            cairo_line_to(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y);
            cairo_arc(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y+radi, radi, -M_PI_2, M_PI_2);
        }
    }
    // final line: we're depnding on i's final value!
    if(i%2==1) {
        cairo_line_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y);
    } else {
        cairo_line_to(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y);
    }
    cairo_stroke(cr);
}

void addarr(cairo_t *cr, pos_t *lb, int vbarnums, int hbarnums)
{
    /* graphically this is not so neat. I'm adding direction triangles over the line. */
    int i;
    float lwi=LWID/2.;
    for(i=0;i<hbarnums-1;i++) {
        // beware a tricky aspect of cairo_arc() it *does* move point forward to where it ends, so no need to move_to's
        // however, you need to get start and end angle right. For this case I invoked the negarc version and it worked. be careful!
        if(i%2==1) {
            cairo_move_to(cr, lb[vbarnums*i+vbarnums-2].x-AAGN, lb[vbarnums*i+vbarnums-2].y);
            cairo_line_to(cr, lb[vbarnums*i+vbarnums-2].x, lb[vbarnums*i+vbarnums-2].y-AHEI);
            cairo_line_to(cr, lb[vbarnums*i+vbarnums-2].x-AXT, lb[vbarnums*i+vbarnums-2].y);
            cairo_fill(cr);
        } else {
            cairo_move_to(cr, lb[vbarnums*i+vbarnums-2].x+AAGN, lb[vbarnums*i+vbarnums-2].y);
            cairo_line_to(cr, lb[vbarnums*i+vbarnums-2].x, lb[vbarnums*i+vbarnums-2].y-AHEI);
            cairo_line_to(cr, lb[vbarnums*i+vbarnums-2].x+AXT, lb[vbarnums*i+vbarnums-2].y);
            cairo_fill(cr);
        }
    }
}

int main (int argc, char *argv[])
{
    // the standard 10x10 SandL grid.
    const int hbarnums=10;
    const int vbarnums=10;
    float ura= (float)rand()/RAND_MAX;
    int myrpoint=OURMAX*ura; // my random between O and OURMAX

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
    float hbarsz=dh/hbarnums; // y direction.
    float radi=hbarsz/2.; //radiu os connecting half circles.
    float dwr=dw+radi;
    float tglen=hbarnums*dw+M_PI*radi*(hbarnums-1); // total grill length: pi*radi is a semicircles circum, and in total there's one less than horizontal bars
    printf("tglen=%2.6f\n", tglen); 

    // now to makr out start sections and curved sections.
    // int totsecs=1+hbarnums+(hbarnums-1);
    int totsecs=2*hbarnums;
    d_t *secs=calloc(totsecs, sizeof(d_t)); // total grill length: pi*radi is a semicircles circum, and in total there's one less than horizontal bars
    secs[0].t = NOWT; // the convention
    secs[2*hbarnums-1].p = OURMAX; // easy one
    secs[2*hbarnums-1].t = (hbarnums%1==0)? LINE2L: LINE2R; // must finish on a straight.
    int k=0;
    for(i=1;i<2*hbarnums-1;i+=2) {
        secs[i].p = secs[i-1].p + OURMAX*dw/tglen;
        secs[i+1].p = secs[i].p + OURMAX*M_PI*radi/tglen;
        if(k%2==0) {
            secs[i].t = LINE2R;
            secs[i+1].t = CURVER;
        } else {
            secs[i].t = LINE2L;
            secs[i+1].t = CURVEL;
        }
        k++;
    }
    printf("Sectioning out our max (%i) in terms of our grill\n", OURMAX); 
    for(i=0;i<2*hbarnums;i++)
        printf("%2.6f:%i\n", secs[i].p, secs[i].t); 
    printf("Now where does our random point (%i) fall?\n", myrpoint);

    for(i=0;i<2*hbarnums;i++) {
        if(myrpoint>secs[i].p)
            continue;
        else
            break;
    }
    // we're depnding oon final value of i
    printf("Ans. At line segment index=%i just before %2.6f of type %i\n", i, secs[i].p, secs[i].t); 
    
    
    int totpoints = hbarnums*VBARNUMS;
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
    for(i=1;i<hbarnums;i++) {
        lb[i*VBARNUMS].x= lb[(i-1)*VBARNUMS].x;
        lb[i*VBARNUMS].y= lb[(i-1)*VBARNUMS].y + hbarsz;
    }

    for(i=1;i<hbarnums;i++)
        for(j=1;j<VBARNUMS;j++) {
            lb[i*VBARNUMS+j].x= lb[i*VBARNUMS+j-1].x + vbarsz;
            lb[i*VBARNUMS+j].y= lb[i*VBARNUMS+j-1].y;
        }

    // cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    cairo_set_source_rgb(cr, 0.65, 0.8, 0.45);
    cairo_set_line_width (cr, LWID);
    grillit(cr, lb, VBARNUMS, hbarnums, radi); /// colours whole grill
    addarr(cr, lb, VBARNUMS, hbarnums);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "grill2.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(lb);
    free(secs);

    return 0;
}
