#include <gource.h>
#include <stdio.h>
#include <stdlib.h>

#define ENTRY_LENGTH 11 //10 + 1 for put '\0'

void init__video(_gource *gource);
void init__subtitle(_gource *gource);
void init__other(_gource *gource);

void init_entry(char **destination);
bool is_malloc_OK(_gource *gource);

void init__gource(_gource *gource){
    init__video(gource);
    init__subtitle(gource);
    init__other(gource);
}

void init__video(_gource *gource){
    gource->video.log_file=NULL;
    init_entry(&gource->video.title);
    gource->video.screen_mode=NULL;
    gource->video.background_color=NULL;
    gource->video.camera_mode=NULL;
}

void init__subtitle(_gource *gource){
    gource->subtitle.subtitle_file=NULL;
    gource->subtitle.font_name=NULL;
    gource->subtitle.font_size=-1;
    gource->subtitle.duration=-1;
    gource->subtitle.color=NULL;
}

void init__other(_gource *gource){
    gource->other.auto_skip_seconds=-1;
    gource->other.seconds_per_day=-1;
    init_entry(&gource->other.date_format);
    gource->other.folder_with_users_avatar_icon=NULL;
    gource->other.output_gorce=NULL;
}

void init_entry(char **destination){
    *destination = (char *) malloc(ENTRY_LENGTH* sizeof(char));
    if(*destination!=NULL){
        for(int i=0;i<ENTRY_LENGTH-1;i++){
            (*destination)[i]=' ';
        }
        (*destination)[ENTRY_LENGTH-1]='\0';
    }
}

bool is__gource_OK(_gource *gource){
    return is_malloc_OK(gource);
}

bool is_malloc_OK(_gource *gource){
    if(gource->video.title==NULL || gource->other.date_format==NULL){
        return false;
    }else{
        return true;
    }
}

void print_gource(_gource *gource){
    printf("Video:\n");
    printf("\tLog file - %s\n", gource->video.log_file);
    printf("\tTitle - %s\n", gource->video.title);
    printf("\tScreen Mode - %s\n", gource->video.screen_mode);
    printf("\tBackground color - %s\n", gource->video.background_color);
    printf("\tCamer mode - %s\n", gource->video.camera_mode);

    printf("Subtitle:\n");
    printf("\tSubtitle file - %s\n", gource->subtitle.subtitle_file);
    printf("\tFont name - %s\n", gource->subtitle.font_name);
    printf("\tFont size - %d\n", gource->subtitle.font_size);
    printf("\tDuration - %d\n", gource->subtitle.duration);
    printf("\tColor - %s\n", gource->subtitle.color);

    printf("Other:\n");
    printf("\tAuto Skip seconds - %d\n", gource->other.auto_skip_seconds);
    printf("\tSeconds per day - %d\n", gource->other.seconds_per_day);
    printf("\tDate format - %s\n", gource->other.date_format);
    printf("\tFolder with users avatar icon - %s\n", gource->other.folder_with_users_avatar_icon);
    printf("\tOutput gource - %s\n", gource->other.output_gorce);

}
