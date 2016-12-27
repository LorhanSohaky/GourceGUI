#include <controller.h>

_gource gource_settings;

int controller (int argc, char *argv[]){
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gourcegui", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate),NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}

void set_log_file(GtkWidget *widget, gpointer data){
    gource_settings.video.log_file=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
}

void set_title(GtkWidget *widget, gpointer data){
    gource_settings.video.title=gtk_entry_get_text (GTK_ENTRY(widget));
}

void set_screen_mode(GtkWidget *widget, gpointer data){
    //TODO Implement
}

void set_background_color(GtkWidget *widget, gpointer data){
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(widget),&rgba);
    gource_settings.video.background_color=gdk_rgba_to_string(&rgba);
    printf("%s\n",gource_settings.video.background_color);
}

void set_camera_mode(GtkWidget *widget, gpointer data){
    //TODO Implement
}
