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

#include "controller.h"
#include "dstring.h"
#include "gource.h"
#include "process_creator.h"
#include "utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_to_argv_valid_field( Gource *gource, char **argv, int *size );
void add_to_argv( char **argv, int *size, char *option, String *value );

void prepare_color( String *color );
void prepare_screen_mode( String *screen_mode );

static void free_gource( Gource *gource );
static void free_video( Video *video );
static void free_caption( Caption *caption );
static void free_other( Other *other );

int controller( int argc, char *argv[] ) {
    Gource gource_settings;
    init_gource_with_default_values( &gource_settings );
    int status = 0;

    if( is_gource_ok( &gource_settings ) ) {
        GtkApplication *app = gtk_application_new( "org.gourcegui", G_APPLICATION_FLAGS_NONE );
        g_signal_connect( app, "activate", G_CALLBACK( activate ), &gource_settings );
        status = g_application_run( G_APPLICATION( app ), argc, argv );
        g_object_unref( app );
        free_gource( &gource_settings );
    } else {
        fprintf( stderr, "Failed to allocate memory.\n" );
        free_gource( &gource_settings );
    }
    return status;
}

void add_to_argv_valid_field( Gource *gource, char **argv, int *size ) {
    prepare_color( gource->video.background_color );
    prepare_color( gource->caption.color );
    if( gource->video.repository != NULL ) {
        add_to_argv( argv, size, NULL, gource->video.repository );
    }

    if( strcmp( string_get_text( gource->video.title ), " " ) != 0 ) { // space=default value
        add_to_argv( argv, size, "--title", gource->video.title );
    }

    if( gource->video.screen_mode != NULL ) {
        if( strcmp( string_get_text( gource->video.screen_mode ), "Fullscreen" ) == 0 ) {
            add_to_argv( argv, size, "--fullscreen", NULL );
        } else if( strcmp( string_get_text( gource->video.screen_mode ), "Windowed" ) == 0 ) {
            add_to_argv( argv, size, "--windowed", NULL );
        } else {
            prepare_screen_mode( gource->video.screen_mode );
            add_to_argv( argv, size, NULL, gource->video.screen_mode );
        }
    }

    if( gource->video.camera_mode != NULL ) {
        if( strcmp( string_get_text( gource->video.camera_mode ), "Overview" ) == 0 ) {
            String *tmp = string_new_with_text( "overview" );
            add_to_argv( argv, size, "--camera-mode", tmp );
        } else if( strcmp( string_get_text( gource->video.camera_mode ), "Track" ) == 0 ) {
            String *tmp = string_new_with_text( "track" );
            add_to_argv( argv, size, "--camera-mode", tmp );
        }
    }

    if( gource->caption.file != NULL ) {
        add_to_argv( argv, size, "--caption-file", gource->caption.file );
    }

    if( atoi( string_get_text( gource->caption.font_size ) ) != 0 ) {
        add_to_argv( argv, size, "--font-size", gource->caption.font_size );
    }

    add_to_argv( argv, size, "--caption-duration", gource->caption.duration );

    add_to_argv( argv, size, "--caption-colour", gource->caption.color );

    if( atoi( string_get_text( gource->other.auto_skip_seconds ) ) != 0 ) {
        add_to_argv( argv, size, "--auto-skip-seconds", gource->other.auto_skip_seconds );
    }

    if( atoi( string_get_text( gource->other.seconds_per_day ) ) != 0 ) {
        add_to_argv( argv, size, "--seconds-per-day", gource->other.seconds_per_day );
    }

    if( !string_is_empty( gource->other.date_format ) &&
        strcmp( string_get_text( gource->other.date_format ), " " ) != 0 ) {
        add_to_argv( argv, size, "--date-format", gource->other.date_format );
    }

    if( gource->other.folder_with_users_avatar_icon != NULL ) {
        add_to_argv( argv, size, "--user-image-dir", gource->other.folder_with_users_avatar_icon );
    }

    if( gource->other.output_gorce != NULL ) {
        // TODO To Implement
        /*add_to_argv(argv,size,"-o","-");
        add_to_argv(argv,size,"|","/usr/bin/ffmpeg");
        add_to_argv(argv,size,"-y","-r");
        add_to_argv(argv,size,"60","-f");
        add_to_argv(argv,size,"image2pipe","-vcodec");
        add_to_argv(argv,size,"ppm","-i");
        add_to_argv(argv,size,"-","-vcodec");
        add_to_argv(argv,size,"libx264","-preset");
        add_to_argv(argv,size,"ultrafast","-pix_fmt");
        add_to_argv(argv,size,"yuv420p","-crf");
        add_to_argv(argv,size,"1","-threads");
        add_to_argv(argv,size,"0","-bf");
        add_to_argv(argv,size,"0",gource->other.output_gorce);*/
    }
    argv[*size] = NULL;
}

void add_to_argv( char **argv, int *size, char *option, String *value ) {
    if( option != NULL ) {
        argv[*size] = option;
        ( *size )++;
    }
    if( value != NULL ) {
        argv[*size] = string_get_text( value );
        ( *size )++;
    }
}

void prepare_color( String *color ) { // Remove # from string
    string_replace_first( color, "#", "" );
}

void prepare_screen_mode( String *screen_mode ) {
    string_sprint( screen_mode, "-%s", string_get_text( screen_mode ) );
}

void static free_gource( Gource *gource ) {
    free_video( &gource->video );
    free_caption( &gource->caption );
    free_other( &gource->other );
}

static void free_video( Video *video ) {
    if( video->repository ) {
        string_free( video->repository );
    }

    if( video->title ) {
        string_free( video->title );
    }

    if( video->screen_mode ) {
        string_free( video->screen_mode );
    }

    if( video->background_color ) {
        string_free( video->background_color );
    }

    if( video->camera_mode ) {
        string_free( video->camera_mode );
    }
}

static void free_caption( Caption *caption ) {
    if( caption->file ) {
        string_free( caption->file );
    }

    if( caption->font_size ) {
        string_free( caption->font_size );
    }

    if( caption->duration ) {
        string_free( caption->duration );
    }

    if( caption->color ) {
        string_free( caption->color );
    }
}

static void free_other( Other *other ) {
    if( other->auto_skip_seconds ) {
        string_free( other->auto_skip_seconds );
    }

    if( other->seconds_per_day ) {
        string_free( other->seconds_per_day );
    }

    if( other->date_format ) {
        string_free( other->date_format );
    }

    if( other->folder_with_users_avatar_icon ) {
        string_free( other->folder_with_users_avatar_icon );
    }

    if( other->output_gorce ) {
        string_free( other->output_gorce );
    }
}
