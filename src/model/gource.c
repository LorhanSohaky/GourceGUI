#include <gource.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

#define STRING_DEFAULT_LENGTH 8 //7 + 1 for put '\0'

void init__video(_gource *gource);
void init__subtitle(_gource *gource);
void init__other(_gource *gource);

void init__string(_string *destination, const char *initial_value);
bool is_malloc_OK(_gource *gource);

void init__gource(_gource *gource){
    init__video(gource);
    init__subtitle(gource);
    init__other(gource);
}

void init__video(_gource *gource){
    gource->video.log_file=NULL;
    init__string(&gource->video.title, "       ");
    gource->video.screen_mode=NULL;
    init__string(&gource->video.background_color, DEFAULT_BACKGROUND_COLOR);
    gource->video.camera_mode=NULL;
}

void init__subtitle(_gource *gource){
    gource->subtitle.subtitle_file=NULL;
    gource->subtitle.font_name=NULL;
    gource->subtitle.font_size=-1;
    gource->subtitle.duration=DEFAULT_SUBTITLE_DURATION;
    init__string(&gource->subtitle.color, DEFAULT_SUBTITLE_COLOR);
}

void init__other(_gource *gource){
    gource->other.auto_skip_seconds=0;
    gource->other.seconds_per_day=0;
    init__string(&gource->other.date_format, "       ");
    gource->other.folder_with_users_avatar_icon=NULL;
    gource->other.output_gorce=NULL;
}

void init__string(_string *destination, const char *initial_value){
    destination->value = (char *) malloc(STRING_DEFAULT_LENGTH* sizeof(char));
    copy_string(destination,initial_value);
}

bool is__gource_OK(_gource *gource){
    return is_malloc_OK(gource);
}

bool is_malloc_OK(_gource *gource){
    if(gource->video.title.size==0 || gource->other.date_format.size==0
    || gource->video.background_color.size==0 || gource->subtitle.color.size==0){
        return false;
    }else{
        return true;
    }
}

void print_gource(_gource *gource){
    printf("Video:\n");
    printf("\tLog file - %s\n", gource->video.log_file);
    printf("\tTitle - %s\n", gource->video.title.value);
    printf("\tScreen Mode - %s\n", gource->video.screen_mode);
    printf("\tBackground color - %s\n", gource->video.background_color.value);
    printf("\tCamer mode - %s\n", gource->video.camera_mode);

    printf("Subtitle:\n");
    printf("\tSubtitle file - %s\n", gource->subtitle.subtitle_file);
    printf("\tFont name - %s\n", gource->subtitle.font_name);
    printf("\tFont size - %d\n", gource->subtitle.font_size);
    printf("\tDuration - %d\n", gource->subtitle.duration);
    printf("\tColor - %s\n", gource->subtitle.color.value);

    printf("Other:\n");
    printf("\tAuto Skip seconds - %d\n", gource->other.auto_skip_seconds);
    printf("\tSeconds per day - %d\n", gource->other.seconds_per_day);
    printf("\tDate format - %s\n", gource->other.date_format.value);
    printf("\tFolder with users avatar icon - %s\n", gource->other.folder_with_users_avatar_icon);
    printf("\tOutput gource - %s\n", gource->other.output_gorce);

}
