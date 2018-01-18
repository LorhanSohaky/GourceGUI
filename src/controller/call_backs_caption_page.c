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

#include "call_backs_caption_page.h"
#include "gource.h"
#include "utils.h"

void set_caption_file( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    gchar *caption_file = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
    string_set_text( gource->caption.file, caption_file );

    g_free( caption_file );
}

gboolean set_font_size( GtkWidget *widget, GdkEvent *event, gpointer data ) {
    Gource *gource = (Gource *)data;
    string_sprint( gource->caption.font_size,
                   "%d",
                   (int)gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) );
    return FALSE;
}

gboolean set_duration( GtkWidget *widget, GdkEvent *event, gpointer data ) {
    Gource *gource = (Gource *)data;
    string_sprint(
        gource->caption.duration, "%f", gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) );
    return FALSE;
}

void set_caption_color( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba( GTK_COLOR_CHOOSER( widget ), &rgba );
    string_sprint( gource->caption.color, "%d", rgba_to_hex( rgba.red, rgba.green, rgba.blue ) );
}
