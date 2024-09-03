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
#define DW (CW-LMAR-RMAR) // drawable width extent
#define DH (CH-TMAR-BMAR) // drawable height extent
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

void grillit4(cairo_t *cr, pos_t *lb, int sidx /* the secs index */, d_t *secs, int vbarnums, int hbarnums, float radi, float tglen, int myrpoint)
{
    // taking up from grillit2, cleaning up: grillet3, is the one that finishishes fo the path.
    // we need two procs, one for a full flow and another for partial flows.
    // // the orginal grillit is good for full flows

    // first the partial shape that has to be filled. ff is the row.
    int ff=(sidx-1)/2;

    float semifrac, widthfrac, widthfracp, widthfracp2;
    if(secs[sidx].t==CURVEL) {
        printf("CURVEL!\n"); 
        semifrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
	printf("semifrac=%2.6f semifracbypi=%2.6f\n", semifrac, semifrac*M_PI);
        cairo_arc_negative(cr, lb[vbarnums*ff].x, lb[vbarnums*ff].y+radi, radi, -M_PI_2-semifrac*M_PI, -3*M_PI_2);
        cairo_stroke(cr);
    } else if(secs[sidx].t==CURVER) {
        printf("CURVER!\n"); 
        semifrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
	printf("semifrac=%2.6f\n", semifrac);
        cairo_arc(cr, lb[vbarnums*ff+vbarnums-1].x, lb[vbarnums*ff+vbarnums-1].y+radi, radi, -M_PI_2+semifrac*M_PI, M_PI_2);
        cairo_stroke(cr);
    } else if(secs[sidx].t==LINE2L) {
        printf("LINE2L!\n"); 
        printf("myrpoint less prev=%2.6f\n", (float)myrpoint - secs[sidx-1].p);
        printf("secs[sidx].p less prev p=%2.6f\n", secs[sidx].p - secs[sidx-1].p);
        widthfrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        // widthfracp = widthfrac*(lb[vbarnums*i+vbarnums-1].x - lb[vbarnums*i].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        widthfracp = widthfrac*(lb[vbarnums*ff+vbarnums-1].x - lb[vbarnums*ff].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        widthfracp2 = (1-widthfrac)*(lb[vbarnums*ff+vbarnums-1].x - lb[vbarnums*ff].x);
        printf("widthfrac=%2.6f widthfracp(pixels)=%2.6f widthfracp2(pixels)=%2.6f\n", widthfrac, widthfracp, widthfracp2); 
        // cairo_arc(cr, lb[vbarnums*ff+vbarnums-1].x - widthfracp, lb[vbarnums*ff].y, 5, 0, 2*M_PI);
        // cairo_arc(cr, lb[vbarnums*ff+vbarnums-1].x - widthfracp-widthfracp2, lb[vbarnums*ff].y, 5, 0, 2*M_PI);
        cairo_move_to(cr, lb[vbarnums*ff+vbarnums-1].x-widthfracp, lb[vbarnums*ff].y);
        cairo_line_to(cr, lb[vbarnums*ff+vbarnums-1].x-widthfracp-widthfracp2, lb[vbarnums*ff].y);
        cairo_stroke(cr);
    } else if(secs[sidx].t==LINE2R) {
        printf("LINE2R!\n"); 
        printf("myrpoint less prev=%2.6f\n", (float)myrpoint - secs[sidx-1].p);
        printf("secs[sidx].p less prev p=%2.6f\n", secs[sidx].p - secs[sidx-1].p);
        widthfrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        printf("widthfrac=%2.6f\n", widthfrac); 
        widthfracp = widthfrac*(lb[vbarnums*ff+vbarnums-1].x - lb[vbarnums*ff].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        widthfracp2 = (1-widthfrac)*(lb[vbarnums*ff+vbarnums-1].x - lb[vbarnums*ff].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        printf("widthfrac=%2.6f widthfracp(pixels)=%2.6f widthfracp2(pixels)=%2.6f\n", widthfrac, widthfracp, widthfracp2); 
        // cairo_arc(cr, lb[vbarnums*ff].x + widthfracp, lb[vbarnums*ff].y, 5, 0, 2*M_PI);
        // cairo_arc(cr, lb[vbarnums*ff].x + widthfracp2, lb[vbarnums*ff].y, 5, 0, 2*M_PI);
        cairo_move_to(cr, lb[vbarnums*ff].x+widthfracp, lb[vbarnums*ff].y);
        cairo_line_to(cr, lb[vbarnums*ff].x+widthfracp+widthfracp2, lb[vbarnums*ff].y);
        cairo_stroke(cr);
    }

    // Now for the full flows: numb full flows
    printf("prev ff = %i\n", (sidx-1)/2);
    // int ff=(sidx-1)/2;
    // int ff=hbarnums-1-(sidx-1)/2;
   printf("ff=%i\n", ff);
    float uradi=OURMAX*radi/tglen; // radi in our units.
    printf("num remaining full flows=%i\n", hbarnums-1-ff); 

    int i, starti;
    // int starti=(secs[sidx].t==CURVER | secs[sidx].t==CURVEL)? ff+1:ff;
    // not very enamoured of this if 
    if(secs[sidx].t==CURVER) {
	starti=ff+1;
         cairo_move_to(cr, lb[vbarnums*starti+vbarnums-1].x, lb[vbarnums*starti+vbarnums-1].y);
    } else if(secs[sidx].t==CURVEL) {
	starti=ff+1;
        cairo_move_to(cr, lb[vbarnums*starti].x, lb[vbarnums*starti].y);
    } else {
	starti=ff;
    }
    for(i=starti;i<hbarnums-1;i++) {
        // beware a tricky aspect of cairo_arc() it *does* move point forward to where it ends, so no need to move_to's
        // however, you need to get start and end angle right. For this case I invoked the negarc version and it worked. be careful!
        if(i%2==1) {
            // cairo_move_to(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y);
            cairo_line_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y);
            cairo_arc_negative(cr, lb[vbarnums*i].x, lb[vbarnums*i].y+radi, radi, -M_PI_2, M_PI_2);
        } else {
            // cairo_move_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y);
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


    // we're examining the end points here. There's a reliance on a ciaro secondary effect.
    // so if it's a line, we must cut backwards, if curve move forwards! I know, already so complicated!
    /*
    if(i%2==1) {
        // cairo_line_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y);
        printf("Endpoint of ff = %2.6f,%2.6f type %i\n", lb[vbarnums*i].x, lb[vbarnums*i].y, secs[sidx].t);
        cairo_arc(cr, lb[vbarnums*i].x, lb[vbarnums*i].y, 5, 0, 2*M_PI);
        cairo_fill(cr);
    } else {
        printf("Endpoint of ff = %2.6f,%2.6f type %i\n", lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y,  secs[sidx].t);
        cairo_arc(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y, 5, 0, 2*M_PI);
        cairo_fill(cr);
    }
    */

}

void grillit3(cairo_t *cr, pos_t *lb, int sidx /* the secs index */, d_t *secs, int vbarnums, int hbarnums, float radi, float tglen, int myrpoint)
{
    // taking up from grillit2, cleaning up: grillet3, is the one that finishishes fo the path.
    // we need two procs, one for a full flow and another for partial flows.
    // // the orginal grillit is good for full flows

    // first the partial shape that has to be filled. ff is the row.
    int ff=(sidx-1)/2;

    float semifrac, widthfrac, widthfracp, widthfracp2;
    if(secs[sidx].t==CURVEL) {
        printf("CURVEL!\n"); 
        semifrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
	printf("semifrac=%2.6f semifracbypi=%2.6f\n", semifrac, semifrac*M_PI);
        cairo_arc_negative(cr, lb[vbarnums*ff].x, lb[vbarnums*ff].y+radi, radi, -M_PI_2-semifrac*M_PI, -3*M_PI_2);
        cairo_stroke(cr);
    } else if(secs[sidx].t==CURVER) {
        printf("CURVER!\n"); 
        semifrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
	printf("semifrac=%2.6f\n", semifrac);
        cairo_arc(cr, lb[vbarnums*ff+vbarnums-1].x, lb[vbarnums*ff+vbarnums-1].y+radi, radi, -M_PI_2+semifrac*M_PI, M_PI_2);
        cairo_stroke(cr);
    } else if(secs[sidx].t==LINE2L) {
        printf("LINE2L!\n"); 
        printf("myrpoint less prev=%2.6f\n", (float)myrpoint - secs[sidx-1].p);
        printf("secs[sidx].p less prev p=%2.6f\n", secs[sidx].p - secs[sidx-1].p);
        widthfrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        // widthfracp = widthfrac*(lb[vbarnums*i+vbarnums-1].x - lb[vbarnums*i].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        widthfracp = widthfrac*(lb[vbarnums*ff+vbarnums-1].x - lb[vbarnums*ff].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        widthfracp2 = (1-widthfrac)*(lb[vbarnums*ff+vbarnums-1].x - lb[vbarnums*ff].x);
        printf("widthfrac=%2.6f widthfracp(pixels)=%2.6f widthfracp2(pixels)=%2.6f\n", widthfrac, widthfracp, widthfracp2); 
        // cairo_arc(cr, lb[vbarnums*ff+vbarnums-1].x - widthfracp, lb[vbarnums*ff].y, 5, 0, 2*M_PI);
        // cairo_arc(cr, lb[vbarnums*ff+vbarnums-1].x - widthfracp-widthfracp2, lb[vbarnums*ff].y, 5, 0, 2*M_PI);
        cairo_move_to(cr, lb[vbarnums*ff+vbarnums-1].x-widthfracp, lb[vbarnums*ff].y);
        cairo_line_to(cr, lb[vbarnums*ff+vbarnums-1].x-widthfracp-widthfracp2, lb[vbarnums*ff].y);
        cairo_stroke(cr);
    } else if(secs[sidx].t==LINE2R) {
        printf("LINE2R!\n"); 
        printf("myrpoint less prev=%2.6f\n", (float)myrpoint - secs[sidx-1].p);
        printf("secs[sidx].p less prev p=%2.6f\n", secs[sidx].p - secs[sidx-1].p);
        widthfrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        printf("widthfrac=%2.6f\n", widthfrac); 
        widthfracp = widthfrac*(lb[vbarnums*ff+vbarnums-1].x - lb[vbarnums*ff].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        widthfracp2 = (1-widthfrac)*(lb[vbarnums*ff+vbarnums-1].x - lb[vbarnums*ff].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        printf("widthfrac=%2.6f widthfracp(pixels)=%2.6f widthfracp2(pixels)=%2.6f\n", widthfrac, widthfracp, widthfracp2); 
        // cairo_arc(cr, lb[vbarnums*ff].x + widthfracp, lb[vbarnums*ff].y, 5, 0, 2*M_PI);
        // cairo_arc(cr, lb[vbarnums*ff].x + widthfracp2, lb[vbarnums*ff].y, 5, 0, 2*M_PI);
        cairo_move_to(cr, lb[vbarnums*ff].x+widthfracp, lb[vbarnums*ff].y);
        cairo_line_to(cr, lb[vbarnums*ff].x+widthfracp+widthfracp2, lb[vbarnums*ff].y);
        cairo_stroke(cr);
    }

    // Now for the full flows: numb full flows
    printf("prev ff = %i\n", (sidx-1)/2);
    // int ff=(sidx-1)/2;
    // int ff=hbarnums-1-(sidx-1)/2;
   printf("ff=%i\n", ff);
    float uradi=OURMAX*radi/tglen; // radi in our units.
    printf("num remaining full flows=%i\n", hbarnums-1-ff); 

    int i, starti;
    // int starti=(secs[sidx].t==CURVER | secs[sidx].t==CURVEL)? ff+1:ff;
    // not very enamoured of this if 
    if(secs[sidx].t==CURVER) {
	starti=ff+1;
         cairo_move_to(cr, lb[vbarnums*starti+vbarnums-1].x, lb[vbarnums*starti+vbarnums-1].y);
    } else if(secs[sidx].t==CURVEL) {
	starti=ff+1;
        cairo_move_to(cr, lb[vbarnums*starti].x, lb[vbarnums*starti].y);
    } else {
	starti=ff;
    }
    for(i=starti;i<hbarnums-1;i++) {
        // beware a tricky aspect of cairo_arc() it *does* move point forward to where it ends, so no need to move_to's
        // however, you need to get start and end angle right. For this case I invoked the negarc version and it worked. be careful!
        if(i%2==1) {
            // cairo_move_to(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y);
            cairo_line_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y);
            cairo_arc_negative(cr, lb[vbarnums*i].x, lb[vbarnums*i].y+radi, radi, -M_PI_2, M_PI_2);
        } else {
            // cairo_move_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y);
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


    // we're examining the end points here. There's a reliance on a ciaro secondary effect.
    // so if it's a line, we must cut backwards, if curve move forwards! I know, already so complicated!
    /*
    if(i%2==1) {
        // cairo_line_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y);
        printf("Endpoint of ff = %2.6f,%2.6f type %i\n", lb[vbarnums*i].x, lb[vbarnums*i].y, secs[sidx].t);
        cairo_arc(cr, lb[vbarnums*i].x, lb[vbarnums*i].y, 5, 0, 2*M_PI);
        cairo_fill(cr);
    } else {
        printf("Endpoint of ff = %2.6f,%2.6f type %i\n", lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y,  secs[sidx].t);
        cairo_arc(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y, 5, 0, 2*M_PI);
        cairo_fill(cr);
    }
    */

}

void grillit2a(cairo_t *cr, pos_t *lb, int sidx /* the secs index */, d_t *secs, int vbarnums, int hbarnums, float radi, float tglen, int myrpoint)
{
    // taking up from grillit2, cleaning up: grillet3, is the one that finishishes fo the path.
    // we need two procs, one for a full flow and another for partial flows.
    // // the orginal grillit is good for full flows
    int i;

    // numb full flows
    int ff=(sidx-1)/2;
    printf("num full flows=%i\n", ff); 

    cairo_move_to(cr, lb[0].x, lb[0].y);
    for(i=0;i<ff;i++) {
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
    float uradi=OURMAX*radi/tglen; // radi in our units.
    printf("radi=%2.6f, uradi=%2.6f usemi %2.6f\n", radi, uradi, uradi*M_PI);
    // cairo_stroke(cr);
    float semifrac, widthfrac, widthfracp /* widthfrac in pixels */;
    if(secs[sidx].t==CURVEL) {
        printf("CURVEL!\n"); 
        // cairo_line_to(cr, lb[vbarnums*i+vbarnums-1].x-hbarsz, lb[vbarnums*i+vbarnums-1].y);
        cairo_line_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y); // return width
        printf("myrpoint less prev=%2.6f\n", (float)myrpoint - secs[sidx-1].p);
        printf("secs[sidx].p less prev p=%2.6f\n", secs[sidx].p - secs[sidx-1].p);
        // printf("fraction of a semicircle=%2.6f\n", ((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p));
        semifrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        printf("fraction of a semicircle=%2.6f\n", semifrac);
        printf("Therefore angle in rads=%2.6f in degrees=%2.6f\n", semifrac*M_PI, semifrac*180);
        // cairo_arc_negative(cr, lb[vbarnums*i].x, lb[vbarnums*i].y+radi, radi, -M_PI_2, -M_PI_2+semifrac*M_PI);
        // cairo_arc_negative(cr, lb[vbarnums*i].x, lb[vbarnums*i].y+radi, radi, -M_PI_2, (1-semifrac)*M_PI);
        cairo_arc_negative(cr, lb[vbarnums*i].x, lb[vbarnums*i].y+radi, radi, -M_PI_2, -M_PI_2-semifrac*M_PI);
        // cairo_arc(cr, lb[vbarnums*i].x, lb[vbarnums*i].y+radi, radi, -M_PI_2, -M_PI_2+semifrac*M_PI);
        cairo_stroke(cr);
        // cairo_arc(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y, 5, 0, 2*M_PI);
        // cairo_fill(cr);
        // cairo_arc(cr, lb[vbarnums*i].x, lb[vbarnums*i].y, 5, 0, 2*M_PI);
        // cairo_fill(cr);
    } else if(secs[sidx].t==CURVER) {
        printf("CURVER!\n"); 
        cairo_line_to(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y);
        semifrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        printf("Therefore angle in rads=%2.6f in degrees=%2.6f\n", semifrac*M_PI, semifrac*180);
        cairo_arc(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y+radi, radi, -M_PI_2, -M_PI_2+semifrac*M_PI);
        cairo_stroke(cr);
    } else if(secs[sidx].t==LINE2L) {
        printf("LINE2L!\n"); 
        printf("myrpoint less prev=%2.6f\n", (float)myrpoint - secs[sidx-1].p);
        printf("secs[sidx].p less prev p=%2.6f\n", secs[sidx].p - secs[sidx-1].p);
        widthfrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        // widthfracp = widthfrac*(lb[vbarnums*i+vbarnums-1].x - lb[vbarnums*i].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        widthfracp = widthfrac*(lb[vbarnums*i+vbarnums-1].x - lb[vbarnums*i].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        printf("widthfrac=%2.6f widthfracp(pixels)=%2.6f\n", widthfrac, widthfracp); 
        cairo_line_to(cr, lb[vbarnums*i+vbarnums-1].x-widthfracp, lb[vbarnums*i].y);
        cairo_stroke(cr);
    } else if(secs[sidx].t==LINE2R) {
        printf("LINE2R!\n"); 
        printf("myrpoint less prev=%2.6f\n", (float)myrpoint - secs[sidx-1].p);
        printf("secs[sidx].p less prev p=%2.6f\n", secs[sidx].p - secs[sidx-1].p);
        widthfrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        widthfracp = widthfrac*(lb[vbarnums*i+vbarnums-1].x - lb[vbarnums*i].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        printf("widthfrac=%2.6f widthfracp(pixels)=%2.6f\n", widthfrac, widthfracp); 
        cairo_line_to(cr, lb[vbarnums*i].x+widthfracp, lb[vbarnums*i].y);
        cairo_stroke(cr);
    }

    // we're examining the end points here. There's a reliance on a ciaro secondary effect.
    // so if it's a line, we must cut backwards, if curve move forwards! I know, already so complicated!
    /*
    if(i%2==1) {
        // cairo_line_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y);
        printf("Endpoint of ff = %2.6f,%2.6f type %i\n", lb[vbarnums*i].x, lb[vbarnums*i].y, secs[sidx].t);
        cairo_arc(cr, lb[vbarnums*i].x, lb[vbarnums*i].y, 5, 0, 2*M_PI);
        cairo_fill(cr);
    } else {
        printf("Endpoint of ff = %2.6f,%2.6f type %i\n", lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y,  secs[sidx].t);
        cairo_arc(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y, 5, 0, 2*M_PI);
        cairo_fill(cr);
    }
    */

}

void grillit2(cairo_t *cr, pos_t *lb, int sidx /* the secs index */, d_t *secs, int vbarnums, int hbarnums, float radi, float tglen, int myrpoint)
{
    // another type of grillit
    // we need two procs, one for a full flow and another for partial flows.
    // // the orginal grillit is good for full flows
    int i;

    // numb full flows
    int ff=(sidx-1)/2;
    printf("num full flows=%i\n", ff); 

    cairo_move_to(cr, lb[0].x, lb[0].y);
    for(i=0;i<ff;i++) {
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
    float uradi=OURMAX*radi/tglen; // radi in our units.
    printf("radi=%2.6f, uradi=%2.6f usemi %2.6f\n", radi, uradi, uradi*M_PI);
    // cairo_stroke(cr);
    float semifrac, widthfrac, widthfracp /* widthfrac in pixels */;
    if(secs[sidx].t==CURVEL) {
        printf("CURVEL!\n"); 
        // cairo_line_to(cr, lb[vbarnums*i+vbarnums-1].x-hbarsz, lb[vbarnums*i+vbarnums-1].y);
        cairo_line_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y); // return width
        printf("myrpoint less prev=%2.6f\n", (float)myrpoint - secs[sidx-1].p);
        printf("secs[sidx].p less prev p=%2.6f\n", secs[sidx].p - secs[sidx-1].p);
        // printf("fraction of a semicircle=%2.6f\n", ((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p));
        semifrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        printf("fraction of a semicircle=%2.6f\n", semifrac);
        printf("Therefore angle in rads=%2.6f in degrees=%2.6f\n", semifrac*M_PI, semifrac*180);
        // cairo_arc_negative(cr, lb[vbarnums*i].x, lb[vbarnums*i].y+radi, radi, -M_PI_2, -M_PI_2+semifrac*M_PI);
        // cairo_arc_negative(cr, lb[vbarnums*i].x, lb[vbarnums*i].y+radi, radi, -M_PI_2, (1-semifrac)*M_PI);
        cairo_arc_negative(cr, lb[vbarnums*i].x, lb[vbarnums*i].y+radi, radi, -M_PI_2, -M_PI_2-semifrac*M_PI);
        // cairo_arc(cr, lb[vbarnums*i].x, lb[vbarnums*i].y+radi, radi, -M_PI_2, -M_PI_2+semifrac*M_PI);
        cairo_stroke(cr);
        // cairo_arc(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y, 5, 0, 2*M_PI);
        // cairo_fill(cr);
        // cairo_arc(cr, lb[vbarnums*i].x, lb[vbarnums*i].y, 5, 0, 2*M_PI);
        // cairo_fill(cr);
    } else if(secs[sidx].t==CURVER) {
        printf("CURVER!\n"); 
        cairo_line_to(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y);
        semifrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        printf("Therefore angle in rads=%2.6f in degrees=%2.6f\n", semifrac*M_PI, semifrac*180);
        cairo_arc(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y+radi, radi, -M_PI_2, -M_PI_2+semifrac*M_PI);
        cairo_stroke(cr);
    } else if(secs[sidx].t==LINE2L) {
        printf("LINE2L!\n"); 
        printf("myrpoint less prev=%2.6f\n", (float)myrpoint - secs[sidx-1].p);
        printf("secs[sidx].p less prev p=%2.6f\n", secs[sidx].p - secs[sidx-1].p);
        widthfrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        // widthfracp = widthfrac*(lb[vbarnums*i+vbarnums-1].x - lb[vbarnums*i].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        widthfracp = widthfrac*(lb[vbarnums*i+vbarnums-1].x - lb[vbarnums*i].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        printf("widthfrac=%2.6f widthfracp(pixels)=%2.6f\n", widthfrac, widthfracp); 
        cairo_line_to(cr, lb[vbarnums*i+vbarnums-1].x-widthfracp, lb[vbarnums*i].y);
        cairo_stroke(cr);
    } else if(secs[sidx].t==LINE2R) {
        printf("LINE2R!\n"); 
        printf("myrpoint less prev=%2.6f\n", (float)myrpoint - secs[sidx-1].p);
        printf("secs[sidx].p less prev p=%2.6f\n", secs[sidx].p - secs[sidx-1].p);
        widthfrac=((float)myrpoint - secs[sidx-1].p) / (secs[sidx].p - secs[sidx-1].p);
        widthfracp = widthfrac*(lb[vbarnums*i+vbarnums-1].x - lb[vbarnums*i].x); //yes, I know, I thought vbarnums*i would be operated on, but then it would be an addition.
        printf("widthfrac=%2.6f widthfracp(pixels)=%2.6f\n", widthfrac, widthfracp); 
        cairo_line_to(cr, lb[vbarnums*i].x+widthfracp, lb[vbarnums*i].y);
        cairo_stroke(cr);
    }

    // we're examining the end points here. There's a reliance on a ciaro secondary effect.
    // so if it's a line, we must cut backwards, if curve move forwards! I know, already so complicated!
    /*
    if(i%2==1) {
        // cairo_line_to(cr, lb[vbarnums*i].x, lb[vbarnums*i].y);
        printf("Endpoint of ff = %2.6f,%2.6f type %i\n", lb[vbarnums*i].x, lb[vbarnums*i].y, secs[sidx].t);
        cairo_arc(cr, lb[vbarnums*i].x, lb[vbarnums*i].y, 5, 0, 2*M_PI);
        cairo_fill(cr);
    } else {
        printf("Endpoint of ff = %2.6f,%2.6f type %i\n", lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y,  secs[sidx].t);
        cairo_arc(cr, lb[vbarnums*i+vbarnums-1].x, lb[vbarnums*i+vbarnums-1].y, 5, 0, 2*M_PI);
        cairo_fill(cr);
    }
    */

}

void grillit(cairo_t *cr, pos_t *lb, int vbarnums, int hbarnums, float radi)
{
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
    if(argc!=3) {
        printf("2 args: 1) random seed 2) number of horiz bars\n");
        exit(EXIT_FAILURE);
    }
    srand(atoi(argv[1]));
    int hbarnums=atoi(argv[2]);
    float ura= (float)rand()/RAND_MAX;
    float ura2= (float)rand()/RAND_MAX;
    int myrpoint=OURMAX*ura; // my random between O and OURMAX
    int myrpoint2=OURMAX*ura2; // my random between O and OURMAX
    int tmp;
    if(myrpoint>myrpoint2) {
        tmp=myrpoint2;
        myrpoint2=myrpoint;
        myrpoint=tmp;
    }
    printf("mrpoints: %i %i\n", myrpoint, myrpoint2);

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
    // just for show
    cairo_rectangle (cr, dtl.x, dtl.y, DW, DH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
    cairo_fill (cr);

    /* vertical divider how ar ewe going to section off the screen vertically */
    float vbarsz=DW/VBARNUMS; // size of steps in x direction
    float hbarsz=DH/hbarnums; // y direction.
    float radi=hbarsz/2.; //radiu os connecting half circles.
    float dwr=DW+radi;
    float tglen=hbarnums*DW+M_PI*radi*(hbarnums-1); // total grill length: pi*radi is a semicircles circum, and in total there's one less than horizontal bars
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
        secs[i].p = secs[i-1].p + OURMAX*DW/tglen;
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
        printf("%2.6f:%i ", secs[i].p, secs[i].t); 
    printf("\nNow where does our random point (%i) fall?\n", myrpoint);

    int sidx, sidx2;
    for(i=0;i<2*hbarnums;i++) {
        if(myrpoint>secs[i].p)
            continue;
        else {
            sidx=i;
            break;
        }
    }
    for(i=0;i<2*hbarnums;i++) {
        if(myrpoint2>secs[i].p)
            continue;
        else {
            sidx2=i;
            break;
        }
    }
    // we're depnding oon final value of i
    printf("Ans. At line segment index=%i just before %2.6f of type %i, currlen=%2.6f prevlen=%2.6f\n", i, secs[sidx].p, secs[sidx].t, secs[sidx].p,secs[i-1].p); 
    printf("Ans. At line segment index=%i just before %2.6f of type %i, currlen=%2.6f prevlen=%2.6f\n", i, secs[sidx2].p, secs[sidx2].t, secs[sidx2].p,secs[i-1].p); 
    // printf("SoAns. At line segment index=%i just before %2.6f of type %i\n", i, secs[i].p, secs[i].t); 
    
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
    // grillit(cr, lb, VBARNUMS, hbarnums, radi); /// colours whole grill
    grillit2(cr, lb, sidx, secs, VBARNUMS, hbarnums, radi, tglen, myrpoint);
    cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);
    // grillit4(cr, lb, sidx, secs, VBARNUMS, hbarnums, radi, tglen, myrpoint, myrpoint2);
    cairo_set_source_rgb(cr, 0.8, 0.7, 0.5);
    grillit3(cr, lb, sidx, secs, VBARNUMS, hbarnums, radi, tglen, myrpoint2);

    // adding arrows in an effort to emphasise direction
    // not the only option, could also do alternative background shades ...
    // addarr(cr, lb, VBARNUMS, hbarnums);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "grill22.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(lb);
    free(secs);

    return 0;
}
