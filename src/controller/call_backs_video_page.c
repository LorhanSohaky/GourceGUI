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

#include "call_backs_video_page.h"
#include "gource.h"
#include "utils.h"

void set_repository( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    gchar *repository = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
    string_set_text( gource->video.repository, repository );

    g_free( repository );
}

gboolean set_title( GtkWidget *widget, GdkEvent *event, gpointer data ) {
    Gource *gource = (Gource *)data;
    string_set_text( gource->video.title, gtk_entry_get_text( GTK_ENTRY( widget ) ) );

    return FALSE;
}

void set_screen_mode( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    gchar *screen_mode = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT( widget ) );
    string_set_text( gource->video.screen_mode, screen_mode );

    g_free( screen_mode );
}

void set_background_color( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba( GTK_COLOR_CHOOSER( widget ), &rgba );
    string_set_text( gource->video.background_color,
                     rgba_to_hex( rgba.red, rgba.green, rgba.blue ) );
}

void set_camera_mode( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    gchar *camera_mode = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT( widget ) );
    string_set_text( gource->video.camera_mode, camera_mode );

    g_free( camera_mode );
}
