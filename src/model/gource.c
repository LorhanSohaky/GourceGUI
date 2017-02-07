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

#include <gource.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

#define STRING_DEFAULT_LENGTH 7 // 6 + 1 for put '\0'

void init__video( _gource *gource );
void init__subtitle( _gource *gource );
void init__other( _gource *gource );

void init__string( String **destination, const char *initial_value );
bool is_malloc_OK( _gource *gource );

void init__gource( _gource *gource ) {
    init__video( gource );
    init__subtitle( gource );
    init__other( gource );
}

void init__video( _gource *gource ) {
    gource->video.repository = NULL;
    init__string( &gource->video.title, " " );
    gource->video.screen_mode = NULL;
    init__string( &gource->video.background_color, DEFAULT_BACKGROUND_COLOR );
    gource->video.camera_mode = NULL;
}

void init__subtitle( _gource *gource ) {
    gource->subtitle.subtitle_file = NULL;
    init__string( &gource->subtitle.font_size, "0" );
    init__string( &gource->subtitle.duration, DEFAULT_SUBTITLE_DURATION );
    init__string( &gource->subtitle.color, DEFAULT_SUBTITLE_COLOR );
}

void init__other( _gource *gource ) {
    init__string( &gource->other.auto_skip_seconds, "0" );
    init__string( &gource->other.seconds_per_day, "0" );
    init__string( &gource->other.date_format, " " );
    gource->other.folder_with_users_avatar_icon = NULL;
    gource->other.output_gorce = NULL;
}

void init__string( String **destination, const char *initial_value ) {
    *destination = string_new_with_text( initial_value );
}

bool is__gource_OK( _gource *gource ) {
    return is_malloc_OK( gource );
}

bool is_malloc_OK( _gource *gource ) {
    if( !gource->video.title || !gource->other.date_format || !gource->video.background_color ||
        !gource->subtitle.color || !gource->subtitle.font_size || !gource->subtitle.duration ||
        !gource->other.auto_skip_seconds || !gource->other.seconds_per_day ) {
        return false;
    } else {
        return true;
    }
}

void print_gource( _gource *gource ) {
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
