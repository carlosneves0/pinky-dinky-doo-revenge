// ---------------------------------------------------------------------------
// Pinky Dink Doo: revenge!, Version 0.7, September 29, 2014
//
// Written by:
//      Carlos Andre Martins Neves  ( carlos.neves@usp.br   )
//      Matheus Costa               ( matheus.costa@usp.br  )
//      Nuno Bernardes Barcellos    ( nuno.barcellos@usp.br )
//
// University of Sao Paulo at Sao Carlos, 2014
//
// ---------------------------------------------------------------------------
//                          Notes
// ---------------------------------------------------------------------------
// * This game still has a lot of space for improvement;
// * This game has a series of limitation due to the library used;
// * The main graphic related limitation of WinBGIm is the abscence of alpha channel handling;
// * The code is completely written in C language;
// * This game only runs on the Windows OS.
// * ...anything else?
// * This game may not be compatible with 64-bit versions of Windows.
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
//                          Macro Guard and Include Directives
// ---------------------------------------------------------------------------
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "global_constants.h"
#include "state_in_game.h"
#include "state_main_menu.h"
#include "state_controls.h"
#include "state_credits.h"
#include "top_bar.h"
#include "timer.h"
#include "audio.h"
#include "image.h"
#include "button.h"
#include "player.h"
#include "npc.h"
#include "bomb.h"


// ---------------------------------------------------------------------------
//                          NO_SOUND Macro
// ---------------------------------------------------------------------------
// if the NO_WIN32_SOUND macro is defined the references to win32's PlaySound() are omitted.
// Removing audio makes the application more stable.
// win32's PlaySound() is unstable and causes crashes.
// #define NO_WIN32_SOUND

// ---------------------------------------------------------------------------
//                          Enums
// ---------------------------------------------------------------------------
enum GAME_STATES            { MAIN_MENU, CONTROLS, CREDITS, IN_GAME };

enum MAIN_MENU_BUTTONS      { PLAY_BUTTON, CONTROLS_BUTTON, CREDITS_BUTTON, EXIT_BUTTON };

enum ESCAPE_MENU_BUTTONS    { CONTINUE_BUTTON, MAIN_MENU_BUTTON };

enum BLOCK_TYPES            { NULL_BLOCK = '0', INDESTRUCTIBLE_BLOCK, DESTRUCTIBLE_BLOCK, PLAYER_RESPAWN_BLOCK = 'P', NPC_RESPAWN_BLOCK = 'N' };

enum DIRECTIONS             { UP, RIGHT, DOWN, LEFT };

enum GAME_STATE             { PLAYING, VICTORY, GAME_OVER };

enum CAUSE_OF_DEATH         { DEATH_BY_PAC_MAN, DEATH_BY_EXPLOSION };


// ---------------------------------------------------------------------------
//                          Structures
// ---------------------------------------------------------------------------
/* Auxiliary structs */


typedef struct _tagStructRect
{
    int left;
    int top;
    int right;
    int bottom;
} rect;


struct _tagStructGame
{
    void* p_current_state;
    int current_state;
    int main_menu_selected_button;
    int main_menu_music_is_on;
    int bool_exit;
};


// ---------------------------------------------------------------------------
//                          Type Definition: game
// ---------------------------------------------------------------------------
typedef struct _tagStructGame   game;


// ---------------------------------------------------------------------------
//                          Functions declarations
// ---------------------------------------------------------------------------
/* The state specific functions are implemented in their respective source files */
/* Main Menu State routines - implemented in state_main_menu.c */
void init_main_menu_state( game* _pGame );
void end_main_menu_state( game* _pGame );
void main_menu_handle_input( game* _pGame, int _pressedKey );
void render_main_menu( game* _pGame );


/* Controls State routines - implemented in state_controls.c */
void init_controls_state( game* _pGame );
void end_controls_state( game* _pGame );
void controls_handle_input( game* _pGame, int _pressedKey );
void render_controls( game* _pGame );


/* Credits State routines - implemented in state_cerdits.c */
void init_credits_state( game* _pGame );
void end_credits_state( game* _pGame );
void credits_handle_input( game* _pGame, int _pressedKey );
void render_credits( game* _pGame );


/* InGame State routines - implemented in state_in_game.c */
void init_in_game_state( game* _pGame );
void end_in_game_state( game* _pGame );
void in_game_handle_input( game* _pGame, int _pressedKey );
void render_in_game( game* _pGame );
void update_in_game( game* _pGame );
int paused( game* _pGame );
void render_esc_menu( game* _pGame );
int find_NPCs_in_map( map* _map, matrix_point* _pPointStruct );
int player_NPC_collision( player* _pPlayer, NPC** _NPCs, int _NPCCount );
int player_victory( in_game_state* _pInGameState );
void handle_game_ended( game* _pGame );


/* Game routines - implemented in game.c */
void init_game( game** _pGame );

void init_game_window( void );

void shutdown_game( game* _pGame );

void update_game( game* _pGame );

int exit_request( game* _pGame );


/* Game State related routines - implemented in game.c */
void init_state(  game* _pGame, int _stateToInit  );

void end_current_state( game* _pGame );

void switch_to_state( game* _pGame, int _stateToSwitchTo );


/* Input routines - implemented in game.c */
void handle_input( game* _pGame );


/* Output routines - implemented in game.c */
void render_game( game* _pGame );

/* "Physics" - implemented in game.c */
int collides( rect _a, rect _b );
int touches( rect _a, rect _b );


/* Random functionality - implemented in game.c */
int return_random_argument( int _numArgs, ... );


#endif // GAME_H_INCLUDED
