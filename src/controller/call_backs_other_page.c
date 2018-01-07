#include "call_backs_other_page.h"

gboolean set_auto_skip( GtkWidget *widget, gpointer data ) {
    if( !string_sprint( gource_settings.other.auto_skip_seconds,
                        "%d",
                        gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) ) ) {
        free_memory( &gource_settings, true );
    }
    return FALSE;
}

gboolean set_seconds_per_day( GtkWidget *widget, gpointer data ) {
    if( !string_sprint( gource_settings.other.seconds_per_day,
                        "%d",
                        gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) ) ) {
        free_memory( &gource_settings, true );
    }
    return FALSE;
}

gboolean set_date_format( GtkWidget *widget, gpointer data ) {
    if( !string_copy_char_array( gource_settings.other.date_format,
                                 gtk_entry_get_text( GTK_ENTRY( widget ) ) ) ) {
        free_memory( &gource_settings, true );
    }
    return FALSE;
}

void set_avatar_folder( GtkWidget *widget, gpointer data ) {
    gource_settings.other.folder_with_users_avatar_icon =
        gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
}

void set_output_gource( GtkWidget *widget ) {
    if( append_extension_when_necessary( widget ) ) {
        gource_settings.other.output_gorce =
            gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
    } else {
        free_memory( &gource_settings, true );
    }
}
