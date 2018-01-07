#ifndef CALL_BACKS_OTHER_PAGE_H

#define CALL_BACKS_OTHER_PAGE_H

#include <gtk/gtk.h>

gboolean set_auto_skip( GtkWidget *widget, gpointer data );
gboolean set_seconds_per_day( GtkWidget *widget, gpointer data );
gboolean set_date_format( GtkWidget *widget, gpointer data );
void set_avatar_folder( GtkWidget *widget, gpointer data );
void set_output_gource( GtkWidget *widget, gpointer data );

#endif
