#ifndef GOURCE_H
#define GOURCE_H

#include <stdbool.h>

static const char *DEFAULT_SUBTITLE_DURATION="3"; //I tested, so 3 it's a good number (LOL)
static const char *DEFAULT_BACKGROUND_COLOR="#555555";
static const char *DEFAULT_SUBTITLE_COLOR="#FFD700";

#define NUMBER_OF_FIELDS 15

typedef struct{
    char *value;
    unsigned int size;
}_string;

typedef struct{
    char *log_file;
    _string title;
    char *screen_mode;
    _string background_color;
    char *camera_mode;
}_video;

typedef struct{
    char *subtitle_file;
    _string font_size;
    _string duration;
    _string color;
}_subtitle;

typedef struct{
    _string auto_skip_seconds;
    _string seconds_per_day;
    _string date_format;
    char *folder_with_users_avatar_icon;
    char *output_gorce;
}_other;

typedef struct{
    _video video;
    _subtitle subtitle;
    _other other;
}_gource;

void init__gource(_gource *gource);
void print_gource(_gource *gource);

bool is__gource_OK(_gource *gource);

#endif
