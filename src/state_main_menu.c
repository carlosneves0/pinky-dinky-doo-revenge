
#include "game.h"
#include "state_main_menu.h"

void init_main_menu_state( game* _pGame )
{
    _pGame->p_current_state = malloc( sizeof( main_menu_state ) );

    ((main_menu_state*)_pGame->p_current_state)->p_background_img = load_image( GC_mm_background_img, GC_bg_img_width, GC_bg_img_height );

    ((main_menu_state*)_pGame->p_current_state)->p_play = load_button( GC_mm_play_button_x,
                                                                      GC_mm_play_button_y,
                                                                      GC_button_width,
                                                                      GC_button_height,
                                                                      GC_mm_play_nr_img,
                                                                      GC_mm_play_se_img );

    ((main_menu_state*)_pGame->p_current_state)->p_controls = load_button( GC_mm_controls_button_x,
                                                                          GC_mm_controls_button_y,
                                                                          GC_button_width,
                                                                          GC_button_height,
                                                                          GC_mm_controls_nr_img,
                                                                          GC_mm_controls_se_img );

    ((main_menu_state*)_pGame->p_current_state)->p_credits = load_button( GC_mm_credits_button_x,
                                                                         GC_mm_credits_button_y,
                                                                         GC_button_width,
                                                                         GC_button_height,
                                                                         GC_mm_credits_nr_img,
                                                                         GC_mm_credits_se_img );

    ((main_menu_state*)_pGame->p_current_state)->p_exit = load_button( GC_mm_exit_button_x,
                                                                      GC_mm_exit_button_y,
                                                                      GC_button_width,
                                                                      GC_button_height,
                                                                      GC_mm_exit_nr_img,
                                                                      GC_mm_exit_se_img );

    // look in the game struct which button is supposed to be selected
    switch ( _pGame->main_menu_selected_button )
    {
        case PLAY_BUTTON:
        {
            ((main_menu_state*)_pGame->p_current_state)->p_play->bool_is_selected = 1;
            ((main_menu_state*)_pGame->p_current_state)->selected_button = PLAY_BUTTON;
            break;
        }

        case CONTROLS_BUTTON:
        {
            ((main_menu_state*)_pGame->p_current_state)->p_controls->bool_is_selected = 1;
            ((main_menu_state*)_pGame->p_current_state)->selected_button = CONTROLS_BUTTON;
            break;
        }

        case CREDITS_BUTTON:
        {
            ((main_menu_state*)_pGame->p_current_state)->p_credits->bool_is_selected = 1;
            ((main_menu_state*)_pGame->p_current_state)->selected_button = CREDITS_BUTTON;
            break;
        }
    }

    // init main menu background music if music isn't already playing
    if ( !_pGame->main_menu_music_is_on )
    {
        play_music( GC_mm_bg_music );
        _pGame->main_menu_music_is_on = 1;
    }

    _pGame->current_state = MAIN_MENU;
}

void end_main_menu_state( game* _pGame )
{
    unload_image( ((main_menu_state*)_pGame->p_current_state)->p_background_img );

    unload_button( ((main_menu_state*)_pGame->p_current_state)->p_play );

    unload_button( ((main_menu_state*)_pGame->p_current_state)->p_controls );

    unload_button( ((main_menu_state*)_pGame->p_current_state)->p_credits );

    unload_button( ((main_menu_state*)_pGame->p_current_state)->p_exit );

    // before freeing the main menu state struct save in the game struct which menu button was selected
    _pGame->main_menu_selected_button = ((main_menu_state*)_pGame->p_current_state)->selected_button;

    free( _pGame->p_current_state );

    _pGame->p_current_state = NULL;
}


void main_menu_handle_input( game* _pGame, int _pressedKey )
{
    switch ( _pressedKey )
    {
        case KEY_UP:
        case 'W':
        case 'w':
        {
            // switch selected button( or not if  play button is the one which is selected ):
            if ( ((main_menu_state*)_pGame->p_current_state)->selected_button == PLAY_BUTTON )
                ; // do nothing
            else if (  ((main_menu_state*)_pGame->p_current_state)->selected_button == CONTROLS_BUTTON )
            {
                ((main_menu_state*)_pGame->p_current_state)->selected_button = PLAY_BUTTON;
                ((main_menu_state*)_pGame->p_current_state)->p_play->bool_is_selected     = 1;
                ((main_menu_state*)_pGame->p_current_state)->p_controls->bool_is_selected = 0;
            }
            else if (  ((main_menu_state*)_pGame->p_current_state)->selected_button == CREDITS_BUTTON )
            {
                ((main_menu_state*)_pGame->p_current_state)->selected_button = CONTROLS_BUTTON;
                ((main_menu_state*)_pGame->p_current_state)->p_controls->bool_is_selected = 1;
                ((main_menu_state*)_pGame->p_current_state)->p_credits->bool_is_selected  = 0;
            }
            else // EXIT_BUTTON
            {
                ((main_menu_state*)_pGame->p_current_state)->selected_button = CREDITS_BUTTON;
                ((main_menu_state*)_pGame->p_current_state)->p_credits->bool_is_selected = 1;
                ((main_menu_state*)_pGame->p_current_state)->p_exit->bool_is_selected    = 0;
            }

            break;
        }

        case KEY_DOWN:
        case 'S':
        case 's':
        {
            // switch selected button( or not if  exit button is the one which is selected ):
            if ( ((main_menu_state*)_pGame->p_current_state)->selected_button == PLAY_BUTTON )
            {
                ((main_menu_state*)_pGame->p_current_state)->selected_button = CONTROLS_BUTTON;
                ((main_menu_state*)_pGame->p_current_state)->p_play->bool_is_selected     = 0;
                ((main_menu_state*)_pGame->p_current_state)->p_controls->bool_is_selected = 1;
            }
            else if (  ((main_menu_state*)_pGame->p_current_state)->selected_button == CONTROLS_BUTTON )
            {
                ((main_menu_state*)_pGame->p_current_state)->selected_button = CREDITS_BUTTON;
                ((main_menu_state*)_pGame->p_current_state)->p_controls->bool_is_selected = 0;
                ((main_menu_state*)_pGame->p_current_state)->p_credits->bool_is_selected  = 1;
            }
            else if (  ((main_menu_state*)_pGame->p_current_state)->selected_button == CREDITS_BUTTON )
            {
                ((main_menu_state*)_pGame->p_current_state)->selected_button = EXIT_BUTTON;
                ((main_menu_state*)_pGame->p_current_state)->p_credits->bool_is_selected = 0;
                ((main_menu_state*)_pGame->p_current_state)->p_exit->bool_is_selected    = 1;
            }
            else // EXIT_BUTTON
                ; // do nothing

            break;
        }

        // KEY_RETURN
        case '\r':
        {
            // switch current state based on which button is selected
            if ( ((main_menu_state*)_pGame->p_current_state)->selected_button == PLAY_BUTTON )
            {
                switch_to_state( _pGame, IN_GAME );
            }
            else if (  ((main_menu_state*)_pGame->p_current_state)->selected_button == CONTROLS_BUTTON )
            {
                switch_to_state( _pGame, CONTROLS );
            }
            else if (  ((main_menu_state*)_pGame->p_current_state)->selected_button == CREDITS_BUTTON )
            {
                switch_to_state( _pGame, CREDITS );
            }
            else // EXIT_BUTTON
            {
                _pGame->bool_exit = 1; // exit request
            }

            break;
        }
    }
}

void render_main_menu( game* _pGame )
{
    // draw background first
    draw_image( ((main_menu_state*)_pGame->p_current_state)->p_background_img, GC_bg_img_x, GC_bg_img_y );

    // draw play button
    render_button( ((main_menu_state*)_pGame->p_current_state)->p_play );

    // draw controls button
    render_button( ((main_menu_state*)_pGame->p_current_state)->p_controls );

    // draw credits button
    render_button( ((main_menu_state*)_pGame->p_current_state)->p_credits );

    // draw exit button
    render_button( ((main_menu_state*)_pGame->p_current_state)->p_exit );
}
