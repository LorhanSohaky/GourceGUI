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

#include "subtitle_page.h"
#include "controller.h"
#include "gource.h"
#include <stdlib.h>

GtkWidget *init_subtitle_page( GtkWidget *window ) {
    GtkWidget *grid, *widget;
    GdkRGBA rgba;
    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous( GTK_GRID( grid ), TRUE );
    gtk_grid_set_row_homogeneous( GTK_GRID( grid ), TRUE );
    gtk_container_set_border_width( GTK_CONTAINER( grid ), 10 );

    widget = gtk_label_new( "Subtitle file: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 0, 1, 1 );

    widget = gtk_file_chooser_button_new( "Choose a file for the subtitle",
                                          GTK_FILE_CHOOSER_ACTION_OPEN );
    g_signal_connect( widget, "file-set", G_CALLBACK( set_subtitle_file ), NULL );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 0, 1, 1 );

    widget = gtk_label_new( "Font size: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 1, 1, 1 );

    widget = gtk_spin_button_new_with_range( 0, 100, 1 );
    g_signal_connect( widget, "focus-out-event", G_CALLBACK( set_font_size ), NULL );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 1, 1, 1 );

    widget = gtk_label_new( "Duration: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 2, 1, 1 );

    widget = gtk_spin_button_new_with_range( 0, 100, 1 );
    gtk_spin_button_set_value( GTK_SPIN_BUTTON( widget ), atoi( DEFAULT_CAPTION_DURATION ) );
    g_signal_connect( widget, "focus-out-event", G_CALLBACK( set_duration ), NULL );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 2, 1, 1 );

    widget = gtk_label_new( "Color: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 3, 1, 1 );

    gdk_rgba_parse( &rgba, DEFAULT_CAPTION_COLOR );
    widget = gtk_color_button_new_with_rgba( &rgba );
    gtk_color_button_set_title( GTK_COLOR_BUTTON( widget ), "Choose a color for the subtitle" );
    g_signal_connect( widget, "color-set", G_CALLBACK( set_subtitle_color ), NULL );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 3, 1, 1 );

    return grid;
}
