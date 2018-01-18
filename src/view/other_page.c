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

#include "other_page.h"
#include "call_backs_other_page.h"

// TODO void save_dialog( GtkWidget *widget, gpointer data );

GtkWidget *init_other_page( GtkWidget *window, Gource *gource ) {
    GtkWidget *grid, *widget;
    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous( GTK_GRID( grid ), TRUE );
    gtk_grid_set_row_homogeneous( GTK_GRID( grid ), TRUE );
    gtk_container_set_border_width( GTK_CONTAINER( grid ), 10 );

    widget = gtk_label_new( "Auto skip seconds: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 0, 1, 1 );

    widget = gtk_spin_button_new_with_range( 0, 100, 0.1 );
    gtk_spin_button_set_value( GTK_SPIN_BUTTON( widget ),
                               atof( string_get_text( gource->other.auto_skip_seconds ) ) );
    g_signal_connect( widget, "focus-out-event", G_CALLBACK( set_auto_skip ), gource );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 0, 1, 1 );

    widget = gtk_label_new( "Seconds per day: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 1, 1, 1 );

    widget = gtk_spin_button_new_with_range( 0, 100, 0.1 );
    gtk_spin_button_set_value( GTK_SPIN_BUTTON( widget ),
                               atof( string_get_text( gource->other.seconds_per_day ) ) );
    g_signal_connect( widget, "focus-out-event", G_CALLBACK( set_seconds_per_day ), gource );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 1, 1, 1 );

    widget = gtk_label_new( "Date format: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 2, 1, 1 );

    widget = gtk_entry_new();
    gtk_entry_set_text( GTK_ENTRY( widget ), string_get_text( gource->other.date_format ) );
    g_signal_connect( widget, "focus-out-event", G_CALLBACK( set_date_format ), gource );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 2, 1, 1 );

    widget = gtk_label_new( "Users avatar: " );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 3, 1, 1 );

    widget = gtk_file_chooser_button_new( "Select the folder with user avatar",
                                          GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER );
    gtk_file_chooser_set_filename( GTK_FILE_CHOOSER( widget ),
                                   string_get_text( gource->other.folder_with_users_avatar_icon ) );
    g_signal_connect( widget, "file-set", G_CALLBACK( set_avatar_folder ), gource );
    gtk_grid_attach( GTK_GRID( grid ), widget, 1, 3, 1, 1 );

    /*TODO widget = gtk_button_new_with_label( "Output gource at file " );
    g_signal_connect( widget, "clicked", G_CALLBACK( save_dialog ), gource );
    gtk_grid_attach( GTK_GRID( grid ), widget, 0, 4, 2, 1 );*/

    return grid;
}

/*TODO void save_dialog( GtkWidget *widget, gpointer data ) {
    GtkFileFilter *filter;
    Gource *gource = (Gource *)data;
    filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern( filter, "*.MP4" );
    gtk_file_filter_add_pattern( filter, "*.mp4" );
    gtk_file_filter_set_name( filter, ".mp4" );
    GtkWidget *dialog = gtk_file_chooser_dialog_new( "Choose a file to save a video of Gource",
                                                     NULL, //GTK_WINDOW(window)
                                                     GTK_FILE_CHOOSER_ACTION_SAVE,
                                                     "Save",
                                                     GTK_RESPONSE_ACCEPT,
                                                     "Cancel",
                                                     GTK_RESPONSE_CANCEL,
                                                     NULL );
    gtk_file_chooser_set_current_name( GTK_FILE_CHOOSER( dialog ), "Untitled document.mp4" );
    gtk_file_chooser_set_do_overwrite_confirmation( GTK_FILE_CHOOSER( dialog ), TRUE );
    gtk_file_chooser_add_filter( GTK_FILE_CHOOSER( dialog ), filter );
    gtk_widget_show_all( dialog );
    gint res = gtk_dialog_run( GTK_DIALOG( dialog ) );
    if( res == GTK_RESPONSE_ACCEPT ) {
        set_output_gource( dialog, gource );
    }
    gtk_widget_destroy( dialog );
}
*/
