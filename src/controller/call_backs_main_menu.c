#include "call_backs_main_menu.h"
#include "gource.h"
#include "process_creator.h"
#include <stdio.h>
#include <stdlib.h>

#define ARGS_TO_OUTPUT_GOURCE 25

void execute( GtkWidget *widget, gpointer data ) {
    Gource *gource = (Gource *)data;
    print_gource( gource );

    //    if( argv != NULL ) {
    // add_to_argv_valid_field( &gource_settings, argv, &number_of_fields );
    // call_prog( "/usr/bin/gource", argv, number_of_fields );
    //    } else {
    // free_memory( &gource_settings, true );
    //    }
    // print_gource( gource_settings );
}
