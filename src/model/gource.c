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

#include "gource.h"
#include "dstring.h"
#include <stdio.h>
#include <stdlib.h>

static void init_video_with_default_values( Gource *gource );
static void init_caption_with_default_values( Gource *gource );
static void init_other_with_default_values( Gource *gource );

void init_string( String **destination, const char *initial_value );
bool is_malloc_OK( Gource *gource );

void init_gource_with_default_values( Gource *gource ) {
    init_video_with_default_values( gource );
    init_caption_with_default_values( gource );
    init_other_with_default_values( gource );
}

void init_video_with_default_values( Gource *gource ) {
    gource->video.repository = DEFAULT_REPOSITORY;
    gource->video.title = DEFAULT_TITLE;
    gource->video.screen_mode = DEFAULT_SCREEN_MODE;
    gource->video.background_color = DEFAULT_BACKGROUND_COLOR;
    gource->video.camera_mode = DEFAULT_CAMERA_MODE;
}

void init_caption_with_default_values( Gource *gource ) {
    gource->caption.file = DEFAULT_CAPTION_FILE;
    gource->caption.font_size = DEFAULT_CAPTION_FONT_SIZE;
    gource->caption.duration = DEFAULT_SUBTITLE_DURATION;
    gource->caption.color = DEFAULT_SUBTITLE_COLOR;
}

void init_other_with_default_values( Gource *gource ) {
    gource->other.auto_skip_seconds = DEFAULT_AUTO_SKIP_SECONDS;
    gource->other.seconds_per_day = DEFAULT_SECONDS_PER_DAY;
    gource->other.date_format = DEFAULT_DATE_FORMAT;
    gource->other.folder_with_users_avatar_icon = DEFAULT_FOLDER_WITH_USERS_AVATAR_ICON;
    gource->other.output_gorce = DEFAULT_OUTPUT_GOURCE;
}

void printGource( Gource *gource ) {
    printf( "Video:\n" );
    printf( "\tRepository - %s\n", gource->video.repository );
    printf( "\tTitle - %s\n", string_get_text( gource->video.title ) );
    printf( "\tScreen Mode - %s\n", gource->video.screen_mode );
    printf( "\tBackground color - %s\n", string_get_text( gource->video.background_color ) );
    printf( "\tCamer mode - %s\n", gource->video.camera_mode );

    printf( "Subtitle:\n" );
    printf( "\tSubtitle file - %s\n", gource->subtitle.subtitle_file );
    printf( "\tFont size - %s\n", string_get_text( gource->subtitle.font_size ) );
    printf( "\tDuration - %s\n", string_get_text( gource->subtitle.duration ) );
    printf( "\tColor - %s\n", string_get_text( gource->subtitle.color ) );

    printf( "Other:\n" );
    printf( "\tAuto Skip seconds - %s\n", string_get_text( gource->other.auto_skip_seconds ) );
    printf( "\tSeconds per day - %s\n", string_get_text( gource->other.seconds_per_day ) );
    printf( "\tDate format - %s\n", string_get_text( gource->other.date_format ) );
    printf( "\tFolder with users avatar icon - %s\n", gource->other.folder_with_users_avatar_icon );
    printf( "\tOutput gource - %s\n", gource->other.output_gorce );
}
