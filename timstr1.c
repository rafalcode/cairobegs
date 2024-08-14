/* take timestr0.c and incoporate strf2.c from chwats */
#define _GNU_SOURCE // actually needed for getline 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<sys/stat.h>
#include <cairo/cairo.h>

#define IW 640 // image/canvas width
#define IH 480 // height
#define LMAR 40
#define RMAR 40
#define TMAR 20
#define BMAR 20

#define RSEED 34 // 34 got "chip off the old block"
#define NTPTS 6

#define LINEWID 2. // can't have .5 of this go over margins, then whole frame will overflow

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
    float x1, y1, x2, y2;
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

    /* now set background of he canvas */
    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba(cr, .05, .05, .05, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    int i;

    /* our drawable are is smaller than canvas as define by the MAR values (i.e. margins) */
    float x1=LMAR;
    float y1=TMAR;
    float xspace=IW-LMAR-RMAR; // drawable space x-wise
    float yspace=IH-TMAR-BMAR; // drawable space y-wise
    float y2=TMAR+yspace/2.; // lowest point
    /* now set background of the drawable */
    cairo_rectangle (cr, x1, y1, xspace, yspace);
    cairo_set_source_rgba(cr, .2, .2, .2, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    //get the time points.
    long long *secarray=getsecs(la);

    // int *xbarsza=calloc(la->asz-1, sizeof(int));
    // for(i=0;i<la->asz-1;++i) 
    //     xbarsza[i]=xbarsza[0] + secarray[i+1]-secarray[i];

    long long ext=secarray[la->asz-1] - secarray[0];
    printf("%lli\n", ext); 
    printf("Seconds per pixel=%2.2f\n", ext/xspace); 
    float n2d= xspace/ext; // "number to divide by" although we choose to multiply better
    printf("n2d, or fraction of pixel that a second represents=%2.6f\n", n2d);
    // for(i=0;i<NTPTS-1;++i) {
    //     printf("%2.2f\n", xbarsza[i]*xspace/ext); 
    //     xspa[i]=xbarsza[i]*xspace/ext; 
    // }
    float *xspa=calloc(la->asz, sizeof(float)); // here we'll convert secarray to xspace array
    xspa[0]=LMAR;
    xspa[la->asz-1]=LMAR+xspace;
    for(i=1;i<la->asz-1;++i) // see above, two values already there.
        xspa[i]= xspa[0] + (secarray[i] - secarray[0])*n2d;

    for(i=0;i<la->asz;++i)
        printf("%2.2f\n", xspa[i]);

    cairo_set_line_width (cr, LINEWID);
    cairo_move_to(cr, xspa[0], y1);
    cairo_line_to(cr, xspa[0], y2);
    for(i=0;i<la->asz-1;++i) {
        cairo_move_to(cr, xspa[i], y1);
        cairo_line_to(cr, xspa[i+1], y1);
        cairo_line_to(cr, xspa[i+1], y2);
        cairo_line_to(cr, xspa[i], y2);
        cairo_close_path(cr);
        cairo_set_source_rgb (cr, 0, 0, 0);
        cairo_stroke_preserve(cr);
        if(i%2==0)
            cairo_set_source_rgb (cr, .8, .6, .4);
        else
            cairo_set_source_rgb (cr, .4, .6, .8);
        cairo_fill(cr);
    }


    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "timstr1.png");
    cairo_surface_destroy (surface);

    for(i=0;i<la->asz;++i)
        free(la->l[i]);
    free(la->l);
    free(la->lz);
    free(la);
    free(secarray);
    free(xspa);

    return 0;
}
