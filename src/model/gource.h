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

#include <dstring.h>
#include <stdbool.h>

// I tested these value, so are good numbers for me (LOL)

// DEFAULT VALUES FOR VIDEO
static const char *DEFAULT_REPOSITORY = NULL;
static const char *DEFAULT_TITLE = NULL;
static const char *DEFAULT_SCREEN_MODE = " ";
static const char *DEFAULT_BACKGROUND_COLOR = "#555555";
static const char *DEFAULT_CAMERA_MODE = " ";

// DEFAULT VALUES FOR CAPTION
static const char *DEFAULT_CAPTION_FILE = NULL;
static const char *DEFAULT_CAPTION_FONT_SIZE = "20";
static const char *DEFAULT_CAPTION_DURATION = "3";
static const char *DEFAULT_CAPTION_COLOR = "#FFD700";

// DEFAULT VALUES FOR OTHER
static const char *DEFAULT_AUTO_SKIP_SECONDS = "3";
static const char *DEFAULT_SECONDS_PER_DAY = "2";
static const char *DEFAULT_DATE_FORMAT = "%d/%m/%y  %H:%M:%S";
static const char *DEFAULT_FOLDER_WITH_USERS_AVATAR_ICON = NULL;
static const char *DEFAULT_OUTPUT_GOURCE = NULL;

#define NUMBER_OF_FIELDS 15

typedef struct {
    char *repository;
    String *title;
    char *screen_mode;
    String *background_color;
    char *camera_mode;
} Video;

typedef struct {
    char *file;
    String *font_size;
    String *duration;
    String *color;
} Caption;

typedef struct {
    String *auto_skip_seconds;
    String *seconds_per_day;
    String *date_format;
    char *folder_with_users_avatar_icon;
    char *output_gorce;
} Other;

typedef struct {
    Video video;
    Subtitle subtitle;
    Other other;
} Gource;

void init_gource_with_default_values( Gource *gource );
void print_gource( Gource *gource );

bool is_gource_ok( Gource *gource );

#endif
