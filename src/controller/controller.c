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
#include <stdio.h>

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
