#ifndef STATE_IN_GAME_H_INCLUDED
#define STATE_IN_GAME_H_INCLUDED


#include "top_bar.h"
#include "button.h"
#include "map.h"
#include "player.h"
#include "npc.h"


/* InGame State struct */
typedef struct _tagStructInGameState
{
    map*    p_map;
    player* p_player;
    NPC**   pp_NPCs;
    int NPC_count;

    top_bar* p_top_bar;
    void* p_esc_menu_img;

    button* p_continue;
    button* p_main_menu;
    button* p_exit;

    int selected_button;
    int bool_menu_is_active;

    int game_state;
    int bool_paused;

    int timer_set;
    timer* game_ended_timer;
} in_game_state;


#endif // STATE_IN_GAME_H_INCLUDED
