#include <other_page.h>

void save_dialog(GtkWidget *widget, gpointer data);

GtkWidget *init_other_page(GtkWidget *window){
    GtkWidget *grid,*widget;
    GtkListStore *liststore;
    GtkCellRenderer *column;
    GdkRGBA rgba;
    grid=gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid),TRUE);
    gtk_grid_set_row_homogeneous (GTK_GRID(grid),TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(grid),10);



    widget=gtk_label_new("Auto skip seconds: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,0,1,1);

    widget=gtk_spin_button_new_with_range(0,100,1);
    gtk_grid_attach(GTK_GRID(grid),widget,1,0,1,1);

    widget=gtk_label_new("Seconds per day: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,1,1,1);

    widget=gtk_spin_button_new_with_range(0,100,1);
    gtk_grid_attach(GTK_GRID(grid),widget,1,1,1,1);

    widget=gtk_label_new("Date format: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,2,1,1);

    widget=gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid),widget,1,2,1,1);

    widget=gtk_label_new("Users avatar: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,3,1,1);

    widget=gtk_file_chooser_button_new("Select the folder with user avatar",GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    gtk_grid_attach(GTK_GRID(grid),widget,1,3,1,1);

    widget=gtk_button_new_with_label("Output gource at file ");
    g_signal_connect (widget, "clicked", G_CALLBACK (save_dialog),window);
    gtk_grid_attach(GTK_GRID(grid),widget,0,4,2,1);

    return grid;
}

void save_dialog(GtkWidget *widget, gpointer data){
    GtkFileFilter *filter;
    GtkWidget *window=(GtkWidget*)data;
    filter =gtk_file_filter_new();
    gtk_file_filter_add_pattern (filter, "*.MP4");
    gtk_file_filter_add_pattern (filter, "*.mp4");
    gtk_file_filter_set_name (filter,".mp4");
    GtkWidget *dialog=gtk_file_chooser_dialog_new ("Choose a file to save a video of Gource",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_SAVE,"Save",GTK_RESPONSE_ACCEPT,"Cancel",GTK_RESPONSE_CANCEL,NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog),TRUE);
    gtk_file_chooser_add_filter (GTK_FILE_CHOOSER(dialog),filter);
    gtk_widget_show_all(dialog);
    gint res=gtk_dialog_run(GTK_DIALOG(dialog));
    if(res==GTK_RESPONSE_ACCEPT){
        printf("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    }
    gtk_widget_destroy(dialog);
}
