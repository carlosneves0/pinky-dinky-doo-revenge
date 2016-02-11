

#include "game.h"
#include "button.h"


button* load_button( int _buttonX, int _buttonY, int _buttonWidth, int _buttonHeight, const char* _normalImg, const char* _selectedImg )
{
    button* p_temp_button = (button*)malloc( sizeof( button ) );

    if ( _normalImg )
        p_temp_button->p_normal_img = load_image( _normalImg, _buttonWidth, _buttonHeight );

    if ( _selectedImg )
        p_temp_button->p_selected_img = load_image( _selectedImg, _buttonWidth, _buttonHeight );

    // buttons are created desselected by default
    p_temp_button->bool_is_selected = 0;

    p_temp_button->x = _buttonX;
    p_temp_button->y = _buttonY;

    return p_temp_button;
}


void unload_button( button* _pButton )
{
    if ( _pButton )
    {
        if ( _pButton->p_normal_img )
            unload_image( _pButton->p_normal_img );

        if ( _pButton->p_selected_img )
            unload_image( _pButton->p_selected_img );

        free( _pButton );

        _pButton = NULL;
    }
}


void render_button( button* _pButton )
{
    if ( _pButton->bool_is_selected )
        draw_image( _pButton->p_selected_img, _pButton->x, _pButton->y );
    else
        draw_image( _pButton->p_normal_img, _pButton->x, _pButton->y );
}
