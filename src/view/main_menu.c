#include <main_menu.h>

void activate (GtkApplication* app,gpointer user_data){
  GtkWidget *window,*grid,*button,*notebook;
  GdkRGBA rgba;
  //window properties
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "GourceGUI");
  gtk_window_set_default_size (GTK_WINDOW (window), 358, 255);
  gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(window),10);

  //button properties
  button=gtk_button_new_with_label("Execute");//TODO change background color:#5cb85c border:#4cae4c
  gtk_widget_set_valign(button,GTK_ALIGN_END);//TODO on hover background color:#449d44 border:#398439

  //notebook properties
  notebook=add_notebook(window);
  gtk_widget_set_vexpand (notebook,TRUE);
  gtk_widget_set_valign(notebook,GTK_ALIGN_FILL);

  //grid properties
  grid=gtk_grid_new();
  gtk_grid_set_column_homogeneous(GTK_GRID(grid),TRUE);
  gtk_container_add(GTK_CONTAINER(window),grid);
  gtk_grid_attach(GTK_GRID(grid),notebook,0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid),button,0,1,1,1);

  gtk_widget_show_all (window);
}

GtkWidget *add_notebook(GtkWidget *window){
    GtkWidget *label,*notebook,*page;
    notebook=gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook),GTK_POS_TOP);
    add_notebook_tab(notebook,"Video",init_video_page(window));
    add_notebook_tab(notebook,"Subtitle",init_subtitle_page(window));
    add_notebook_tab(notebook,"Other settings",init_other_page(window));
    return notebook;
}

void add_notebook_tab(GtkWidget *notebook, char *label, GtkWidget *page){
    GtkWidget *g_label;

    g_label=gtk_label_new(label);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),page,g_label);

}
