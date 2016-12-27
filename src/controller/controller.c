#include <controller.h>

int controller (int argc, char *argv[]){
    _gource gource_settings;
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gourcegui", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate),NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}
