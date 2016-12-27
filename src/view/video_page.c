#include <video_page.h>
#include  <controller.h>

GtkWidget *init_video_page(GtkWidget *window){
    GtkWidget *grid,*widget;
    GtkListStore *liststore;
    GtkCellRenderer *column;
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
    g_signal_connect (widget, "key-release-event", G_CALLBACK (set_title),NULL);
    gtk_grid_attach(GTK_GRID(grid),widget,1,1,1,1);

    widget=gtk_label_new("Screen Mode: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,2,1,1);

    liststore = gtk_list_store_new(1, G_TYPE_STRING);
    widget = gtk_combo_box_new_with_model(GTK_TREE_MODEL(liststore));//Make a drop down list same of https://developer.gnome.org/hig/stable/drop-down-lists.html.en
    gtk_list_store_insert_with_values(liststore, NULL, -1,0, "fullscreen",-1);
    gtk_list_store_insert_with_values(liststore, NULL, -1,0, "windowed",-1);
    gtk_list_store_insert_with_values(liststore, NULL, -1,0, "640 x 480",-1);
    gtk_list_store_insert_with_values(liststore, NULL, -1,0, "720 x 480",-1);
    gtk_list_store_insert_with_values(liststore, NULL, -1,0, "1280 x 720",-1);
    gtk_list_store_insert_with_values(liststore, NULL, -1,0, "1920 x 1080",-1);
    gtk_list_store_insert_with_values(liststore, NULL, -1,0, "3840 x 2160",-1);
    gtk_list_store_insert_with_values(liststore, NULL, -1,0, "7680 x 4320",-1);
    column = gtk_cell_renderer_text_new();
    gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(widget), column, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(widget), column,"text", 0,NULL);
    g_signal_connect (widget, "changed", G_CALLBACK (set_screen_mode),NULL);
    gtk_grid_attach(GTK_GRID(grid),widget,1,2,1,1);
    g_object_unref(liststore);

    widget=gtk_label_new("Background color: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,3,1,1);

    gdk_rgba_parse(&rgba,"#555555");//Set default color
    widget=gtk_color_button_new_with_rgba(&rgba);
    gtk_color_button_set_title (GTK_COLOR_BUTTON(widget),"Choose a color for the background");
    g_signal_connect (widget, "color-set", G_CALLBACK (set_background_color),NULL);
    gtk_grid_attach(GTK_GRID(grid),widget,1,3,1,1);

    widget=gtk_label_new("Camera mode: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,4,1,1);

    liststore = gtk_list_store_new(1, G_TYPE_STRING);
    widget = gtk_combo_box_new_with_model(GTK_TREE_MODEL(liststore));
    gtk_list_store_insert_with_values(liststore, NULL, -1,0, "Overview",-1);
    gtk_list_store_insert_with_values(liststore, NULL, -1,0, "Track",-1);
    column = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(widget), column, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(widget), column,"text", 0,NULL);
    gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
    g_signal_connect (widget, "changed", G_CALLBACK (set_camera_mode),NULL);
    gtk_grid_attach(GTK_GRID(grid),widget,1,4,1,1);
    g_object_unref(liststore);

    return grid;
}
