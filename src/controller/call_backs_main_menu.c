/*
 The MIT License (MIT)
 Copyright (c) 2018 Lorhan Sohaky
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

#include "call_backs_main_menu.h"
#include "gource.h"
#include "process_creator.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void add_gource_arguments( char *arguments[], Gource *gource, unsigned int *count );

static void add_video_arguments( char *arguments[], Video *video, unsigned int *count );
static void add_caption_arguments( char *arguments[], Caption *caption, unsigned int *count );
static void add_other_arguments( char *arguments[], Other *other, unsigned int *count );

void execute( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    unsigned int number_of_arguments = 0;

    char **arguments_for_gource = calloc( NUMBER_OF_FIELDS * 2 + 2 + 25,
                                          sizeof( char ** ) ); // +2 because the first argument is
                                                               // the program itself and the last
                                                               // is the NULL
                                                               // +25 to output gource option
    if( arguments_for_gource ) {
        arguments_for_gource[number_of_arguments++] =
            string_get_text( gource->settings.gource_executable_path );
        add_gource_arguments( arguments_for_gource, gource, &number_of_arguments );
        call_prog( string_get_text( gource->settings.gource_executable_path ),
                   arguments_for_gource,
                   number_of_arguments );
    }

    print_gource( gource );
}

static void add_gource_arguments( char *arguments[], Gource *gource, unsigned int *count ) {
    add_video_arguments( arguments, &gource->video, count );
    add_caption_arguments( arguments, &gource->caption, count );
    add_other_arguments( arguments, &gource->other, count );

    arguments[( *count )] = NULL;
}

static void add_video_arguments( char *arguments[], Video *video, unsigned int *count ) {
    if( !string_is_empty( video->repository ) ) {
        arguments[( *count )++] = string_get_text( video->repository );
    }

    if( !string_is_empty( video->title ) ) {
        arguments[( *count )++] = "--title";

        arguments[( *count )++] = string_get_text( video->title );
    }

    if( !string_is_empty( video->screen_mode ) ) {
        if( !strcmp( "Fullscreen", string_get_text( video->screen_mode ) ) ) {
            arguments[( *count )++] = "-f";
        } else if( !strcmp( "Windowed", string_get_text( video->screen_mode ) ) ) {
            arguments[( *count )++] = "-w";
        } else {
            String *tmp = string_new_with_text( string_get_text( video->screen_mode ) );
            string_sprint( video->screen_mode, "-%s", string_get_text( tmp ) );
            string_free( tmp );

            arguments[( *count )++] = string_get_text( video->screen_mode );
        }
    }

    if( !string_is_empty( video->background_color ) ) {
        arguments[( *count )++] = "-b";

        string_replace_first( video->background_color, "#", "" );
        arguments[( *count )++] = string_get_text( video->background_color );
    }

    if( !string_is_empty( video->camera_mode ) ) {
        arguments[( *count )++] = "--camera-mode";

        string_tolower( string_get_text( video->camera_mode ) );
        arguments[( *count )++] = string_get_text( video->camera_mode );
    }
}

static void add_caption_arguments( char *arguments[], Caption *caption, unsigned int *count ) {
    if( !string_is_empty( caption->file ) ) {
        arguments[( *count )++] = "--caption-file";

        arguments[( *count )++] = string_get_text( caption->file );
    }

    if( !string_is_empty( caption->font_size ) ||
        strcmp( string_get_text( caption->font_size ), "0" ) ) {
        arguments[( *count )++] = "--caption-size";

        arguments[( *count )++] = string_get_text( caption->font_size );
    }

    if( !string_is_empty( caption->duration ) ||
        strcmp( string_get_text( caption->duration ), "0" ) ) {
        arguments[( *count )++] = "--caption-duration";
        arguments[( *count )++] = string_get_text( caption->duration );
    }

    if( !string_is_empty( caption->color ) ) {
        arguments[( *count )++] = "--caption-colour";

        string_replace_first( caption->color, "#", "" );
        arguments[( *count )++] = string_get_text( caption->color );
    }
}

static void add_other_arguments( char *arguments[], Other *other, unsigned int *count ) {
    if( !string_is_empty( other->auto_skip_seconds ) ||
        strcmp( string_get_text( other->auto_skip_seconds ), "0" ) ) {
        arguments[( *count )++] = "--auto-skip-seconds";

        arguments[( *count )++] = string_get_text( other->auto_skip_seconds );
    }

    if( !string_is_empty( other->seconds_per_day ) ||
        strcmp( string_get_text( other->seconds_per_day ), "0" ) ) {
        arguments[( *count )++] = "--seconds-per-day";

        arguments[( *count )++] = string_get_text( other->seconds_per_day );
    }

    if( !string_is_empty( other->date_format ) ) {
        arguments[( *count )++] = "--date-format";

        arguments[( *count )++] = string_get_text( other->date_format );
    }

    if( !string_is_empty( other->folder_with_users_avatar_icon ) ) {
        arguments[( *count )++] = "--user-image-dir";

        arguments[( *count )++] = string_get_text( other->folder_with_users_avatar_icon );
    }
}
