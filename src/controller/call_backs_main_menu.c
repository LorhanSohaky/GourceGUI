#include "call_backs_main_menu.h"

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
