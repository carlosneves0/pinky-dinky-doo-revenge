

#include "game.h"
#include "state_credits.h"


/* Credits State routines */
void init_credits_state( game* _pGame )
{
    _pGame->p_current_state = malloc( sizeof( credits_state ) );

    ((credits_state*)_pGame->p_current_state)->p_background_img = load_image( GC_cr_background_img, GC_bg_img_width, GC_bg_img_height );

    ((credits_state*)_pGame->p_current_state)->p_back = load_button( GC_c_back_button_x,
                                                                    GC_c_back_button_y,
                                                                    GC_button_width,
                                                                    GC_button_height,
                                                                    NULL,
                                                                    GC_c_back_se_img );

    // set the back button to be selected:
    ((credits_state*)_pGame->p_current_state)->p_back->bool_is_selected = 1;

    // pause main menu background music and init credits background music
    pause_audio();

    _pGame->main_menu_music_is_on = 0;

    play_music( GC_cr_bg_music );

    _pGame->current_state = CREDITS;
}

void end_credits_state( game* _pGame )
{
    unload_image( ((credits_state*)_pGame->p_current_state)->p_background_img );

    unload_button( ((credits_state*)_pGame->p_current_state)->p_back );

    free( _pGame->p_current_state );

    _pGame->p_current_state = NULL;
}

void credits_handle_input( game* _pGame, int _pressedKey )
{
    switch ( _pressedKey )
    {
        // KEY_RETURN
        case '\r':
        {
            // switch current state to main menu state
            //draw_image( ((credits_state*)_pGame->p_current_state)->p_back->p_activated_img, c_back_button_x, c_back_button_y );

            //delay( 100 );

            switch_to_state( _pGame, MAIN_MENU );

            break;
        }
    }
}

void render_credits( game* _pGame )
{
    // draw background first
    draw_image( ((credits_state*)_pGame->p_current_state)->p_background_img, GC_bg_img_x, GC_bg_img_y );

    // draw back button
    render_button( ((credits_state*)_pGame->p_current_state)->p_back );
}
