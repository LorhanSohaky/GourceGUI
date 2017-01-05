#include <video_page.h>
#include <controller.h>
#include <gource.h>

GtkWidget *init_video_page(GtkWidget *window){
    GtkWidget *grid,*widget;
    GdkRGBA rgba;
    grid=gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid),TRUE);
    gtk_grid_set_row_homogeneous (GTK_GRID(grid),TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(grid),10);

    widget=gtk_label_new("LOG file: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,0,1,1);

    widget=gtk_file_chooser_button_new ("Choose a LOG file",GTK_FILE_CHOOSER_ACTION_OPEN);
    g_signal_connect (widget, "file-set", G_CALLBACK (set_log_file),NULL);
    gtk_grid_attach(GTK_GRID(grid),widget,1,0,1,1);

    widget=gtk_label_new("Title: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,1,1,1);

    widget=gtk_entry_new();
    g_signal_connect (widget, "focus-out-event", G_CALLBACK (set_title),NULL);
    gtk_grid_attach(GTK_GRID(grid),widget,1,1,1,1);

    widget=gtk_label_new("Screen Mode: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,2,1,1);

    widget=gtk_combo_box_text_new_with_entry();//TODO Make a drop down list same of https://developer.gnome.org/hig/stable/drop-down-lists.html.en
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "fullscreen");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "windowed");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "640 x 480");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "720 x 480");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "1280 x 720");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "1920 x 1080");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "3840 x 2160");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "7680 x 4320");
    g_signal_connect (widget, "changed", G_CALLBACK (set_screen_mode),NULL);
    gtk_grid_attach(GTK_GRID(grid),widget,1,2,1,1);

    widget=gtk_label_new("Background color: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,3,1,1);

    gdk_rgba_parse(&rgba,DEFAULT_BACKGROUND_COLOR);
    widget=gtk_color_button_new_with_rgba(&rgba);
    gtk_color_button_set_title (GTK_COLOR_BUTTON(widget),"Choose a color for the background");
    g_signal_connect (widget, "color-set", G_CALLBACK (set_background_color),NULL);
    gtk_grid_attach(GTK_GRID(grid),widget,1,3,1,1);

    widget=gtk_label_new("Camera mode: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,4,1,1);

    widget = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), " ");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "Overview");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "Track");
    g_signal_connect (widget, "changed", G_CALLBACK (set_camera_mode),NULL);
    gtk_grid_attach(GTK_GRID(grid),widget,1,4,1,1);

    return grid;
}
