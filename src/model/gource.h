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

#include <stdbool.h>

static const char *DEFAULT_SUBTITLE_DURATION = "3"; // I tested, so 3 it's a good number (LOL)
static const char *DEFAULT_BACKGROUND_COLOR = "#555555";
static const char *DEFAULT_SUBTITLE_COLOR = "#FFD700";

#define NUMBER_OF_FIELDS 15

typedef struct {
    char *value;
    unsigned int size;
} _string;

typedef struct {
    char *repository;
    _string title;
    char *screen_mode;
    _string background_color;
    char *camera_mode;
} _video;

typedef struct {
    char *subtitle_file;
    _string font_size;
    _string duration;
    _string color;
} _subtitle;

typedef struct {
    _string auto_skip_seconds;
    _string seconds_per_day;
    _string date_format;
    char *folder_with_users_avatar_icon;
    char *output_gorce;
} _other;

typedef struct {
    _video video;
    _subtitle subtitle;
    _other other;
} _gource;

void init__gource( _gource *gource );
void print_gource( _gource *gource );

bool is__gource_OK( _gource *gource );

#endif
