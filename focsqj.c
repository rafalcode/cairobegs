/* a 9 by nine matrix of rectangles 
 * the first in a series exploring heatmap colors*/
/* another case of coming back to something and it not working at all */
#include <stdio.h>
#include <stdlib.h>
#include <cairo/cairo.h>
#include<cairo_jpg.h>

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

int main (int argc, char *argv[])
{

	if(argc!=4) {
		printf("Error. Pls supply 4 args:\n");
		printf("1) width of output image\n");
		printf("2) height of output image\n");
		printf("4) conft file with first line as jpg filename, and rest of lines xcoord, then ycoord, etc.\n");
		exit(EXIT_FAILURE);
	}
    int gw=atoi(argv[1]);
    int gh=atoi(argv[2]);

    larr_t *la=slurplines(argv[3]);
    int numsq=(la->asz-1)/2;
    printf("numsq=%i\n", numsq); 

    cairo_surface_t *surf0 = cairo_image_surface_create_from_jpeg(la->l[0]);
    int iw = cairo_image_surface_get_width (surf0); // input jpg width
    int ih = cairo_image_surface_get_height (surf0); // input jpg height

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, gw, gh);
    cairo_t *cr;

    int minb=10; /// minimum border
    int wsq0=(gw-(numsq+1)*minb)/numsq;
    int h0=wsq0; // because square
    float y0=(gh-h0)/2;

    cr = cairo_create(surface);

    cairo_rectangle (cr, 0, 0, gw, gh); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);
    cairo_destroy (cr);

    int i;
    float clipx, clipy, r2x;
    float mpoi[2];
    for(i=1;i<=numsq;++i)  {
        cr = cairo_create(surface);
        mpoi[0]=atof(la->l[(i-1)*2+1]);
        mpoi[1]=atof(la->l[(i-1)*2+2]);
        printf("mpois:%2.2f %2.2f\n", mpoi[0], mpoi[1]); 
        cairo_set_source_rgb(cr, 0.2, 0.8, 0.9);
        r2x = i*minb+(i-1)*wsq0;
        cairo_rectangle (cr, i*minb+(i-1)*wsq0, y0, wsq0, h0);
        cairo_clip(cr);
        clipx=mpoi[0]-wsq0/2.;
        clipy=mpoi[1]-h0/2.;
        cairo_set_source_surface(cr, surf0, r2x-clipx, y0-clipy);
        cairo_paint (cr);
        cairo_destroy (cr);
     }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "rects03.png");
    cairo_surface_destroy (surface);
    cairo_surface_destroy (surf0);

    return 0;
}

