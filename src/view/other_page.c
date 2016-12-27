#include <other_page.h>

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
    gtk_grid_attach(GTK_GRID(grid),widget,0,4,2,1);

    return grid;
}
