#ifndef GOURCE_H
#define GOURCE_H

typedef struct{
    char *log_file;
    const char *title;
    const char *screen_mode;
    char *background_color;
    char *camera_mode;
}_video;

typedef struct{
    char *subtitle_file;
    char *font_name;
    int font_size;
    int duration;
    char *color;
}_subtitle;

typedef struct{
    int auto_skip_seconds;
    int seconds_per_day;
    const char *date_format;
    char *folder_with_users_avatar_icon;
    char *color;
    char *output_gorce;
}_other;

typedef struct{
    _video video;
    _subtitle subtitle;
    _other other;
}_gource;

#endif
