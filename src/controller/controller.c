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

_gource gource_settings;

#define ARGS_TO_OUTPUT_GOURCE 25

bool append_extension_when_necessary( GtkWidget *widget );
void string_tolower( char *string );

void add_to_argv_valid_field( _gource *gource, char **argv, int *size );
void add_to_argv( char **argv, int *size, char *option, char *value );

void prepare_color( String *color );
void prepare_screen_mode( char **screen_mode );

bool copy_number_to_string( String *string, int value );

void static free_memory( _gource *gource, bool is_erro );
void static free_video( _gource *gource );
void static free_subtitle( _gource *gource );
void static free_other( _gource *gource );

int controller( int argc, char *argv[] ) {
    GtkApplication *app;
    int status = 0;
    init__gource( &gource_settings );
    if( is__gource_OK( &gource_settings ) ) {
        app = gtk_application_new( "org.gourcegui", G_APPLICATION_FLAGS_NONE );
        g_signal_connect( app, "activate", G_CALLBACK( activate ), NULL );
        status = g_application_run( G_APPLICATION( app ), argc, argv );
        g_object_unref( app );
        free_memory( &gource_settings, false );
    } else {
        free_memory( &gource_settings, true );
    }
    return status;
}

// CALLBACKs of main_menu
void execute( GtkWidget *widget, gpointer data ) {
    int number_of_fields = 0;
    char **argv;
    argv =
        (char **)malloc( sizeof( char ** ) * ( 2 * NUMBER_OF_FIELDS + 1 + ARGS_TO_OUTPUT_GOURCE ) );
    if( argv != NULL ) {
        add_to_argv_valid_field( &gource_settings, argv, &number_of_fields );
        call_prog( "/usr/bin/gource", argv, number_of_fields );
    } else {
        free_memory( &gource_settings, true );
    }
    print_gource( &gource_settings );
}

// CALLBACKs of video_page

// CALLBACKs of subtitle_page

void set_subtitle_file( GtkWidget *widget, gpointer data ) {
    gource_settings.subtitle.subtitle_file =
        gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
}

gboolean set_font_size( GtkWidget *widget, gpointer data ) {
    if( !copy_number_to_string( gource_settings.subtitle.font_size,
                                gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) ) ) {
        free_memory( &gource_settings, true );
    }
    return FALSE;
}

gboolean set_duration( GtkWidget *widget, gpointer data ) {
    if( !copy_number_to_string( gource_settings.subtitle.duration,
                                gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) ) ) {
        free_memory( &gource_settings, true );
    }
    return FALSE;
}

void set_subtitle_color( GtkWidget *widget, gpointer data ) {
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba( GTK_COLOR_CHOOSER( widget ), &rgba );
    if( !string_copy_char_array( gource_settings.subtitle.color,
                                 rgba_to_hex( rgba.red, rgba.green, rgba.blue ) ) ) {
        free_memory( &gource_settings, true );
    }
}

// CALLBACKs other_page

gboolean set_auto_skip( GtkWidget *widget, gpointer data ) {
    if( !string_sprint( gource_settings.other.auto_skip_seconds,
                        "%d",
                        gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) ) ) {
        free_memory( &gource_settings, true );
    }
    return FALSE;
}

gboolean set_seconds_per_day( GtkWidget *widget, gpointer data ) {
    if( !string_sprint( gource_settings.other.seconds_per_day,
                        "%d",
                        gtk_spin_button_get_value( GTK_SPIN_BUTTON( widget ) ) ) ) {
        free_memory( &gource_settings, true );
    }
    return FALSE;
}

gboolean set_date_format( GtkWidget *widget, gpointer data ) {
    if( !string_copy_char_array( gource_settings.other.date_format,
                                 gtk_entry_get_text( GTK_ENTRY( widget ) ) ) ) {
        free_memory( &gource_settings, true );
    }
    return FALSE;
}

void set_avatar_folder( GtkWidget *widget, gpointer data ) {
    gource_settings.other.folder_with_users_avatar_icon =
        gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
}

void set_output_gource( GtkWidget *widget ) {
    if( append_extension_when_necessary( widget ) ) {
        gource_settings.other.output_gorce =
            gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( widget ) );
    } else {
        free_memory( &gource_settings, true );
    }
}

bool append_extension_when_necessary( GtkWidget *widget ) {
    char *tmp = gtk_file_chooser_get_current_name( GTK_FILE_CHOOSER( widget ) );
    tmp = &tmp[strlen( tmp ) - strlen( ".MP4" )];
    string_tolower( tmp );
    if( strcmp( tmp, ".mp4" ) != 0 ) {
        tmp = (char *)malloc(
            sizeof( char ) *
            ( strlen( gtk_file_chooser_get_current_name( GTK_FILE_CHOOSER( widget ) ) ) +
              strlen( ".mp4" ) ) );
        if( tmp != NULL ) {
            sprintf(
                tmp, "%s.mp4", gtk_file_chooser_get_current_name( GTK_FILE_CHOOSER( widget ) ) );
            gtk_file_chooser_set_current_name( GTK_FILE_CHOOSER( widget ), tmp );
            free( tmp );
        } else {
            return false;
        }
    }
    return true;
}

void string_tolower( char *string ) {
    for( int i = 0; i < strlen( string ); i++ ) {
        string[i] = tolower( string[i] );
    }
}

void add_to_argv_valid_field( _gource *gource, char **argv, int *size ) {
    prepare_color( gource->video.background_color );
    prepare_color( gource->subtitle.color );
    if( gource->video.repository != NULL ) {
        add_to_argv( argv, size, NULL, gource->video.repository );
    }

    if( strcmp( string_get_text( gource->video.title ), " " ) != 0 ) { // space=default value
        add_to_argv( argv, size, "--title", string_get_text( gource->video.title ) );
    }

    if( gource->video.screen_mode != NULL ) {
        if( strcmp( gource->video.screen_mode, "Fullscreen" ) == 0 ) {
            add_to_argv( argv, size, "--fullscreen", NULL );
        } else if( strcmp( gource->video.screen_mode, "Windowed" ) == 0 ) {
            add_to_argv( argv, size, "--windowed", NULL );
        } else {
            prepare_screen_mode( &gource->video.screen_mode );
            add_to_argv( argv, size, NULL, gource->video.screen_mode );
        }
    }

    if( gource->video.camera_mode != NULL ) {
        if( strcmp( gource->video.camera_mode, "Overview" ) == 0 ) {
            add_to_argv( argv, size, "--camera-mode", "overview" );
        } else if( strcmp( gource->video.camera_mode, "Track" ) == 0 ) {
            add_to_argv( argv, size, "--camera-mode", "track" );
        }
    }

    if( gource->subtitle.subtitle_file != NULL ) {
        add_to_argv( argv, size, "--caption-file", gource->subtitle.subtitle_file );
    }

    if( atoi( string_get_text( gource->subtitle.font_size ) ) != 0 ) {
        add_to_argv( argv, size, "--font-size", string_get_text( gource->subtitle.font_size ) );
    }

    add_to_argv( argv, size, "--caption-duration", string_get_text( gource->subtitle.duration ) );

    add_to_argv( argv, size, "--caption-colour", string_get_text( gource->subtitle.color ) );

    if( atoi( string_get_text( gource->other.auto_skip_seconds ) ) != 0 ) {
        add_to_argv(
            argv, size, "--auto-skip-seconds", string_get_text( gource->other.auto_skip_seconds ) );
    }

    if( atoi( string_get_text( gource->other.seconds_per_day ) ) != 0 ) {
        add_to_argv(
            argv, size, "--seconds-per-day", string_get_text( gource->other.seconds_per_day ) );
    }

    if( !string_is_empty( gource->other.date_format ) &&
        strcmp( string_get_text( gource->other.date_format ), " " ) != 0 ) {
        add_to_argv( argv, size, "--date-format", string_get_text( gource->other.date_format ) );
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

void add_to_argv( char **argv, int *size, char *option, char *value ) {
    if( option != NULL ) {
        argv[*size] = option;
        ( *size )++;
    }
    if( value != NULL ) {
        argv[*size] = value;
        ( *size )++;
    }
}

void prepare_color( String *color ) { // Remove # from string
    string_replace_first( color, "#", "" );
}

void prepare_screen_mode( char **screen_mode ) {
    char *tmp = g_try_malloc( strlen( *screen_mode ) + 2 );
    if( tmp != NULL ) {
        sprintf( tmp, "-%s", *screen_mode );
        g_free( *screen_mode );
        *screen_mode = tmp;
    }
}

bool copy_number_to_string( String *string, int value ) {
    return string_sprint( string, "%d", value ); // 10= decimal
}

void static free_memory( _gource *gource, bool is_erro ) {
    if( is_erro == true ) {
        fprintf( stderr, "Failed to allocate memory.\n" );
        exit( 0 );
    }
    free_video( gource );
    free_subtitle( gource );
    free_other( gource );
}

void static free_video( _gource *gource ) {
    if( gource->video.repository != NULL ) {
        g_free( gource->video.repository );
    }

    if( gource->video.title != NULL ) {
        string_free( gource->video.title );
    }

    if( gource->video.screen_mode != NULL ) {
        g_free( gource->video.screen_mode );
    }

    if( gource->video.background_color != NULL ) {
        string_free( gource->video.background_color );
    }

    if( gource->video.camera_mode != NULL ) {
        g_free( gource->video.camera_mode );
    }
}

void static free_subtitle( _gource *gource ) {
    if( gource->subtitle.subtitle_file != NULL ) {
        g_free( gource->subtitle.subtitle_file );
    }

    if( gource->subtitle.font_size != NULL ) {
        string_free( gource->subtitle.font_size );
    }

    if( gource->subtitle.duration != NULL ) {
        string_free( gource->subtitle.duration );
    }

    if( gource->subtitle.color != NULL ) {
        string_free( gource->subtitle.color );
    }
}

void static free_other( _gource *gource ) {
    if( gource->other.auto_skip_seconds != NULL ) {
        string_free( gource->other.auto_skip_seconds );
    }

    if( gource->other.seconds_per_day != NULL ) {
        string_free( gource->other.seconds_per_day );
    }

    if( gource->other.date_format != NULL ) {
        string_free( gource->other.date_format );
    }

    if( gource->other.folder_with_users_avatar_icon != NULL ) {
        g_free( gource->other.folder_with_users_avatar_icon );
    }

    if( gource->other.output_gorce != NULL ) {
        g_free( gource->other.output_gorce );
    }
}
