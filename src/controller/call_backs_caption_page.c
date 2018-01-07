#include "call_backs_caption_page.h"

void set_caption_file( GtkWidget *widget, gpointer data ) {
    gource_settings.caption.file = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
}

gboolean set_font_size( GtkWidget *widget, gpointer data ) {
    if( !copy_number_to_string( gource_settings.caption.font_size,
                                gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) ) ) {
        free_memory( &gource_settings, true );
    }
    return FALSE;
}

gboolean set_duration( GtkWidget *widget, gpointer data ) {
    if( !copy_number_to_string( gource_settings.caption.duration,
                                gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) ) ) {
        free_memory( &gource_settings, true );
    }
    return FALSE;
}

void set_caption_color( GtkWidget *widget, gpointer data ) {
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba( GTK_COLOR_CHOOSER( widget ), &rgba );
    if( !string_copy_char_array( gource_settings.caption.color,
                                 rgba_to_hex( rgba.red, rgba.green, rgba.blue ) ) ) {
        free_memory( &gource_settings, true );
    }
}
