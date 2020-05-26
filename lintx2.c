/* Not a bad attempt ... I pull text out of a file and dispplay as cairo
 * I am still stufying the whole fon t and text extents stuff, but this came out OK
 * collection of text in to array of string was quite good */ 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cairo/cairo.h>

#define VBARNUMS 6
#define HBARNUMS 6
#define STRBUF 128 /* ample but not excessive buffer, woul dneed to be modified later */
#define STRPBUF 128 /* ample but not excessive buffer, woul dneed to be modified later */

void creatch(cairo_t *cr, char *alphabet, int im_w, int im_h)
{
    cairo_select_font_face (cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, 14.0);

    cairo_font_extents_t fe;
    cairo_text_extents_t te;
    char letter[2]; /* this will be where we put our individual characters, with the null char to mark them out */

    cairo_font_extents (cr, &fe);

    int i;

    for (i=0; i < strlen(alphabet); i++) {
        *letter = '\0';
        strncat (letter, alphabet + i, 1);

        cairo_text_extents (cr, letter, &te);
        cairo_move_to (cr, i*15 + im_w/2-90 - te.x_bearing - te.width / 2, im_h/2 - fe.descent + fe.height / 2);
        cairo_show_text (cr, letter);
    }
}

void creatstr(cairo_t *cr, char *alphabet, int cnv_w, int cnv_h)
{
/*  this function is like creatch, except not processed char by char, but by whole string
 *  mne for cnv is canvas */
    cairo_select_font_face (cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, 16.0);

    cairo_font_extents_t fe;
    cairo_text_extents_t te;

    cairo_font_extents (cr, &fe);


    cairo_text_extents (cr, alphabet, &te);
    cairo_move_to (cr, cnv_w/2 - te.x_bearing - te.width/2, cnv_h/2 - fe.descent + fe.height / 2);
    cairo_show_text (cr, alphabet);
}

int main (int argc, char *argv[])
{
    int i, im_w=480, im_h=480;
    char ch;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, im_w, im_h);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, im_w, im_h); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* argument accounting: we're going to pull our text from a file */
    FILE *ftin;
    int j=0, k=0;
    char **txt;
    txt=malloc(sizeof(char *)*STRPBUF);
    for(i=0; i<STRPBUF; ++i) 
        txt[i]=malloc(sizeof(char)*STRBUF);
    /* without prev file knowledge apply string buffers */
    if(argc!=2) {
        printf("Error. Pls supply appropriate arguments (filename with text in it).\n");
        exit(EXIT_FAILURE);
    }
    ftin=fopen(argv[1],"r");
    while((ch=fgetc(ftin)) != EOF) {
        if(ch == '\n') {
            txt[j++][k] ='\0';
            k = 0;
        } else 
            txt[j][k++] =ch;
    }

    /* vertical divider how ar ewe going to section off the screen vertically */
    int vbar=im_h/VBARNUMS;
    int vpos[VBARNUMS];
    /* arrange array of positions */
    vpos[0]=vbar/2;
    for(i=1;i<VBARNUMS;i++)
        vpos[i] = vpos[i-1] + vbar;


    /* Drawing code goes here */
    cairo_set_line_width (cr, 4);
    cairo_set_source_rgba(cr, 0.25, 0.8, 0.25, 0.6);
    for(i=0;i<VBARNUMS;i++) {
        cairo_move_to(cr, im_w/2 -50, vpos[i]);
        cairo_line_to(cr, im_w/2 +50, vpos[i]);
        cairo_stroke (cr);
    }
    /*  we want some text now. We have a function, but actually to set color
     *  we need to set color for the whole "cr"  */
    cairo_set_source_rgba (cr, 0.7, 0.6, 0.75, 0.8);
    for(i=0; i<j; ++i) 
        creatstr(cr, txt[i], im_w, im_h*(i+1)/4);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "ltx3.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    for(i=0; i<STRPBUF; ++i) 
        free(txt[i]);
    free(txt);

    return 0;
}
