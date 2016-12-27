#include <controller.h>
#include <utils.h>

_gource gource_settings;

void set_font_name(GtkFontChooser *button);
void set_font_size(GtkFontChooser *button);

int controller (int argc, char *argv[]){
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gourcegui", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate),NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}

//CALLBACKs of video_page

void set_log_file(GtkWidget *widget, gpointer data){
    gource_settings.video.log_file=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
}

gboolean set_title(GtkWidget *widget, gpointer data){
    gource_settings.video.title=gtk_entry_get_text (GTK_ENTRY(widget));
    return FALSE;
}

void set_screen_mode(GtkWidget *widget, gpointer data){
    //TODO Implement
}

void set_background_color(GtkWidget *widget, gpointer data){
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(widget),&rgba);
    gource_settings.video.background_color=rgba_to_hex(rgba.red,rgba.green,rgba.blue);
}

void set_camera_mode(GtkWidget *widget, gpointer data){
    //TODO Implement
}

//CALLBACKs of subtitle_page

void set_subtitle_file(GtkWidget *widget, gpointer data){
    gource_settings.subtitle.subtitle_file=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
}

void set_font(GtkWidget *widget, gpointer data){
    set_font_name(GTK_FONT_CHOOSER(widget));
    set_font_size(GTK_FONT_CHOOSER(widget));
}

gboolean set_duration(GtkWidget *widget, gpointer data){
    gource_settings.subtitle.duration=gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
    return FALSE;
}

void set_subtitle_color(GtkWidget *widget, gpointer data){
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(widget),&rgba);
    gource_settings.subtitle.color=rgba_to_hex(rgba.red,rgba.green,rgba.blue);
}







void set_font_name(GtkFontChooser *button){
    gource_settings.subtitle.font_name=gtk_font_chooser_get_font(button);
}

void set_font_size(GtkFontChooser *button){
    gource_settings.subtitle.font_size=gtk_font_chooser_get_font_size(button)/1000;
}
