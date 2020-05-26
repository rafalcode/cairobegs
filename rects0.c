/* a 9 by nine matrix of rectangles 
 * the first in a series exploring heatmap colors*/
/* another case of coming back to something and it not working at all */
#include <cairo/cairo.h>

#define GW 640 /* grid width */
#define GH GW /* grid height */
#define BW 120 /* grid width */
#define BH 100 /* grid height */
#define BPx 40 /* starting pt of block in xdir */
#define BPy 200 /* starting pt of block in ydir */

float classhmap[256][3] = { {255/255.0, 237/255.0, 237/255.0}, {255/255.0, 224/255.0, 224/255.0}, {255/255.0, 209/255.0, 209/255.0}, {255/255.0, 193/255.0, 193/255.0}, {255/255.0, 176/255.0, 176/255.0}, {255/255.0, 159/255.0, 159/255.0}, {255/255.0, 142/255.0, 142/255.0}, {255/255.0, 126/255.0, 126/255.0}, {255/255.0, 110/255.0, 110/255.0}, {255/255.0, 94/255.0, 94/255.0}, {255/255.0, 81/255.0, 81/255.0}, {255/255.0, 67/255.0, 67/255.0}, {255/255.0, 56/255.0, 56/255.0}, {255/255.0, 46/255.0, 46/255.0}, {255/255.0, 37/255.0, 37/255.0}, {255/255.0, 29/255.0, 29/255.0}, {255/255.0, 23/255.0, 23/255.0}, {255/255.0, 18/255.0, 18/255.0}, {255/255.0, 14/255.0, 14/255.0}, {255/255.0, 11/255.0, 11/255.0}, {255/255.0, 8/255.0, 8/255.0}, {255/255.0, 6/255.0, 6/255.0}, {255/255.0, 5/255.0, 5/255.0}, {255/255.0, 3/255.0, 3/255.0}, {255/255.0, 2/255.0, 2/255.0}, {255/255.0, 2/255.0, 2/255.0}, {255/255.0, 1/255.0, 1/255.0}, {255/255.0, 1/255.0, 1/255.0}, {255/255.0, 0/255.0, 0/255.0}, {255/255.0, 0/255.0, 0/255.0}, {255/255.0, 0/255.0, 0/255.0}, {255/255.0, 0/255.0, 0/255.0}, {255/255.0, 0/255.0, 0/255.0}, {255/255.0, 0/255.0, 0/255.0}, {255/255.0, 0/255.0, 0/255.0}, {255/255.0, 0/255.0, 0/255.0}, {255/255.0, 1/255.0, 0/255.0}, {255/255.0, 4/255.0, 0/255.0}, {255/255.0, 6/255.0, 0/255.0}, {255/255.0, 10/255.0, 0/255.0}, {255/255.0, 14/255.0, 0/255.0}, {255/255.0, 18/255.0, 0/255.0}, {255/255.0, 22/255.0, 0/255.0}, {255/255.0, 26/255.0, 0/255.0}, {255/255.0, 31/255.0, 0/255.0}, {255/255.0, 36/255.0, 0/255.0}, {255/255.0, 41/255.0, 0/255.0}, {255/255.0, 45/255.0, 0/255.0}, {255/255.0, 51/255.0, 0/255.0}, {255/255.0, 57/255.0, 0/255.0}, {255/255.0, 62/255.0, 0/255.0}, {255/255.0, 68/255.0, 0/255.0}, {255/255.0, 74/255.0, 0/255.0}, {255/255.0, 81/255.0, 0/255.0}, {255/255.0, 86/255.0, 0/255.0}, {255/255.0, 93/255.0, 0/255.0}, {255/255.0, 99/255.0, 0/255.0}, {255/255.0, 105/255.0, 0/255.0}, {255/255.0, 111/255.0, 0/255.0}, {255/255.0, 118/255.0, 0/255.0}, {255/255.0, 124/255.0, 0/255.0}, {255/255.0, 131/255.0, 0/255.0}, {255/255.0, 137/255.0, 0/255.0}, {255/255.0, 144/255.0, 0/255.0}, {255/255.0, 150/255.0, 0/255.0}, {255/255.0, 156/255.0, 0/255.0}, {255/255.0, 163/255.0, 0/255.0}, {255/255.0, 169/255.0, 0/255.0}, {255/255.0, 175/255.0, 0/255.0}, {255/255.0, 181/255.0, 0/255.0}, {255/255.0, 187/255.0, 0/255.0}, {255/255.0, 192/255.0, 0/255.0}, {255/255.0, 198/255.0, 0/255.0}, {255/255.0, 203/255.0, 0/255.0}, {255/255.0, 208/255.0, 0/255.0}, {255/255.0, 213/255.0, 0/255.0}, {255/255.0, 218/255.0, 0/255.0}, {255/255.0, 222/255.0, 0/255.0}, {255/255.0, 227/255.0, 0/255.0}, {255/255.0, 232/255.0, 0/255.0}, {255/255.0, 235/255.0, 0/255.0}, {255/255.0, 238/255.0, 0/255.0}, {255/255.0, 242/255.0, 0/255.0}, {255/255.0, 245/255.0, 0/255.0}, {255/255.0, 247/255.0, 0/255.0}, {255/255.0, 250/255.0, 0/255.0}, {255/255.0, 251/255.0, 0/255.0}, {253/255.0, 252/255.0, 0/255.0}, {250/255.0, 252/255.0, 1/255.0}, {248/255.0, 252/255.0, 2/255.0}, {244/255.0, 252/255.0, 2/255.0}, {241/255.0, 252/255.0, 3/255.0}, {237/255.0, 252/255.0, 3/255.0}, {233/255.0, 252/255.0, 3/255.0}, {229/255.0, 252/255.0, 4/255.0}, {225/255.0, 252/255.0, 4/255.0}, {220/255.0, 252/255.0, 5/255.0}, {216/255.0, 252/255.0, 5/255.0}, {211/255.0, 252/255.0, 6/255.0}, {206/255.0, 252/255.0, 7/255.0}, {201/255.0, 252/255.0, 7/255.0}, {197/255.0, 252/255.0, 8/255.0}, {191/255.0, 251/255.0, 8/255.0}, {185/255.0, 249/255.0, 9/255.0}, {180/255.0, 247/255.0, 9/255.0}, {174/255.0, 246/255.0, 10/255.0}, {169/255.0, 244/255.0, 11/255.0}, {164/255.0, 242/255.0, 11/255.0}, {158/255.0, 240/255.0, 12/255.0}, {151/255.0, 238/255.0, 13/255.0}, {146/255.0, 236/255.0, 14/255.0}, {140/255.0, 233/255.0, 14/255.0}, {134/255.0, 231/255.0, 15/255.0}, {128/255.0, 228/255.0, 16/255.0}, {122/255.0, 226/255.0, 17/255.0}, {116/255.0, 223/255.0, 18/255.0}, {110/255.0, 221/255.0, 19/255.0}, {105/255.0, 218/255.0, 20/255.0}, {99/255.0, 216/255.0, 21/255.0}, {93/255.0, 214/255.0, 22/255.0}, {88/255.0, 211/255.0, 23/255.0}, {82/255.0, 209/255.0, 24/255.0}, {76/255.0, 207/255.0, 25/255.0}, {71/255.0, 204/255.0, 26/255.0}, {66/255.0, 202/255.0, 28/255.0}, {60/255.0, 200/255.0, 30/255.0}, {55/255.0, 198/255.0, 31/255.0}, {50/255.0, 196/255.0, 33/255.0}, {45/255.0, 194/255.0, 34/255.0}, {40/255.0, 191/255.0, 35/255.0}, {36/255.0, 190/255.0, 37/255.0}, {31/255.0, 188/255.0, 39/255.0}, {27/255.0, 187/255.0, 40/255.0}, {23/255.0, 185/255.0, 43/255.0}, {19/255.0, 184/255.0, 44/255.0}, {15/255.0, 183/255.0, 46/255.0}, {12/255.0, 182/255.0, 48/255.0}, {9/255.0, 181/255.0, 51/255.0}, {6/255.0, 181/255.0, 53/255.0}, {3/255.0, 180/255.0, 55/255.0}, {1/255.0, 180/255.0, 57/255.0}, {0/255.0, 180/255.0, 60/255.0}, {0/255.0, 180/255.0, 62/255.0}, {0/255.0, 180/255.0, 65/255.0}, {0/255.0, 181/255.0, 68/255.0}, {0/255.0, 182/255.0, 70/255.0}, {0/255.0, 182/255.0, 74/255.0}, {0/255.0, 183/255.0, 77/255.0}, {0/255.0, 184/255.0, 80/255.0}, {0/255.0, 184/255.0, 84/255.0}, {0/255.0, 186/255.0, 88/255.0}, {0/255.0, 187/255.0, 92/255.0}, {0/255.0, 188/255.0, 95/255.0}, {0/255.0, 190/255.0, 99/255.0}, {0/255.0, 191/255.0, 104/255.0}, {0/255.0, 193/255.0, 108/255.0}, {0/255.0, 194/255.0, 112/255.0}, {0/255.0, 196/255.0, 116/255.0}, {0/255.0, 198/255.0, 120/255.0}, {0/255.0, 200/255.0, 125/255.0}, {0/255.0, 201/255.0, 129/255.0}, {0/255.0, 203/255.0, 134/255.0}, {0/255.0, 205/255.0, 138/255.0}, {0/255.0, 207/255.0, 143/255.0}, {0/255.0, 209/255.0, 147/255.0}, {0/255.0, 211/255.0, 151/255.0}, {0/255.0, 213/255.0, 156/255.0}, {0/255.0, 215/255.0, 160/255.0}, {0/255.0, 216/255.0, 165/255.0}, {0/255.0, 219/255.0, 171/255.0}, {0/255.0, 222/255.0, 178/255.0}, {0/255.0, 224/255.0, 184/255.0}, {0/255.0, 227/255.0, 190/255.0}, {0/255.0, 229/255.0, 197/255.0}, {0/255.0, 231/255.0, 203/255.0}, {0/255.0, 233/255.0, 209/255.0}, {0/255.0, 234/255.0, 214/255.0}, {0/255.0, 234/255.0, 220/255.0}, {0/255.0, 234/255.0, 225/255.0}, {0/255.0, 234/255.0, 230/255.0}, {0/255.0, 234/255.0, 234/255.0}, {0/255.0, 234/255.0, 238/255.0}, {0/255.0, 234/255.0, 242/255.0}, {0/255.0, 234/255.0, 246/255.0}, {0/255.0, 234/255.0, 248/255.0}, {0/255.0, 234/255.0, 251/255.0}, {0/255.0, 234/255.0, 254/255.0}, {0/255.0, 234/255.0, 255/255.0}, {0/255.0, 232/255.0, 255/255.0}, {0/255.0, 228/255.0, 255/255.0}, {0/255.0, 224/255.0, 255/255.0}, {0/255.0, 219/255.0, 255/255.0}, {0/255.0, 214/255.0, 254/255.0}, {0/255.0, 208/255.0, 252/255.0}, {0/255.0, 202/255.0, 250/255.0}, {0/255.0, 195/255.0, 247/255.0}, {0/255.0, 188/255.0, 244/255.0}, {0/255.0, 180/255.0, 240/255.0}, {0/255.0, 173/255.0, 236/255.0}, {0/255.0, 164/255.0, 232/255.0}, {0/255.0, 156/255.0, 228/255.0}, {0/255.0, 147/255.0, 222/255.0}, {0/255.0, 139/255.0, 218/255.0}, {0/255.0, 130/255.0, 213/255.0}, {0/255.0, 122/255.0, 208/255.0}, {0/255.0, 117/255.0, 205/255.0}, {0/255.0, 112/255.0, 203/255.0}, {0/255.0, 107/255.0, 199/255.0}, {0/255.0, 99/255.0, 196/255.0}, {0/255.0, 93/255.0, 193/255.0}, {0/255.0, 86/255.0, 189/255.0}, {0/255.0, 78/255.0, 184/255.0}, {0/255.0, 71/255.0, 180/255.0}, {0/255.0, 65/255.0, 175/255.0}, {0/255.0, 58/255.0, 171/255.0}, {0/255.0, 52/255.0, 167/255.0}, {0/255.0, 46/255.0, 162/255.0}, {0/255.0, 40/255.0, 157/255.0}, {0/255.0, 35/255.0, 152/255.0}, {0/255.0, 30/255.0, 147/255.0}, {0/255.0, 26/255.0, 142/255.0}, {0/255.0, 22/255.0, 136/255.0}, {0/255.0, 18/255.0, 131/255.0}, {0/255.0, 15/255.0, 126/255.0}, {0/255.0, 12/255.0, 120/255.0}, {0/255.0, 9/255.0, 115/255.0}, {1/255.0, 8/255.0, 110/255.0}, {1/255.0, 6/255.0, 106/255.0}, {1/255.0, 5/255.0, 101/255.0}, {2/255.0, 4/255.0, 97/255.0}, {3/255.0, 4/255.0, 92/255.0}, {4/255.0, 5/255.0, 89/255.0}, {5/255.0, 5/255.0, 85/255.0}, {6/255.0, 6/255.0, 82/255.0}, {7/255.0, 7/255.0, 79/255.0}, {8/255.0, 8/255.0, 77/255.0}, {10/255.0, 10/255.0, 77/255.0}, {12/255.0, 12/255.0, 77/255.0}, {14/255.0, 14/255.0, 76/255.0}, {16/255.0, 16/255.0, 74/255.0}, {19/255.0, 19/255.0, 73/255.0}, {21/255.0, 21/255.0, 72/255.0}, {24/255.0, 24/255.0, 71/255.0}, {26/255.0, 26/255.0, 69/255.0}, {29/255.0, 29/255.0, 70/255.0}, {32/255.0, 32/255.0, 69/255.0}, {35/255.0, 35/255.0, 68/255.0}, {37/255.0, 37/255.0, 67/255.0}, {40/255.0, 40/255.0, 67/255.0}, {42/255.0, 42/255.0, 65/255.0}, {44/255.0, 44/255.0, 65/255.0}, {46/255.0, 46/255.0, 64/255.0}, {48/255.0, 48/255.0, 63/255.0}, {49/255.0, 50/255.0, 62/255.0}, {51/255.0, 51/255.0, 61/255.0}, {53/255.0, 52/255.0, 61/255.0} };

int main (int argc, char *argv[])
{

    cairo_surface_t *surface;
    cairo_t *cr;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, GW, GH);
    cr = cairo_create (surface);
    /* Examples are in 1.0 x 1.0 coordinate space */
    cairo_rectangle (cr, 0, 0, GW, GH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    int i, j, k;
    for (i=1; i<10; i++)
        for (j=1; j<10; j++) {
            k=i*20+2*j;
            // cairo_set_source_rgb(cr, classhmap[k][0], classhmap[k][1], classhmap[k][2]);
            cairo_set_source_rgb(cr, 0.2, 0.8, 0.9);
            cairo_rectangle (cr, i/10.0 - 0.04, j/10.0 - 0.04, 0.08, 0.08);
            cairo_fill (cr);
        }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "rects0.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}

