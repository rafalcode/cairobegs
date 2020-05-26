/* The puff effect in action
 * Company:   */
#include <cairo/cairo.h>
#include <gtk/gtk.h>


gpointer text[7] = { "Z", "e", "t", "C", "o", "d", "e" };
gboolean timer = TRUE;

static gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
    cairo_t *cr;
    cairo_text_extents_t extents;

    static gdouble alpha = 1.0;
    static gdouble size = 1;


    gint x = widget->allocation.width / 2;
    gint y = widget->allocation.height / 2;

    cr = gdk_cairo_create(widget->window);

    cairo_set_source_rgb(cr, 0.5, 0, 0); 
    cairo_paint(cr);

    cairo_select_font_face(cr, "Courier",
            CAIRO_FONT_SLANT_NORMAL,
            CAIRO_FONT_WEIGHT_BOLD);

    size += 0.8;

    if (size > 20) {
        alpha -= 0.01;
    }

    cairo_set_font_size(cr, size);

    cairo_set_source_rgb(cr, 1, 1, 1); 

    cairo_text_extents(cr, "ZetCode", &extents);
    cairo_move_to(cr, x - extents.width/2, y);
    cairo_text_path(cr, "ZetCode");
    cairo_clip(cr);
    cairo_stroke(cr);
    cairo_paint_with_alpha(cr, alpha);

    if (alpha <= 0) {
        timer = FALSE;
    }

    cairo_destroy(cr);

    return FALSE;
}

static gboolean time_handler (GtkWidget *widget)
{
    if (widget->window == NULL) return FALSE;

    if (!timer) return FALSE;

    gtk_widget_queue_draw(widget);

    return TRUE;
}

int main (int argc, char *argv[])
{
    GtkWidget *window;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(window, "expose-event", G_CALLBACK(on_expose_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 200); 
    gtk_window_set_title(GTK_WINDOW(window), "puff");
    gtk_widget_set_app_paintable(window, TRUE);

    g_timeout_add(14, (GSourceFunc) time_handler, (gpointer) window);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
