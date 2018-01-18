/*
 The MIT License (MIT)
 Copyright (c) 2018 Lorhan Sohaky
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

#include "call_backs_other_page.h"
#include "gource.h"
#include "utils.h"
#include <stdbool.h>
#include <string.h>

// TODO static bool append_extension_when_necessary( GtkWidget *widget );

gboolean set_auto_skip( GtkWidget *widget, GdkEvent *event, gpointer data ) {
    Gource *gource = (Gource *)data;
    string_sprint( gource->other.auto_skip_seconds,
                   "%f",
                   gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) );
    return FALSE;
}

gboolean set_seconds_per_day( GtkWidget *widget, GdkEvent *event, gpointer data ) {
    Gource *gource = (Gource *)data;
    string_sprint( gource->other.seconds_per_day,
                   "%f",
                   gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) );
    return FALSE;
}

gboolean set_date_format( GtkWidget *widget, GdkEvent *event, gpointer data ) {
    Gource *gource = (Gource *)data;
    string_set_text( gource->other.date_format, gtk_entry_get_text( GTK_ENTRY( widget ) ) );
    return FALSE;
}

void set_avatar_folder( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    gchar *folder_with_users_avatar_icon =
        gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
    string_set_text( gource->other.folder_with_users_avatar_icon, folder_with_users_avatar_icon );

    g_free( folder_with_users_avatar_icon );
}

/*TODO void set_output_gource( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    if( append_extension_when_necessary( widget ) ) {
        gchar *output_gorce = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
        string_set_text( gource->other.output_gorce, output_gorce );

        g_free( output_gorce );
    }
}

static bool append_extension_when_necessary( GtkWidget *widget ) {
    char *tmp = gtk_file_chooser_get_current_name( GTK_FILE_CHOOSER( widget ) );
    tmp = &tmp[strlen( tmp ) - strlen( ".MP4" )];
    string_tolower( tmp );
    if( strcmp( tmp, ".mp4" ) != 0 ) {
        tmp = (char *)malloc(
            sizeof( char ) *
            ( strlen( gtk_file_chooser_get_current_name( GTK_FILE_CHOOSER( widget ) ) ) +
              strlen( ".mp4" ) ) );
        if( tmp != NULL ) {
            sprintf(
                tmp, "%s.mp4", gtk_file_chooser_get_current_name( GTK_FILE_CHOOSER( widget ) ) );
            gtk_file_chooser_set_current_name( GTK_FILE_CHOOSER( widget ), tmp );
            free( tmp );
        } else {
            return false;
        }
    }
    return true;
}
*/
