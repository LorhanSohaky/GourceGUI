#include "call_backs_caption_page.h"
#include "gource.h"
#include "utils.h"

void set_caption_file( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    gchar *caption_file = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
    string_set_text( gource->caption.file, caption_file );

    g_free( caption_file );
}

gboolean set_font_size( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    string_sprint(
        gource->caption.font_size, "%d", gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) );
    return FALSE;
}

gboolean set_duration( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    string_sprint(
        gource->caption.duration, "%d", gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) );
    return FALSE;
}

void set_caption_color( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba( GTK_COLOR_CHOOSER( widget ), &rgba );
    string_sprint( gource->caption.color, "%d", rgba_to_hex( rgba.red, rgba.green, rgba.blue ) );
}
