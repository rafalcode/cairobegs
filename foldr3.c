/* *****************************************************
   partial code credit: Rick Dearman
   following from foldr.c ...extends short lines too 
   Note this can only manage unix terminated lines, not Mac nor DOS.
 ******************************************************/
/*  this ver takes text and render it inot an image */
/*  work in progress, need to look at how line global is being used. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cairo/cairo.h>
/* these two for making the directory */
#include <sys/stat.h>                                                                                                                                 
#include <sys/types.h>                                                                                                                                

#define MAXLINLEN 4000 /*  max input line size */
#define MAXLINES 10 /*  max input line size */
#define FOLDLENGTH 20 /* this will be the max line lenght of the output */

/* for output directory and filenames */
#define TMPBUF1 16
#define TMPBUF2 32
#define WIDTH 640
#define HEIGHT WIDTH

const float FONTSZ=14.0;

/* proto */
int getpara(FILE *, char **);  /*  taken from the KnR book. */

int getpara(FILE *fp, char **line) /* renders a paragraph into a line */
{
    int c, i;

    char oldc ='x'; // x marks the spot .. a variable to keep the previosu character in, initialised by anything except '\n'

    for ( i=0; i<MAXLINLEN-1 && ( c=fgetc(fp)) != EOF; ++i) {
        if ((c=='\n') & (oldc=='\n')) {
            line[0][i-1] = c; // previous \n was converted to a space, must convert it back
            line[0][i] = c;
            break;
        }
        oldc=c;
        if (c=='\n') c= ' ';
        line[0][i] = c;
    }
    /* deal with issue in the last c read was a newrenline: include it explicitly */
    if(oldc == '\n')
        line[0][i++] = oldc;
    /*  among other things, you don't get final '\n' if you don't put this in */

    line[0][i] = '\0'; /* render as string */
    return i;
}

int main(int argc, char *argv[])
{
    int i, t, len, RBSZ;
	char *num, *fnam, *dnam;
    char **line;
    line=malloc(sizeof(char *)*MAXLINES);
    for(i=0; i<MAXLINES; ++i) 
        line[i]=calloc(MAXLINLEN, sizeof(char));

    num=malloc(sizeof(char)*TMPBUF1);
    dnam=malloc(sizeof(char)*TMPBUF1);
    fnam=malloc(sizeof(char)*TMPBUF2);

    /* argument accounting */
    if(argc!=3) {
        printf("Error. Pls textfilename and directory in which to put image files.\n");
        exit(1);
    }
    FILE *fp;
    fp=fopen(argv[1], "r"); // first argument used up for the input here.
    sprintf(dnam, "%s", argv[2]); // second argument used for directoryname to create
    mkdir(dnam, 0755); /* this where the directory is made, second arg is a mode_t works as seen here. */

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT);
    cairo_t *cr = cairo_create (surface);
    cairo_select_font_face (cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, FONTSZ);
    cairo_font_extents_t fe;
    cairo_text_extents_t te;

    int location, spaposholder, j=0/* numlines in each im */, k=0 /* numims */; // mne: space position holder

    while (( len = getpara(fp, line)) > 0 ) { /*  while each call to getpara rtruns at least one char */
            /*  if this is an extra long line then we 
             *  loop through it replacing a space nearest
             *  to the foldarea with a newline. */
            t = 0;
            location = 0;
            while(t<len) {

                if(line[j][t] == ' ')
                    spaposholder = t;

                if(location==FOLDLENGTH) {
                    line[j][spaposholder] = '\0';
                    j++;
                    location = 0;
                }
                location++;
                t++;
            }
            /*  now begins the fairly hefty image prep part */
        cairo_rectangle (cr, 0, 0, WIDTH, HEIGHT); /* arg explan: topleftcorner and size of shape  */
        cairo_set_source_rgba (cr, 0.0, 0.01, 0.01, 0.95); /*  final number is alpha, 1.0 is opaque */
        cairo_fill (cr);
        RBSZ=HEIGHT/j;
        for(i=0; i<j; ++i) {
            cairo_text_extents (cr, line[i], &te);
            cairo_move_to (cr, WIDTH/2 - te.x_bearing - te.width/2, (RBSZ*i + RBSZ/2) - fe.descent + fe.height/2);
            cairo_set_source_rgb(cr, 0.3, 0.2, .2);
            cairo_show_text (cr, line[i]);
        }
        strcpy(fnam,dnam); /* flush fnam with orginal dnam */
        sprintf(num, "/%03i.png", k);
        strcat(fnam,num);
        cairo_surface_write_to_png (surface, fnam);
        k++;
        for(i=0; i<MAXLINES; ++i) 
            memset(line[i],0,MAXLINLEN);
    }

    fclose(fp);
    cairo_destroy (cr);
    cairo_surface_destroy(surface);
    free(num);
    free(fnam);
    free(dnam);
    for(i=0; i<MAXLINES; ++i) 
        free(line[i]);
    return 0;
}
