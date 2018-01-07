#ifndef CALL_BACKS_VIDEO_PAGE_H

#define CALL_BACKS_VIDEO_PAGE_H

#include <gtk/gtk.h>

void set_repository( GtkWidget *widget, gpointer data );
gboolean set_title( GtkWidget *widget, gpointer data );
void set_screen_mode( GtkWidget *widget, gpointer data );
void set_background_color( GtkWidget *widget, gpointer data );
void set_camera_mode( GtkWidget *widget, gpointer data );

#endif
