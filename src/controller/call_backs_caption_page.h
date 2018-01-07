#ifndef CALL_BACKS_CAPTION_PAGE_H

#define CALL_BACKS_CAPTION_PAGE_H

#include <gtk/gtk.h>

void set_caption_file( GtkWidget *widget, gpointer data );
gboolean set_font_size( GtkWidget *widget, gpointer data );
gboolean set_duration( GtkWidget *widget, gpointer data );
void set_caption_color( GtkWidget *widget, gpointer data );

#endif
