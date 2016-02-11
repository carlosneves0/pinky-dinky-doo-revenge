#ifndef STATE_MAIN_MENU_H_INCLUDED
#define STATE_MAIN_MENU_H_INCLUDED


#include "button.h"


/* Main Menu State struct */
typedef struct _tagStructMainMenuState
{
    void* p_background_img;
    button* p_play;
    button* p_controls;
    button* p_credits;
    button* p_exit;
    int selected_button;
} main_menu_state;





#endif // STATE_MAIN_MENU_H_INCLUDED
