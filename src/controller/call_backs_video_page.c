#include "call_backs_video_page.h"

void set_repository( GtkWidget *widget, gpointer data ) {
    gource_settings.video.repository = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
}

gboolean set_title( GtkWidget *widget, gpointer data ) {
    if( !string_copy_char_array( gource_settings.video.title,
                                 gtk_entry_get_text( GTK_ENTRY( widget ) ) ) ) {
        free_memory( &gource_settings, true );
    }
    return FALSE;
}

void set_screen_mode( GtkWidget *widget, gpointer data ) {
    gource_settings.video.screen_mode =
        gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT( widget ) );
}

void set_background_color( GtkWidget *widget, gpointer data ) {
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba( GTK_COLOR_CHOOSER( widget ), &rgba );
    if( !string_copy_char_array( gource_settings.video.background_color,
                                 rgba_to_hex( rgba.red, rgba.green, rgba.blue ) ) ) {
        free_memory( &gource_settings, true );
    }
}

void set_camera_mode( GtkWidget *widget, gpointer data ) {
    gource_settings.video.camera_mode =
        gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT( widget ) );
}
