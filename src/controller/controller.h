#include <main_menu.h>
#include <gtk/gtk.h>

int controller (int argc, char *argv[]);

void execute(GtkWidget *widget, gpointer data);

void set_log_file(GtkWidget *widget, gpointer data);
gboolean set_title(GtkWidget *widget, gpointer data);
void set_screen_mode(GtkWidget *widget, gpointer data);
void set_background_color(GtkWidget *widget, gpointer data);
void set_camera_mode(GtkWidget *widget, gpointer data);

void set_subtitle_file(GtkWidget *widget, gpointer data);
gboolean set_font_size(GtkWidget *widget, gpointer data);
gboolean set_duration(GtkWidget *widget, gpointer data);
void set_subtitle_color(GtkWidget *widget, gpointer data);

gboolean set_auto_skip(GtkWidget *widget, gpointer data);
gboolean set_seconds_per_day(GtkWidget *widget, gpointer data);
gboolean set_date_format(GtkWidget *widget, gpointer data);
void set_avatar_folder(GtkWidget *widget, gpointer data);
void set_output_gource(GtkWidget *widget);
