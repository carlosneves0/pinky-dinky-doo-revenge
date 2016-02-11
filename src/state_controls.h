#ifndef STATE_CONTROLS_H_INCLUDED
#define STATE_CONTROLS_H_INCLUDED


#include "game.h"
#include "button.h"

/* Controls State struct */
typedef struct _tagStructControlsState
{
    void* p_background_img;
    button* p_back;
} controls_state;



#endif // STATE_CONTROLS_H_INCLUDED
