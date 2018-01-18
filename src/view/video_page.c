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

#include "video_page.h"
#include "call_backs_video_page.h"
#include <string.h>

GtkWidget *init_video_page( GtkWidget *window, Gource *gource ) {
    GtkWidget *grid, *widget;
    GdkRGBA rgba;
    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous( GTK_GRID( grid ), TRUE );
    gtk_grid_set_row_homogeneous( GTK_GRID( grid ), TRUE );
    gtk_container_set_border_width( GTK_CONTAINER( grid ), 10 );

    widget = gtk_label_new( "Folder of repository: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 0, 1, 1 );

    widget = gtk_file_chooser_button_new( "Select the folder of the repository",
                                          GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER );
    gtk_file_chooser_set_filename( GTK_FILE_CHOOSER( widget ),
                                   string_get_text( gource->video.repository ) );
    g_signal_connect( widget, "file-set", G_CALLBACK( set_repository ), gource );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 0, 1, 1 );

    widget = gtk_label_new( "Title: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 1, 1, 1 );

    widget = gtk_entry_new();
    gtk_entry_set_text( GTK_ENTRY( widget ), string_get_text( gource->video.title ) );
    g_signal_connect( widget, "focus-out-event", G_CALLBACK( set_title ), gource );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 1, 1, 1 );

    widget = gtk_label_new( "Screen Mode: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 2, 1, 1 );

    widget =
        gtk_combo_box_text_new_with_entry(); // TODO Make a drop down list same of
                                             // https://developer.gnome.org/hig/stable/drop-down-lists.html.en
    char *screen_mode[] = {"Fullscreen",
                           "Windowed",
                           "640x480",
                           "720x480",
                           "1280x720",
                           "1920x1080",
                           "3840x2160",
                           "7680x4320"};
    int length_screen_mode = 8;
    int index_default_screen_mode = 0;
    for( int i = 0; i < length_screen_mode; i++ ) {
        if( !strcmp( screen_mode[i], string_get_text( gource->video.screen_mode ) ) ) {
            index_default_screen_mode = i;
        }
        gtk_combo_box_text_append_text( GTK_COMBO_BOX_TEXT( widget ), screen_mode[i] );
    }
    gtk_combo_box_set_active( GTK_COMBO_BOX( widget ), index_default_screen_mode );
    g_signal_connect( widget, "changed", G_CALLBACK( set_screen_mode ), gource );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 2, 1, 1 );

    widget = gtk_label_new( "Background color: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 3, 1, 1 );

    gdk_rgba_parse( &rgba, string_get_text( gource->video.background_color ) );
    widget = gtk_color_button_new_with_rgba( &rgba );
    gtk_color_button_set_title( GTK_COLOR_BUTTON( widget ), "Choose a color for the background" );
    g_signal_connect( widget, "color-set", G_CALLBACK( set_background_color ), gource );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 3, 1, 1 );

    widget = gtk_label_new( "Camera mode: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 4, 1, 1 );

    widget = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text( GTK_COMBO_BOX_TEXT( widget ), "" );
    char *camera_mode[] = {"Overview", "Track"};
    int length_camera_mode = 2;
    int index_default_camera_mode = 0;
    for( int i = 0; i < length_camera_mode; i++ ) {
        if( !strcmp( camera_mode[i], string_get_text( gource->video.camera_mode ) ) ) {
            index_default_camera_mode = i;
        }
        gtk_combo_box_text_append_text( GTK_COMBO_BOX_TEXT( widget ), camera_mode[i] );
    }
    gtk_combo_box_set_active( GTK_COMBO_BOX( widget ), index_default_camera_mode );
    g_signal_connect( widget, "changed", G_CALLBACK( set_camera_mode ), gource );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 4, 1, 1 );

    return grid;
}
