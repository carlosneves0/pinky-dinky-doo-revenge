#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED


#include "game.h"
#include "timer.h"

typedef struct _tagStructMatrixPoint
{
    int i;
    int j;
} matrix_point;


/* Bomb Struct */
typedef struct _tagBombStruct
{
    int left;
    int top;
    int right;
    int bottom;

    int i;
    int j;

    int range;
    int active;
    int explode;

    matrix_point* p_blocks_that_will_explode;  // i,j coordinates in map's matrix
    int blocks_count;

    void*  bomb_img;
    void** explosion_frames;

    timer* bomb_timer;
    timer* explosion_timer;
} bomb;


bomb* construct_bomb();

void destroy_bomb( bomb* _pBomb );

void render_bomb( bomb* _pBomb );

void render_explosion( bomb* _pBomb, map* _pMap, void* _pVoidPlayer, void** _voidNPCs, int _NPCCount );

void explode( void* _pVoidGame );

void explode_destructibles( bomb* _pBomb, map* _pMap );

void explode_player( bomb* _pBomb, void* _pVoidPlayer );

void explode_NPCs( bomb* _pBomb, void** _voidNPCs, int _NPCCount );


#endif // BOMB_H_INCLUDED
