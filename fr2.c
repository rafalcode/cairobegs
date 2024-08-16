/* fr for frams
 * here were draw the frame and at the end put a picture in it.
 * Be careful to the put the picutre in an end.
 * CHECKED:
 * - when including outside image, only the expose part is stored. i.e. the clip genuinely crops the image
*/
#include <cairo/cairo.h>
#include <math.h>
#include "rcolp.h"

// image
#define IW 640 // image/canvas width
#define IH 480 // height

// How the margins are encuntered in clockiwise fashion and in Cairo's convention
// Left Right, Top Bottom
// outer margin
#define LOM 20
#define ROM 20
#define TOM 60
#define BOM 30
// outer margin
#define FT0 30 // frame thickness
#define LIM FT0
#define RIM FT0
#define TIM FT0
#define BIM FT0


// x0,y0 - x1,y0
//   |       |
// x0,y1 - x1,y1
// these two: x0 x1 y0 y1
const float OM[4]={LOM, IW-ROM, TOM, IH-BOM};
const float IM[4]={LOM+LIM, IW-ROM-RIM, TOM+TIM, IH-BOM-BIM};
const float ixt[2]={IW-LOM-LIM-ROM-RIM, IH-TOM-TIM-BOM-BIM}; // inner extents x and y

int main (int argc, char *argv[])
{
    int cidx; // colour index
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);

    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */

    cairo_set_source_rgba (cr, .9, .9, .9, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);


    // cairo_set_source_rgb(cr, .2, 0.6, 0.4);
    // cairo_fill(cr);

    cairo_set_line_width (cr, 10.0);

    // Top piece
    cairo_move_to (cr, OM[0], OM[2]);
    cairo_line_to (cr, OM[1], OM[2]);
    cairo_line_to (cr, IM[1], IM[2]);
    cairo_line_to (cr, IM[0], IM[2]);
    cidx=623; // tan
    cairo_set_source_rgb(cr, rcol[cidx].f3[0], rcol[cidx].f3[1], rcol[cidx].f3[2]);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);

    // cidx=623; // tan
    // cairo_set_source_rgb(cr, rcol[cidx].f3[0], rcol[cidx].f3[1], rcol[cidx].f3[2]);
    // cairo_fill_preserve(cr);

    // RHS piece
    cairo_move_to (cr, OM[1], OM[2]);
    cairo_line_to (cr, OM[1], OM[3]);
    cairo_line_to (cr, IM[1], IM[3]);
    cairo_line_to (cr, IM[1], IM[2]);
    cairo_close_path(cr);
    cidx=622; // tan
    cairo_set_source_rgb(cr, rcol[cidx].f3[0], rcol[cidx].f3[1], rcol[cidx].f3[2]);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);

    // bottom piece
    cairo_move_to (cr, OM[1], OM[3]);
    cairo_line_to (cr, OM[0], OM[3]);
    cairo_line_to (cr, IM[0], IM[3]);
    cairo_line_to (cr, IM[1], IM[3]);
    cairo_close_path(cr);
    cidx=622; // tan
    cairo_set_source_rgb(cr, rcol[cidx].f3[0], rcol[cidx].f3[1], rcol[cidx].f3[2]);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);

    // LHS piece
    cairo_move_to (cr, OM[0], OM[3]);
    cairo_line_to (cr, OM[0], OM[2]);
    cairo_line_to (cr, IM[0], IM[2]);
    cairo_line_to (cr, IM[0], IM[3]);
    cairo_close_path(cr);
    cidx=623; // tan
    cairo_set_source_rgb(cr, rcol[cidx].f3[0], rcol[cidx].f3[1], rcol[cidx].f3[2]);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);
    
    // middle
    cairo_rectangle(cr, IM[0], IM[2], ixt[0], ixt[1]);
    cairo_clip(cr); // somehow, this means the rectangle is the only writeable part now.
    // cairo_new_path (cr); /* path not consumed by clip()*/
    // cairo_surface_t *image = cairo_image_surface_create_from_png("Third_folio.png");
    cairo_surface_t *image = cairo_image_surface_create_from_png("corot_corso.png");
    cairo_set_source_surface (cr, image, -340, -300);
    cairo_paint (cr);
    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "fr2.png");
    cairo_surface_destroy (surface);
    cairo_surface_destroy (image);
    return 0;
}
