/* take timestr1.c and this time, produce dots at the ponts
 * and make the preceding line (or the line lkeading up to that point) belong to the path of that point */
#define _GNU_SOURCE // actually needed for getline 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<sys/stat.h>
#include <cairo/cairo.h>

#define IW 640 // image/canvas width
#define IH 480 // height
#define LMAR 20
#define RMAR 20
#define TMAR 50
#define BMAR 20

#define RSEED 34 // 34 got "chip off the old block"
#define NROWS 32
#define LFRAC .25 // the fraction of each row given to the line

#define LINEWID 1. // can't have .5 of this go over margins, then whole frame will overflow

#define THROWAWAYMEMSZ 128
#define GBUF 4
#define CONDREALLOC(x, b, c, a, t, a2, t2); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
        (a2)=realloc((a2), (b)*sizeof(t2)); \
        for(i=((b)-(c));i<(b);++i) { \
            ((a)[i]) = NULL; \
            ((a2)[i]) = 0; \
        } \
    }

typedef struct /* dpt_t: drawable point type */
{
    float x, y;
} dpt_t; 

typedef struct /* larr_t line array struct */
{
    char **l;
    size_t *lz;
    int lbf;
    int asz;
} larr_t;

larr_t *slurplines(char *fn)
{
    FILE *stream;
    // char *line = NULL;
    size_t len = 0;
    int i;

    stream = fopen(fn, "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    larr_t *la=malloc(sizeof(larr_t));
    la->lbf=GBUF;
    la->asz=0;
    la->l=malloc(la->lbf*sizeof(char*)); // does need this, yes, though later it won't be free'd
    la->lz=malloc(la->lbf*sizeof(size_t)); // does need this, yes, though later it won't be free'd
    for(i=0;i<la->lbf;++i) {
        la->lz[i]=0;
        la->l[i]=NULL;
    }

    while ((la->lz[la->asz] = getline(la->l+la->asz, &len, stream)) != -1) {
        // nread is number of returned characters
        CONDREALLOC(la->asz, la->lbf, GBUF, la->l, char*, la->lz, size_t);
        // printf("Retrieved line of length (returned val method): %zu\n", nread);
        // printf("Retrieved line of length (strlen method): %zu\n", strlen(line));
        // fwrite(line, nread, 1, stdout);
        if(la->l[la->asz][la->lz[la->asz]-1]=='\n') // check the newline
            la->l[la->asz][la->lz[la->asz]-1]='\0'; // smash the newline, of course you could save a byte and reallocate, etc. etc.
        la->asz++;
    }

    /* now to see if normalise works */
    for(i=la->asz;i<la->lbf;++i)
        free(la->l[i]);
    la->l=realloc(la->l, la->asz*sizeof(char*)); // normalize
    la->lz=realloc(la->lz, la->asz*sizeof(size_t)); // normalize

    /* Ok that's it */
    fclose(stream);
    return la;
}

long long *getsecs(larr_t *la)
{
    long long *secarray=calloc(la->asz, sizeof(long long)); 

    int i;
    struct tm *tm_var=calloc(1, sizeof(struct tm));
    // this program only covers time in a single day, we choose 01/01/1970 to make it easy. month=0 is Jan actually.
    tm_var->tm_mday=1;
    tm_var->tm_year=70;
    char *mtime_str=calloc(THROWAWAYMEMSZ, sizeof(char));

    for(i=0;i<la->asz;++i) {
        sscanf(la->l[i], "%2d%2d%2d", &tm_var->tm_hour, &tm_var->tm_min, &tm_var->tm_sec);

        if (strftime(mtime_str, THROWAWAYMEMSZ, "%s", tm_var) == 0) {
            fprintf(stderr, "strftime returned 0");
            exit(EXIT_FAILURE);
        }

        secarray[i]=atol(mtime_str);
    }

    // allow some warnings.
    for(i=1;i<la->asz;++i) {
        // printf("%lli\n", secarray[i]); 
        if(secarray[i] < secarray[i-1])
            printf("Not monotonically increasingi entry found at idx %i\n", i); 
        else if(secarray[i] == secarray[i-1])
            printf("Repeat second entry found at idx %i\n", i); 
    }
    printf("endtime-startime=%lli\n", secarray[la->asz-1] - secarray[0]); 

    free(tm_var);
    free(mtime_str);
    return secarray;
}

int main (int argc, char *argv[])
{
    if(argc!=2)  {
        printf("One arg required: filename six digit continuous timespecs per line\n");
        exit(EXIT_FAILURE);
    }
    larr_t *la=slurplines(argv[1]);
    printf("how many timespec lines? i.e. asz :%i\n", la->asz); 

    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);

    int i;

    /* our drawable are is smaller than canvas as define by the MAR values (i.e. margins) */
    float x1=LMAR;
    float y1=TMAR;
    float xspace=(IW-LMAR-RMAR); // drawable space x-wise PER ROW
    float xspacex=xspace*NROWS; // expanded xspace due to folds/wrapping
    float yspace=(float)(IH-TMAR-BMAR); // drawable space y-wise PER ROW
    float yspacer=yspace/NROWS; // drawable space y-wise PER ROW, yspace is reduced therefore yspacer

    /* now set background of the drawable */
    cairo_rectangle (cr, x1, y1, xspace, yspace);
    cairo_set_source_rgba(cr, .05, .05, .05, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);
    printf("xspa %2.2f yspa %2.2f\n", xspace, yspace); 

    //get the time points.
    long long *secarray=getsecs(la);

    // int *xbarsza=calloc(la->asz-1, sizeof(int));
    // for(i=0;i<la->asz-1;++i) 
    //     xbarsza[i]=xbarsza[0] + secarray[i+1]-secarray[i];

    long long ext=secarray[la->asz-1] - secarray[0];
    printf("%lli\n", ext); 
    printf("Seconds per pixel=%2.2f\n", ext/xspace); 
    float n2d= xspacex/ext; // "number to divide by" although we choose to multiply better
    printf("n2d, or fraction of pixel that a second represents=%2.6f\n", n2d);
    // for(i=0;i<NTPTS-1;++i) {
    //     printf("%2.2f\n", xbarsza[i]*xspace/ext); 
    //     xspa[i]=xbarsza[i]*xspace/ext; 
    // }
    dpt_t *spa=calloc(la->asz, sizeof(dpt_t)); // here we'll convert secarray to xspace array
                                             //
    const float tfrac=1-LFRAC; // heh, I rtied constant int on this, no!
    spa[0].x=LMAR;
    spa[0].y=TMAR+yspacer*(tfrac+LFRAC/2.); // in the middle
    // printf("%2.2f %2.4f\n", TMAR+yspacer, TMAR+yspacer*(tfrac+LFRAC/2.));
    spa[la->asz-1].x=LMAR+xspace;
    spa[la->asz-1].y=TMAR+yspacer*(tfrac+LFRAC/2.) + (NROWS-1)*yspacer;

    // we want all the possible lines, even if a point does not occur on them, because a line will still have to be drawn.
    float *lineys=calloc(NROWS, sizeof(float)); // line y positions
    for(i=0;i<NROWS;++i) {
        lineys[i]=TMAR+yspacer*(tfrac+LFRAC/2.) + i*yspacer;
    }



    // get some variables together to establish on which row a point has to be moved to, i.e how many folds are required.
    float cval; // curent value
    int timesover=0;
    int oldtimesover=0;
    int nfolds=0; // to track foldppts;
    int *foldpts=calloc(NROWS-1, sizeof(int)); // which spa indices is on a new row?
    for(i=1;i<la->asz-1;++i) {
        cval = (secarray[i] - secarray[0])*n2d; // current val, actually the x position of the point, without considering wrapping/folding.
        timesover = (int)(cval/xspace); // how many times over the permitted xlength tha value is. A floor op done here via casting.
        if(timesover!=oldtimesover)
            foldpts[nfolds++]=i;
        // printf("cval %2.2f to %i\n", cval, timesover); 
        spa[i].x = LMAR+cval- timesover*xspace;
        spa[i].y = TMAR+yspacer*(tfrac+LFRAC/2.) + timesover*yspacer;
        // printf("%2.2f:%2.2f\n", spa[i].x, spa[i].y);
        oldtimesover=timesover;
    }
    // printf("xs: %2.2f\n", xspace/4.);
    printf("Foldpts:\n"); 
    for(i=0;i<nfolds;++i) 
        printf("%i\n", foldpts[i]); 

    for(i=0;i<la->asz;++i)
        printf("%2.2f:%2.2f\n", spa[i].x, spa[i].y);

    cairo_set_line_width (cr, LINEWID);
    // go to first point
    cairo_set_source_rgba(cr, 0.85, 0.1, 0.2, 0.8);
    cairo_arc(cr, spa[0].x, spa[0].y, 3, 0, 2 * M_PI); // you don't needa move_to here.
    cairo_fill(cr);
    cairo_close_path(cr);

    // cairo_move_to(cr, spa[0].x, spa[0].y);
    // these os are line_to and then arc, as a unit.
    int k=0;
    for(i=1;i<la->asz;++i) {
        cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 1.0);
        cairo_move_to(cr, spa[i-1].x, spa[i-1].y);
        // if(i==foldpts[k]) {
        // OK so the next is not all that easy. the point has moved to a the next or even later line, but we need to draw it
        // and it does belong" to the point.
        if(spa[i].y !=lineys[k]) {
            // we need to continue to end of current row, start on next (fold back?)
            cairo_line_to(cr, LMAR+xspace, lineys[k]);
            cairo_close_path(cr);
            cairo_stroke(cr);
            k++;
            while(spa[i].y !=lineys[k]) {
                cairo_move_to(cr, LMAR, lineys[k]);
                cairo_line_to(cr, LMAR+xspace, lineys[k]);
                cairo_close_path(cr);
                k++;
            }
            cairo_move_to(cr, LMAR, spa[i].y);
        }
        cairo_line_to(cr, spa[i].x, spa[i].y);
        cairo_stroke(cr);
        cairo_set_source_rgba(cr, 0.85, 0.1, 0.2, 0.8);
        cairo_arc(cr, spa[i].x, spa[i].y, 3, 0, 2 * M_PI);
        cairo_fill(cr);
        cairo_close_path(cr);
    }

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "timstr2.png");
    cairo_surface_destroy (surface);

    for(i=0;i<la->asz;++i)
        free(la->l[i]);
    free(la->l);
    free(la->lz);
    free(la);
    free(secarray);
    free(spa);

    return 0;
}
