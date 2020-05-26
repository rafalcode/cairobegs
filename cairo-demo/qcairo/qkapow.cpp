#include "qkapow.h"

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <cairo.h>
#include <math.h>

const char fontname[] = "Sans";
const char default_text[] = "KAPOW";

#define IMAGE_WIDTH  384
#define IMAGE_HEIGHT 256

#define SPIKES 10
#define SHADOW_OFFSET 10

#define X_FUZZ 16
#define Y_FUZZ 16

void QKapow::make_star_path(cairo_t *cr)
{
    double x;
    double y;
    int i;

    srand (45);

    double X_OUTER_RADIUS  = (width() / 2 - X_FUZZ - SHADOW_OFFSET);
    double Y_OUTER_RADIUS  = (height() / 2 - Y_FUZZ - SHADOW_OFFSET);
    double X_INNER_RADIUS  = (X_OUTER_RADIUS * 0.7);
    double Y_INNER_RADIUS  = (Y_OUTER_RADIUS * 0.7);

    for (i = 0; i < SPIKES * 2; i++) {

	x = width() / 2 + cos (M_PI * i / SPIKES) * X_INNER_RADIUS +
	    (double) rand() * X_FUZZ / RAND_MAX;
	y = height() / 2 + sin (M_PI * i / SPIKES) * Y_INNER_RADIUS +
	    (double) rand() * Y_FUZZ / RAND_MAX;

	if (i == 0)
	    cairo_move_to (cr, x, y);
	else
	    cairo_line_to (cr, x, y);

	i++;

	x = width() / 2 + cos (M_PI * i / SPIKES) * X_OUTER_RADIUS +
	    (double) rand() * X_FUZZ / RAND_MAX;
	y = height() / 2 + sin (M_PI * i / SPIKES) * Y_OUTER_RADIUS +
	    (double) rand() * Y_FUZZ / RAND_MAX;

	cairo_line_to (cr, x, y);
    }

    cairo_close_path (cr);
}

void QKapow::bend_it (double *x, double *y)
{
    const double cx = width() / 2, cy = 500;
    double angle, radius, t;

    /* We're going to wrap the points around a big circle with center
     * at (cx, cy), with cy being somewhere well below the visible area.
     * On top of that, we'll scale up the letters going left to right.
     */

    angle = M_PI / 2 - (double) (*x - cx) / width();
    t = 3 * M_PI / 4 - angle + 0.05;
    angle = 3 * M_PI / 4 - pow (t, 1.8);
    radius = cy - (height() / 2 + (*y - height() / 2) * t * 2);

    *x = cx + cos (angle) * radius;
    *y = cy - sin (angle) * radius;
}

void QKapow::make_text_path (cairo_t *cr, double x, double y, const char *text)
{
    m_first = 1;
			     
cairo_path_t *path;
    cairo_path_data_t *data;
    int i;

    cairo_move_to (cr, x, y);
    cairo_text_path (cr, text);

    path = cairo_copy_path_flat (cr);

    cairo_new_path (cr);

    for (i=0; i < path->num_data; i += path->data[i].header.length) {
	data = &path->data[i];
	switch (data->header.type) {
	case CAIRO_PATH_MOVE_TO:
	    x = data[1].point.x;
	    y = data[1].point.y;
	    bend_it (&x, &y);
	    cairo_move_to (cr, x, y);
	    break;
	case CAIRO_PATH_LINE_TO:
	    x = data[1].point.x;
	    y = data[1].point.y;
	    bend_it (&x, &y);
	    cairo_line_to (cr, x, y);
	    break;
	case CAIRO_PATH_CLOSE_PATH:
	    cairo_close_path (cr);
	    break;
	default:
	    qDebug("unexpected path element");
	}
    }

    free (path);
}


QKapow::QKapow( QWidget *parent )
    : QCairoWidget( parent ),
      m_text( "sample" )
{
    resize( IMAGE_WIDTH, IMAGE_HEIGHT );
}

void QKapow::cairoPaint( cairo_t *cr, const QRect & )
{
    double x;
    double y;
    QString text = m_text.left(20);
    cairo_text_extents_t extents;
    cairo_pattern_t *pattern;

    cairo_set_line_width (cr, 2);

    cairo_save (cr);
    cairo_translate (cr, SHADOW_OFFSET, SHADOW_OFFSET);
    make_star_path (cr);
    cairo_paint_with_alpha (cr, 0.5);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_fill (cr);
    cairo_restore (cr);

    make_star_path (cr);
    cairo_paint_with_alpha (cr, 1);
    pattern =
	cairo_pattern_create_radial (width() / 2, height() / 2, 10,
				     width() / 2, height() / 2, 230);
    cairo_pattern_add_color_stop_rgba (pattern, 0, 1, 1, 0.2, 1);
    cairo_pattern_add_color_stop_rgba (pattern, 1, 1, 0, 0, 1);
    cairo_set_source (cr, pattern);
    cairo_fill (cr);

    make_star_path (cr);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);

    cairo_select_font_face (cr, fontname,
		       CAIRO_FONT_SLANT_NORMAL,
		       CAIRO_FONT_WEIGHT_BOLD);

    cairo_set_font_size (cr, 50);
    cairo_text_extents (cr, ( const char* )text.latin1(), &extents);
    x = width() / 2 - (extents.width / 2 + extents.x_bearing);
    y = height() / 2 - (extents.height / 2 + extents.y_bearing);

    make_text_path (cr, x, y, text.latin1());

    pattern =
	cairo_pattern_create_linear (width() / 2 - 10, height() / 4,
				     width() / 2 + 10, 3 * height() / 4);
    cairo_pattern_add_color_stop_rgba (pattern, 0, 1, 1, 1, 1);
    cairo_pattern_add_color_stop_rgba (pattern, 1, 0, 0, 0.4, 1);
    cairo_set_source (cr, pattern);

    cairo_fill (cr);

    make_text_path (cr, x, y, text.latin1());
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);

    cairo_show_page (cr);
}

QSize QKapow::sizeHint() const
{
    return size();
}
