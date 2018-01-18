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

void execute( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    unsigned int number_of_arguments = 0;

    char **arguments_for_gource = calloc( NUMBER_OF_FIELDS * 2 + 2,
                                          sizeof( char ** ) ); // +2 because the first argument is
                                                               // the program itself and the last
                                                               // is the NULL
    if( arguments_for_gource ) {
        arguments_for_gource[number_of_arguments++] = "/usr/bin/gource";
        add_gource_arguments( arguments_for_gource, gource, &number_of_arguments );
        call_prog( "/usr/bin/gource", arguments_for_gource, number_of_arguments );
    }

    print_gource( gource );
}

static void add_gource_arguments( char *arguments[], Gource *gource, unsigned int *count ) {
    add_video_arguments( arguments, &gource->video, count );
    add_caption_arguments( arguments, &gource->caption, count );

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
