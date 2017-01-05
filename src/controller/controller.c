#include <controller.h>
#include <utils.h>
#include <gource.h>
#include <string.h>
#include <stdlib.h>

_gource gource_settings;

void set_font_name(GtkFontChooser *button);
void set_font_size(GtkFontChooser *button);

void free_memory(_gource *gource);

int controller (int argc, char *argv[]){
    GtkApplication *app;
    int status=0;

    init__gource(&gource_settings);
    if(is__gource_OK(&gource_settings)){
        app = gtk_application_new ("org.gourcegui", G_APPLICATION_FLAGS_NONE);
        g_signal_connect (app, "activate", G_CALLBACK (activate),NULL);
        status = g_application_run (G_APPLICATION (app), argc, argv);
        print_gource(&gource_settings);
        g_object_unref (app);
        free_memory(&gource_settings);
    }else{
        fprintf(stderr, "Failed to allocate memory.\n");
    }
    return status;
}

//CALLBACKs of video_page

void set_log_file(GtkWidget *widget, gpointer data){
    gource_settings.video.log_file=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
}

gboolean set_title(GtkWidget *widget, gpointer data){
    //gource_settings.video.title=gtk_entry_get_text (GTK_ENTRY(widget));
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

//CALLBACKs other_page

gboolean set_auto_skip(GtkWidget *widget, gpointer data){
    gource_settings.other.auto_skip_seconds=gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
    return FALSE;
}

gboolean set_seconds_per_day(GtkWidget *widget, gpointer data){
    gource_settings.other.seconds_per_day=gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
    return FALSE;
}

gboolean set_date_format(GtkWidget *widget, gpointer data){
    //gource_settings.other.date_format=gtk_entry_get_text(GTK_ENTRY(widget));
    return FALSE;
}

void set_avatar_folder(GtkWidget *widget, gpointer data){
    gource_settings.other.folder_with_users_avatar_icon=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
}

void set_output_gource(GtkWidget *widget){
    gource_settings.other.output_gorce=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));
}



void set_font_name(GtkFontChooser *button){
    gource_settings.subtitle.font_name=gtk_font_chooser_get_font(button);
}

void set_font_size(GtkFontChooser *button){
    gource_settings.subtitle.font_size=gtk_font_chooser_get_font_size(button)/1000;
}


void free_memory(_gource *gource){
    free(gource->video.title);
    free(gource->other.date_format);
}
