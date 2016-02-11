#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED


#include "timer.h"
#include "bomb.h"
#include "map.h"
#include "npc.h"


// ---------------------------------------------------------------------------
//                          Struct declaration
// ---------------------------------------------------------------------------
struct _tagStructNPC
{
    void** NPC_up_frames;
    void** NPC_right_frames;
    void** NPC_down_frames;
    void** NPC_left_frames;

    int    up_frame_index;
    int    right_frame_index;
    int    down_frame_index;
    int    left_frame_index;

    int left;
    int top;
    int right;
    int bottom;

    int i;
    int j;

    int direction;

    int alive;

    //void (*p_NPC_AI)( NPC*, bomb*, NPC**, int, map* );   // walking AI

    timer* walk_timer;
    timer* AI_timer;
    timer* frame_timer;
};


// ---------------------------------------------------------------------------
//                          Type definition: NPC
// ---------------------------------------------------------------------------
typedef struct _tagStructNPC    NPC;


// ---------------------------------------------------------------------------
//                          Functions declarations
// ---------------------------------------------------------------------------
NPC* construct_NPC( int _xInMatrix, int _yInMatrix );

void destroy_NPC( NPC* _pNPC );

void render_NPC( NPC* _pNPC );

void render_NPCs( NPC** _NPCs, int _NPCCount );

void update_NPCs_frames( NPC** _NPCs, int _NPCCount );

void update_NPCs( NPC** _NPCs, int _NPCCount, bomb* _pBomb, map* _pMap );

void NPC_walk( NPC* _pNPC, bomb* _pBomb, NPC** _NPCs, int _NPCCount, map* _pMap, int _dir );

int  NPC_can_walk( NPC* _pNPC, bomb* _pBomb, NPC** _NPCs, int _NPCCount, map* _pMap, int _dir );

void NPC_random_walk_AI( NPC* _pNPC, bomb* _pBomb, NPC** _NPCs, int _NPCCount, map* _pMap );


#endif // NPC_H_INCLUDED
