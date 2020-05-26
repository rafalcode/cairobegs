/* Image genertorsimplest experiment to divide a screen out and draw lines */
#include <cairo/cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* these two for making the directory */
#include <sys/stat.h>                                                                                                                                 
#include <sys/types.h>                                                                                                                                

#define TMPBUF1 16
#define TMPBUF2 32

#define WIDTH 64
#define HEIGHT WIDTH

int main (int argc, char *argv[])
{
    int i;
	char *num, *fnam, *dnam;
    num=malloc(sizeof(char)*TMPBUF1);
    dnam=malloc(sizeof(char)*TMPBUF1);
    fnam=malloc(sizeof(char)*TMPBUF2);

	if(argc != 2) {
		printf("Error. Pls supply tmpdir name, which is the subdir to store the many files this program outputs.\n");
		exit(EXIT_FAILURE);
	}
    /*  first things first create the directory */
    sprintf(dnam, "%s", argv[1]); // just cannot get this working // just cannot get this working
    mkdir(dnam, 0755); /* this where the directory is made, second arg is a mode_t works as seen here. */

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT);
    cairo_t *cr = cairo_create (surface);

    for(i=0; i<=100; ++i) {
        cairo_rectangle (cr, 0, 0, WIDTH, HEIGHT); /* arg explan: topleftcorner and size of shape  */
        cairo_set_source_rgb (cr, 0.01*i, 0.01*i, 0.01*i); /*  final number is alpha, 1.0 is opaque */
        cairo_fill (cr);

        strcpy(fnam,dnam); /* flush fnam with orginal dnam */
        sprintf(num, "/%04i.png", i);
        strcat(fnam,num);

        cairo_surface_write_to_png (surface, fnam);

    }
    cairo_destroy (cr);
    cairo_surface_destroy(surface);

    free(num);
    free(fnam);
    free(dnam);

    return 0;
}
