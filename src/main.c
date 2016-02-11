

#include "game.h"


int main( void )
{
    game* p_pddr = NULL;


    init_game( &p_pddr );


    while ( !exit_request( p_pddr ) )
    {
        handle_input( p_pddr );

        render_game( p_pddr );

        update_game( p_pddr );
    }


    shutdown_game( p_pddr );


    return 0;
}
