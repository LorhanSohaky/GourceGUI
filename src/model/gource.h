/*
The MIT License (MIT)
Copyright (c) 2016 Lorhan Sohaky
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef GOURCE_H
#define GOURCE_H

#include "dstring.h"
#include <stdlib.h>

// I tested these value, so are good numbers for me (LOL)

// DEFAULT VALUES FOR VIDEO
#define DEFAULT_REPOSITORY ""
#define DEFAULT_TITLE ""
#define DEFAULT_SCREEN_MODE " "
#define DEFAULT_BACKGROUND_COLOR "#555555"
#define DEFAULT_CAMERA_MODE " "

// DEFAULT VALUES FOR CAPTION
#define DEFAULT_CAPTION_FILE ""
#define DEFAULT_CAPTION_FONT_SIZE "20"
#define DEFAULT_CAPTION_DURATION "3"
#define DEFAULT_CAPTION_COLOR "#FFD700"

// DEFAULT VALUES FOR OTHER
#define DEFAULT_AUTO_SKIP_SECONDS "3"
#define DEFAULT_SECONDS_PER_DAY "2"
#define DEFAULT_DATE_FORMAT "%d/%m/%y  %H:%M:%S"
#define DEFAULT_FOLDER_WITH_USERS_AVATAR_ICON ""
#define DEFAULT_OUTPUT_GOURCE ""

#define NUMBER_OF_FIELDS 15

typedef struct {
    String *repository;
    String *title;
    String *screen_mode;
    String *background_color;
    String *camera_mode;
} Video;

typedef struct {
    String *file;
    String *font_size;
    String *duration;
    String *color;
} Caption;

typedef struct {
    String *auto_skip_seconds;
    String *seconds_per_day;
    String *date_format;
    String *folder_with_users_avatar_icon;
    String *output_gorce;
} Other;

typedef struct {
    Video video;
    Caption caption;
    Other other;
} Gource;

void init_gource_with_default_values( Gource *gource );
void print_gource( Gource *gource );

int is_gource_ok( Gource *gource );

#endif
