#include <controller.h>
#include <process_creator.h>
#include <utils.h>
#include <gource.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

_gource gource_settings;

#define ARGS_TO_OUTPUT_GOURCE 25

void set_font_name(GtkFontChooser *button);
void set_font_size(GtkFontChooser *button);
void remove_size_of_font_name(char *font_name);

bool append_extension_when_necessary(GtkWidget *widget);
void string_tolower(char *string);

void add_to_argv_valid_field(_gource *gource,char **argv,int *size);
void add_to_argv(char **argv,int *size,char *option, char *value);

void prepare_color(char *color);
void prepare_screen_mode(char **screen_mode);

void copy_number_to_string(_string *string, int value);

void free_memory(_gource *gource);

int controller (int argc, char *argv[]){
    GtkApplication *app;
    int status=0;
    init__gource(&gource_settings);
    if(is__gource_OK(&gource_settings)){
        app = gtk_application_new ("org.gourcegui", G_APPLICATION_FLAGS_NONE);
        g_signal_connect (app, "activate", G_CALLBACK (activate),NULL);
        status = g_application_run (G_APPLICATION (app), argc, argv);
        g_object_unref (app);
        free_memory(&gource_settings);
    }else{
        fprintf(stderr, "Failed to allocate memory.\n");
    }
    return status;
}

//CALLBACKs of main_menu
void execute(GtkWidget *widget, gpointer data){
    int number_of_fields=0;
    char **argv;
    argv=(char **)malloc(sizeof(char **)*(2*NUMBER_OF_FIELDS+1+ARGS_TO_OUTPUT_GOURCE));
    if(argv!=NULL){
        add_to_argv_valid_field( &gource_settings, argv, &number_of_fields);
        call_prog("/usr/bin/gource",argv,number_of_fields);
    }else{
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
    print_gource(&gource_settings);

}

//CALLBACKs of video_page

void set_log_file(GtkWidget *widget, gpointer data){
    gource_settings.video.log_file=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
}

gboolean set_title(GtkWidget *widget, gpointer data){
    copy_string(&gource_settings.video.title,gtk_entry_get_text (GTK_ENTRY(widget)));
    if(gource_settings.video.title.size==0){
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
    return FALSE;
}

void set_screen_mode(GtkWidget *widget, gpointer data){
    gource_settings.video.screen_mode=gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widget));
}

void set_background_color(GtkWidget *widget, gpointer data){
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(widget),&rgba);
    copy_string(&gource_settings.video.background_color,rgba_to_hex(rgba.red,rgba.green,rgba.blue));
    if(gource_settings.video.background_color.size==0){
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
}

void set_camera_mode(GtkWidget *widget, gpointer data){
    gource_settings.video.camera_mode=gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widget));
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
    copy_number_to_string(&gource_settings.subtitle.duration,gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget)));
    if(gource_settings.subtitle.duration.size==0){
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
    return FALSE;
}

void set_subtitle_color(GtkWidget *widget, gpointer data){
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(widget),&rgba);
    copy_string(&gource_settings.subtitle.color,rgba_to_hex(rgba.red,rgba.green,rgba.blue));
    if(gource_settings.subtitle.color.size==0){
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
}

//CALLBACKs other_page

gboolean set_auto_skip(GtkWidget *widget, gpointer data){
    copy_number_to_string(&gource_settings.other.auto_skip_seconds,gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget)));
    if(gource_settings.other.auto_skip_seconds.size==0){
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
    return FALSE;
}

gboolean set_seconds_per_day(GtkWidget *widget, gpointer data){
    copy_number_to_string(&gource_settings.other.seconds_per_day,gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget)));
    if(gource_settings.other.seconds_per_day.size==0){
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
    return FALSE;
}

gboolean set_date_format(GtkWidget *widget, gpointer data){
    copy_string(&gource_settings.other.date_format,gtk_entry_get_text (GTK_ENTRY(widget)));
    if(gource_settings.other.date_format.size==0){
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
    return FALSE;
}

void set_avatar_folder(GtkWidget *widget, gpointer data){
    gource_settings.other.folder_with_users_avatar_icon=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
}

void set_output_gource(GtkWidget *widget){
    if(append_extension_when_necessary(widget)){
        gource_settings.other.output_gorce=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));
    }else{
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
}



void set_font_name(GtkFontChooser *button){
    gource_settings.subtitle.font_name=gtk_font_chooser_get_font(button);
    remove_size_of_font_name(gource_settings.subtitle.font_name);
}

void set_font_size(GtkFontChooser *button){
    copy_number_to_string(&gource_settings.subtitle.font_size,gtk_font_chooser_get_font_size(button)/1000);
}

void remove_size_of_font_name(char *font_name){
    char *last_space=strrchr(font_name,' ');
    font_name[last_space-font_name]='\0';
}


bool append_extension_when_necessary(GtkWidget *widget){
    char *tmp=gtk_file_chooser_get_current_name (GTK_FILE_CHOOSER(widget));
    tmp=&tmp[strlen(tmp)-strlen(".MP4")];
    string_tolower(tmp);
    if (strcmp(tmp,".mp4")!=0) {
        tmp=(char *) malloc(sizeof(char)*(strlen(gtk_file_chooser_get_current_name (GTK_FILE_CHOOSER(widget)))+strlen(".mp4")));
        if(tmp!=NULL){
            sprintf(tmp,"%s.mp4", gtk_file_chooser_get_current_name (GTK_FILE_CHOOSER(widget)));
            gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER(widget),tmp);
            free(tmp);
        }else{
            return false;
        }
    }
    return true;
}

void string_tolower(char *string){
    for(int i=0;i<strlen(string);i++){
        string[i]=tolower(string[i]);
    }
}

void add_to_argv_valid_field(_gource *gource,char **argv,int *size){
    char *tmp;
    prepare_color(gource->video.background_color.value);
    prepare_color(gource->subtitle.color.value);
    if(gource->video.log_file!=NULL){
        add_to_argv(argv,size,NULL,gource->video.log_file);
    }

    if(strcmp(gource->video.title.value, " ")!=0){// space=default value
        add_to_argv(argv,size,"--title",gource->video.title.value);
    }

    if(gource->video.screen_mode!=NULL){
        if(strcmp(gource->video.screen_mode,"Fullscreen")==0){
            add_to_argv(argv,size,"--fullscreen",NULL);
        }else if(strcmp(gource->video.screen_mode,"Windowed")==0){
            add_to_argv(argv,size,"--windowed",NULL);
        }else{
            prepare_screen_mode(&gource->video.screen_mode);
            add_to_argv(argv,size,NULL,gource->video.screen_mode);
        }
    }

    if(gource->video.camera_mode!=NULL){
        if(strcmp(gource->video.camera_mode,"Overview")==0){
            add_to_argv(argv,size,"--camera-mode","overview");
        }else if(strcmp(gource->video.camera_mode,"Track")==0){
            add_to_argv(argv,size,"--camera-mode","track");
        }
    }

    if(gource->subtitle.subtitle_file!=NULL){
        add_to_argv(argv,size,"--caption-file",gource->subtitle.subtitle_file);
    }

    if(atoi(gource->subtitle.font_size.value)!=0){
        add_to_argv(argv,size,"--font-size",gource->subtitle.font_size.value);
    }

    add_to_argv(argv,size,"--caption-duration",gource->subtitle.duration.value);

    add_to_argv(argv,size,"--caption-colour",gource->subtitle.color.value);

    if(atoi(gource->other.auto_skip_seconds.value)!=0){
        add_to_argv(argv,size,"--auto-skip-seconds",gource->other.auto_skip_seconds.value);
    }

    if(atoi(gource->other.seconds_per_day.value)!=0){
        add_to_argv(argv,size,"--seconds-per-day",gource->other.seconds_per_day.value);
    }

    if(strcmp(gource->other.date_format.value," ")!=0){
        add_to_argv(argv,size,"--date-format",gource->other.date_format.value);
    }

    if(gource->other.folder_with_users_avatar_icon!=NULL){
        add_to_argv(argv,size,"--user-image-dir",gource->other.folder_with_users_avatar_icon);
    }

    if(gource->other.output_gorce!=NULL){
        //TODO To Implement
        /*add_to_argv(argv,size,"-o","-");
        add_to_argv(argv,size,"|","/usr/bin/ffmpeg");
        add_to_argv(argv,size,"-y","-r");
        add_to_argv(argv,size,"60","-f");
        add_to_argv(argv,size,"image2pipe","-vcodec");
        add_to_argv(argv,size,"ppm","-i");
        add_to_argv(argv,size,"-","-vcodec");
        add_to_argv(argv,size,"libx264","-preset");
        add_to_argv(argv,size,"ultrafast","-pix_fmt");
        add_to_argv(argv,size,"yuv420p","-crf");
        add_to_argv(argv,size,"1","-threads");
        add_to_argv(argv,size,"0","-bf");
        add_to_argv(argv,size,"0",gource->other.output_gorce);*/
    }
    argv[*size]=NULL;
}

void add_to_argv(char **argv,int *size,char *option, char *value){
    if(option!=NULL){
        argv[*size]=option;
        (*size)++;
    }
    if(value!=NULL){
        argv[*size]=value;
        (*size)++;
    }
}

void prepare_color(char *color){//Remove # from string
    if(color[0]=='#'){
        strcpy(color,&color[1]);
    }
}

void prepare_screen_mode(char **screen_mode){
    char *tmp=g_try_malloc(strlen(*screen_mode)+2);
    if(tmp!=NULL){
        sprintf(tmp,"-%s",*screen_mode);
        g_free(*screen_mode);
        *screen_mode=tmp;
    }
}

void copy_number_to_string(_string *string, int value){
    if(length_of_int(value)<string->size){
        sprintf(string->value,"%d",value);
    }else{
        char *tmp=(char *)realloc(string->value,length_of_int(value)+string->size+1);
        if(tmp!=NULL){
            string->size=length_of_int(value)+string->size+1;
            string->value=tmp;
            sprintf(string->value,"%d",value);
        }else{
            string->size=0;
        }
    }
}


void free_memory(_gource *gource){
    if(gource->video.title.value!=NULL){
        free(gource->video.title.value);
    }

    if(gource->video.background_color.value!=NULL){
        free(gource->video.background_color.value);
    }

    if(gource->subtitle.color.value!=NULL){
        free(gource->subtitle.color.value);
    }

    if(gource->other.date_format.value!=NULL){
        free(gource->other.date_format.value);
    }
}
