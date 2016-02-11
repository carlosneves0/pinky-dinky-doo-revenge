
#include "game.h"


void init_game( game** _ppGame )
{
    // allocate game struct in the pointer caller passed through _ppGame
    *_ppGame = (game*)malloc( sizeof( game ) );

    // check if malloc was successful
    if ( !*_ppGame )
        exit( EXIT_FAILURE );

    // there are yet no requests to quit the game
    (*_ppGame)->bool_exit = 0;

    // create and centralize the game window
    init_game_window();

    // init the flag to the main menu state so it knows wether to start or not the background music
    (*_ppGame)->main_menu_music_is_on = 0;

    // set the play button to be selected in the main menu
    (*_ppGame)->main_menu_selected_button = PLAY_BUTTON;

    // initialize the first game state, the main menu state
    (*_ppGame)->p_current_state = NULL;
    init_state( *_ppGame, MAIN_MENU );

    // initialize the current game state flag variable
    (*_ppGame)->current_state = MAIN_MENU;
}

void init_game_window( void )
{
    // Using Win32 API to get the user's desktop resolution in pixels: width x height
    int screen_width, screen_height;
    {
        const HWND desktop_handle = GetDesktopWindow();

        RECT desktop_rect;

        GetWindowRect( desktop_handle, &desktop_rect );

        screen_width  = desktop_rect.right;
        screen_height = desktop_rect.bottom;
    }

    // Calculating the position in which the window will be centered on the screen
    int window_left = ( screen_width  - GC_window_width  ) / 2;
    int window_top  = ( screen_height - GC_window_height ) / 2;

    // Call WinBGIm's initwindow(...) to create a window for us
    initwindow( GC_window_width, GC_window_height, GC_game_name, window_left, window_top );
}


void shutdown_game( game* _pGame )
{
    end_current_state( _pGame );

    // deallocate the used game struct
    if ( _pGame )
    {
        free( _pGame );
        _pGame = NULL;
    }
}


void update_game( game* _pGame )
{
    switch( _pGame->current_state )
    {
        case IN_GAME:
        {
            update_in_game( _pGame );

            break;
        }
    }

    // calculate good sleep time based on time elapsed in rendering and other operations: todo

    return;
}


int exit_request( game* _pGame )
{
    return _pGame->bool_exit ? 1 : 0;
}


/* Game State related routines */
void init_state( game* _pGame, int _stateToInit  )
{
    switch ( _stateToInit )
    {
        case MAIN_MENU:
        {
            if ( _pGame->p_current_state )
            {
                end_current_state( _pGame );
            }

            init_main_menu_state( _pGame );

            break;
        }

        case CONTROLS:
        {
            if ( _pGame->p_current_state )
            {
                end_current_state( _pGame );
            }

            init_controls_state( _pGame );

            break;
        }

        case CREDITS:
        {
            if ( _pGame->p_current_state )
            {
                end_current_state( _pGame );
            }

            init_credits_state( _pGame );

            break;
        }

        case IN_GAME:
        {
            if ( _pGame->p_current_state )
            {
                end_current_state( _pGame );
            }

            init_in_game_state( _pGame );

            break;
        }
    }
}


void end_current_state( game* _pGame )
{
    switch ( _pGame->current_state )
    {
        case MAIN_MENU:
        {
            if ( _pGame->p_current_state )
                end_main_menu_state( _pGame );

            break;
        }

        case CONTROLS:
        {
            if ( _pGame->p_current_state )
                end_controls_state( _pGame );

            break;
        }

        case CREDITS:
        {
            if ( _pGame->p_current_state )
                end_credits_state( _pGame );

            break;
        }

        case IN_GAME:
        {
            if ( _pGame->p_current_state )
                end_in_game_state( _pGame );

            break;
        }
    }
}


void switch_to_state( game* _pGame, int _stateToSwitchTo )
{
    end_current_state( _pGame );

    _pGame->current_state = _stateToSwitchTo;

    init_state( _pGame, _stateToSwitchTo );
}


/* Input Routines */
void handle_input( game* _pGame )
{
    if ( kbhit() )
    {
        int c = getch();

        switch ( _pGame->current_state )
        {
            case MAIN_MENU:
            {
                main_menu_handle_input( _pGame, c );
                break;
            }

            case CONTROLS:
            {
                controls_handle_input( _pGame, c );
                break;
            }

            case CREDITS:
            {
                credits_handle_input( _pGame, c );
                break;
            }

            case IN_GAME:
            {
                in_game_handle_input( _pGame, c );
                break;
            }
        }
    }
}


/* Output Routines */
void render_game( game* _pGame )
{
    swapbuffers();

    switch ( _pGame->current_state )
    {
        case MAIN_MENU:
        {
            render_main_menu( _pGame );
            break;
        }

        case CONTROLS:
        {
            render_controls( _pGame );
            break;
        }

        case CREDITS:
        {
            render_credits( _pGame );
            break;
        }

        case IN_GAME:
        {
            render_in_game( _pGame );
            break;
        }
    }
}


/* Collision */
int collides( rect _a, rect _b )
{
    if ( _a.left >= _b.right || _a.right <= _b.left || _a.top >= _b.bottom || _a.bottom <= _b.top )
        return 0;
    else
        return 1;
}


int touches( rect _a, rect _b )
{
    if ( _a.left == _b.right || _a.right == _b.left || _a.top == _b.bottom || _a.bottom == _b.top )
        return 1;
    else
        return 0;
}


/* Random functionality */
int return_random_argument( int _numArgs, ... )
{
    va_list args_list;

    va_start( args_list, _numArgs );

    int arguments[_numArgs];

    int i;
    for ( i = 0; i < _numArgs; i++ )
        arguments[i] = va_arg( args_list, int );

    va_end( args_list );

    return arguments[rand() % _numArgs];
}
