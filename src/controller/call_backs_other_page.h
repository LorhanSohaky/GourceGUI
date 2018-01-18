#ifndef CALL_BACKS_OTHER_PAGE_H

#define CALL_BACKS_OTHER_PAGE_H

#include <gtk/gtk.h>

gboolean set_auto_skip( GtkWidget *widget, GdkEvent *event, gpointer data );

gboolean set_seconds_per_day( GtkWidget *widget, GdkEvent *event, gpointer data );
gboolean set_date_format( GtkWidget *widget, GdkEvent *event, gpointer data );
void set_avatar_folder( GtkWidget *widget, gpointer data );
// TODO void set_output_gource( GtkWidget *widget, gpointer data );

#endif
