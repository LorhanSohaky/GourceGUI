#include <gtk/gtk.h>
#include <stdio.h>
#include <video_page.h>
#include <subtitle_page.h>


typedef struct{
    char *log_file_for_gource;
    char *log_file_for_subtitle;
}_properties;

void activate (GtkApplication* app,gpointer user_data);
GtkWidget *add_notebook(GtkWidget *window);
void add_notebook_tab(GtkWidget *notebook, char *label, GtkWidget *page);
