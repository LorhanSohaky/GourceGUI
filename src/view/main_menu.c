/*
The MIT License (MIT)
Copyright (c) 2016 Lorhan Sohaky
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "main_menu.h"
#include "call_backs_main_menu.h"
#include "caption_page.h"
#include "gource.h"
#include "other_page.h"
#include "video_page.h"
#include <gtk/gtk.h>

GtkWidget *add_notebook( GtkWidget *window, Gource *gource );
void add_notebook_tab( GtkWidget *notebook, char *label, GtkWidget *page );

void activate( GtkApplication *app, gpointer data ) {
    Gource *gource = (Gource *)data;
    GtkWidget *window = gtk_application_window_new( app );
    gtk_window_set_title( GTK_WINDOW( window ), "GourceGUI" );
    gtk_window_set_default_size( GTK_WINDOW( window ), 358, 255 );
    gtk_window_set_resizable( GTK_WINDOW( window ), FALSE );
    gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );

    GtkWidget *button = gtk_button_new_with_label(
        "Execute" ); // TODO change background color:#5cb85c border:#4cae4c
    g_signal_connect( button, "clicked", G_CALLBACK( execute ), gource );
    gtk_widget_set_valign( button,
                           GTK_ALIGN_END ); // TODO on hover background color:#449d44 border:#398439

    GtkWidget *notebook = add_notebook( window, gource );
    gtk_widget_set_vexpand( notebook, TRUE );
    gtk_widget_set_valign( notebook, GTK_ALIGN_FILL );

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous( GTK_GRID( grid ), TRUE );
    gtk_container_add( GTK_CONTAINER( window ), grid );
    gtk_grid_attach( GTK_GRID( grid ), notebook, 0, 0, 1, 1 );
    gtk_grid_attach( GTK_GRID( grid ), button, 0, 1, 1, 1 );

    gtk_widget_show_all( window );
}

GtkWidget *add_notebook( GtkWidget *window, Gource *gource ) {
    GtkWidget *notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos( GTK_NOTEBOOK( notebook ), GTK_POS_TOP );
    add_notebook_tab( notebook, "Video", init_video_page( window, gource ) );
    add_notebook_tab( notebook, "Caption", init_caption_page( window, gource ) );
    add_notebook_tab( notebook, "Other settings", init_other_page( window, gource ) );
    return notebook;
}

void add_notebook_tab( GtkWidget *notebook, char *label, GtkWidget *page ) {
    GtkWidget *g_label;

    g_label = gtk_label_new( label );
    gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), page, g_label );
}
