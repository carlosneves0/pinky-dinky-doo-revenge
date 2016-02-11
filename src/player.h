#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED


#include "map.h"
#include "bomb.h"


// ---------------------------------------------------------------------------
//                          Struct declaration
// ---------------------------------------------------------------------------
struct _tagStructPlayer
{
    void* p_up_img;
    void* p_right_img;
    void* p_down_img;
    void* p_left_img;
    void* p_dead_by_pac_man_img;
    void* p_dead_by_explosion_img;

    int left;
    int top;
    int right;
    int bottom;

    int i;
    int j;

    int direction;

    int alive;
    int num_lives;

    int how_many_bombs;

    int cause_of_death;

    bomb* p_bomb;
};


// ---------------------------------------------------------------------------
//                          Type definition: player
// ---------------------------------------------------------------------------
typedef struct _tagStructPlayer     player;


// ---------------------------------------------------------------------------
//                          Functions declarations
// ---------------------------------------------------------------------------
player* construct_player();

void destroy_player( player* _pPlayer );

void render_player( player* _pPlayer );

void update_player( player* _pPlayer );

void player_walk( player* _pPlayer, map* _pMap, int _dir );

int player_can_walk( player* _pPlayer, map* _pMap, int _dir );

void player_drop_bomb( void* _pVoidGame );


#endif // PLAYER_H_INCLUDED
