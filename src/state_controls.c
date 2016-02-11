

#include "game.h"



void init_controls_state( game* _pGame )
{
    _pGame->p_current_state = malloc( sizeof( controls_state ) );

    ((controls_state*)_pGame->p_current_state)->p_background_img = load_image( GC_co_background_img, GC_bg_img_width, GC_bg_img_height );

    ( ((controls_state*)_pGame->p_current_state) )->p_back = load_button( GC_c_back_button_x,
                                                                         GC_c_back_button_y,
                                                                         GC_button_width,
                                                                         GC_button_height,
                                                                         NULL,
                                                                         GC_c_back_se_img );

    // set the back button to be selected:
    ((controls_state*)_pGame->p_current_state)->p_back->bool_is_selected = 1;

    _pGame->current_state = CONTROLS;
}

void end_controls_state( game* _pGame )
{
    unload_image( ((controls_state*)_pGame->p_current_state)->p_background_img );

    unload_button( ((controls_state*)_pGame->p_current_state)->p_back );

    free( _pGame->p_current_state );

    _pGame->p_current_state = NULL;
}

void controls_handle_input( game* _pGame, int _pressedKey )
{
    switch ( _pressedKey )
    {
        // KEY_RETURN
        case '\r':
        {
            switch_to_state( _pGame, MAIN_MENU );

            break;
        }
    }
}

void render_controls( game* _pGame )
{
    // draw background first
    draw_image( ((controls_state*)_pGame->p_current_state)->p_background_img, GC_bg_img_x, GC_bg_img_y );

    // draw back button
    render_button( ((controls_state*)_pGame->p_current_state)->p_back );
}
