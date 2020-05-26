/* simplest experiment to divide a screen out and draw lines */
#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ASZ 32
#define STEP 10
#define RSEED 3
#define NUMWALKS 4

#define VSPLITS 32
#define HSPLITS 32
#define WIDTH 640
#define HEIGHT WIDTH

void freemy2Darr(int **carr)
{
    int i;
    for(i=0; i<NUMWALKS; ++i) 
        free(carr[i]);
    free(carr);
}

int **createmy2Drwalkcarr(void)
{

    int **carr; /*  this will be the array which holds our random walk, the prefix "c" is for cumulative, see below as we build it */
    unsigned int i, j, rhold;
    carr=malloc(NUMWALKS*sizeof(int *));
    for(i=0; i<NUMWALKS; ++i) 
        carr[i]=calloc(ASZ,sizeof(int));

    srand(RSEED);

    for(j=0; j<NUMWALKS; ++j) {
        rhold=rand(); /* only one random number required (as they fgo up to RAND_MAX */

        for(i=1; i<ASZ; ++i) /* we start on the second entry ... note how the first entry is already zero due to the previous calloc */
            carr[j][i] = STEP - (rhold>>i & 1)*STEP*2 + carr[j][i-1]; /* 1's and 0's rendered into -STEP and +STEP (respectively) */
    }
    return carr;
}

int main (int argc, char *argv[])
{
    int i, j;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, WIDTH, HEIGHT); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* by vertical splits is how we section off the screen vertically, this will be the time axis */
    int vbar=WIDTH / VSPLITS;
    float *hpos;
    hpos=calloc(VSPLITS,sizeof(float));
    /* arrange array of horizontal positions, these will be the midpoints of the vertical bars
     * Mnemonic phrase: vertical bars define the hpos's */
    j=1;
    for(i=0;i<VSPLITS;i++) { 
        hpos[i] = j*vbar/2.0;
        j+=2;
    }

    /* Drawing code goes here */
    cairo_set_line_width (cr, 1);

    int **carr;

    carr=createmy2Drwalkcarr();

    cairo_set_source_rgba(cr, 0.25, 0.8, 0.25, 0.6); /* just one colour for now */
    for(j=0; j<NUMWALKS; ++j) {
        cairo_move_to(cr, hpos[0], carr[j][0] + HEIGHT/2);
        for(i=1; i<ASZ; ++i) { /* we start on the second entry ... note how the first entry is already zero due to the previous calloc */
            cairo_line_to(cr, hpos[i], carr[j][i] + HEIGHT/2); /*  the line directive .. */
            cairo_stroke(cr); /*  gives the line a stroke */
            cairo_move_to(cr, hpos[i], carr[j][i] + HEIGHT/2); /* moves currpt (ciaro inbuilt) to where the line ended. */
        }
    }


    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "linev.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    free(hpos);
    freemy2Darr(carr);

    return 0;
}
