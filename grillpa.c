/* uses grillpa.c : parametrization in the grill. */
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
#define DWX (CW-LMAR-RMAR) // drawable width extent
#define DHX (CH-TMAR-BMAR) // drawable height extent
#define LWID 3

#define OURMAX 100 // i.e. our max 

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

void chkslb(pos_t *lb, d_t *secs, int hbarnums, int vbarnums)
{
    // exploring connection between secs the parametrization (just distance, no coords and the coords
    // int i, j, k, k2;
    int i, k2;
    /*
    for(i=0;i<hbarnums;i++)
        for(j=0;j<vbarnums;j++) {
            k=i*vbarnums+j;
            k2=(k+1)%2;
            printf("%2.6f:%i - (%2.4f,%2.4f)\n", secs[k2].p, secs[k2].t, lb[i*vbarnums+j].x, lb[i*vbarnums+j].y);
        }
        */
    int totp=hbarnums*vbarnums;
    printf("totp=%i\n", totp); 
    // printf("%2.6f:%i - (%2.4f,%2.4f)\n", secs[k2].p, secs[k2].t, lb[0].x, lb[0].y); // the trivial one
    for(i=0;i<totp;i++) {
            k2=(i+1)%2;
            printf("%2.6f:%i\n", secs[i].p, secs[i].t, lb[k2].x, lb[k2].y);
        }
}

int main (int argc, char *argv[])
{
    if(argc!=2) {
        printf("1 arg: 1) number of horiz bars\n");
        exit(EXIT_FAILURE);
    }

    int i, j;
    int hbarnums=atoi(argv[1]);
    float hbarsz=DHX/hbarnums; // y direction.
    float radi=hbarsz/2.; //radiu os connecting half circles.

    // now the drawable
    pos_t dtl;
    dtl.x=LMAR+radi; // dtl: drawable top left
    dtl.y=TMAR;

    /* vertical divider how ar ewe going to section off the screen vertically */
    float dwxt=DWX-2*radi; // extent of drawables
    float tglen=hbarnums*DWX+M_PI*radi*(hbarnums-1); // total grill length: pi*radi is a semicircles circum, and in total there's one less than horizontal bars
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
    
    int totpoints = hbarnums*2;
    pos_t *lb=calloc(totpoints, sizeof(pos_t)); /* ori: origin, lb, last bar, */

    // first point, top left
    lb[0].x= LMAR+radi;
    lb[0].y = TMAR + 3*hbarsz/4.;
    // first row, only x changes
    for(i=1;i<2;i++) {
         lb[i].x= lb[i-1].x + dwxt;
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

    chkslb(lb, secs, hbarnums);

    /* Write output and clean up */
    free(lb);
    free(secs);

    return 0;
}
