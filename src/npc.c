

#include "game.h"
#include "npc.h"


NPC* construct_NPC( int _xInMatrix, int _yInMatrix )
{
    NPC* p_temp_npc = (NPC*)malloc( sizeof( NPC ) );

    // load all 12 frames of the pacmen
    p_temp_npc->NPC_up_frames    = (void**)malloc( GC_NPC_frames * sizeof( void* ) );

    p_temp_npc->NPC_right_frames = (void**)malloc( GC_NPC_frames * sizeof( void* ) );

    p_temp_npc->NPC_down_frames  = (void**)malloc( GC_NPC_frames * sizeof( void* ) );

    p_temp_npc->NPC_left_frames  = (void**)malloc( GC_NPC_frames * sizeof( void* ) );

    int i;
    for ( i = 0; i < GC_NPC_frames; i++ )
        p_temp_npc->NPC_up_frames[i] = load_image( GC_pac_man_up_frames[i], GC_block_size, GC_block_size );

    for ( i = 0; i < GC_NPC_frames; i++ )
        p_temp_npc->NPC_right_frames[i] = load_image( GC_pac_man_right_frames[i], GC_block_size, GC_block_size );

    for ( i = 0; i < GC_NPC_frames; i++ )
        p_temp_npc->NPC_down_frames[i] = load_image( GC_pac_man_down_frames[i], GC_block_size, GC_block_size );

    for ( i = 0; i < GC_NPC_frames; i++ )
        p_temp_npc->NPC_left_frames[i] = load_image( GC_pac_man_left_frames[i], GC_block_size, GC_block_size );

    // set the first frame to be active
    p_temp_npc->up_frame_index    = 0;
    p_temp_npc->right_frame_index = 0;
    p_temp_npc->down_frame_index  = 0;
    p_temp_npc->left_frame_index  = 0;

    p_temp_npc->left = _xInMatrix * GC_block_size;

    p_temp_npc->top = _yInMatrix * GC_block_size + GC_y_offset;

    p_temp_npc->direction = rand() % 4;

    p_temp_npc->alive = 1;

    // initalize NPC artificial inteligence
    // p_temp_npc->p_NPC_AI = NPC_random_walk_AI;

    p_temp_npc->walk_timer  = create_timer( GC_NPC_walk_duration );

    p_temp_npc->AI_timer    = create_timer( GC_NPC_AI_delay );

    p_temp_npc->frame_timer = create_timer( GC_NPC_frames_duration );

    return p_temp_npc;
}


void destroy_NPC( NPC* _pNPC )
{
    if ( _pNPC )
    {
        for ( int i = 0; i < GC_NPC_frames; i++ )
            unload_image( _pNPC->NPC_up_frames[i] );

        destroy_timer( _pNPC->walk_timer  );
        destroy_timer( _pNPC->AI_timer    );
        destroy_timer( _pNPC->frame_timer );

        free( _pNPC->NPC_up_frames );

        free( _pNPC );
        _pNPC = NULL;
    }
}


void render_NPC( NPC* _pNPC )
{
    if ( !_pNPC->alive )
        return;
    else
    {
        //draw_image( _pNPC->NPC_up_frames[_pNPC[i]->up_frame_index], _pNPC->x_in_pixels, _pNPC->y_in_pixels );
    }
}


void render_NPCs( NPC** _NPCs, int _NPCCount )
{
    update_NPCs_frames( _NPCs, _NPCCount );

    int i;
    for ( i = 0; i < _NPCCount; i++ )
    {
        if ( !_NPCs[i]->alive )
            continue;
        else
        {
            switch( _NPCs[i]->direction )
            {
                case UP:
                {
                    draw_image( _NPCs[i]->NPC_up_frames[_NPCs[i]->up_frame_index], _NPCs[i]->left, _NPCs[i]->top );
                    break;
                }

                case RIGHT:
                {
                    draw_image( _NPCs[i]->NPC_right_frames[_NPCs[i]->right_frame_index], _NPCs[i]->left, _NPCs[i]->top );
                    break;
                }

                case DOWN:
                {
                    draw_image( _NPCs[i]->NPC_down_frames[_NPCs[i]->down_frame_index], _NPCs[i]->left, _NPCs[i]->top );
                    break;
                }

                case LEFT:
                {
                    draw_image( _NPCs[i]->NPC_left_frames[_NPCs[i]->left_frame_index], _NPCs[i]->left, _NPCs[i]->top );
                    break;
                }
            }
        }
    }
}


void update_NPCs_frames( NPC** _NPCs, int _NPCCount )
{
    int i;
    for ( i = 0; i < _NPCCount; i++ )
    {
        if ( time_left( _NPCs[i]->frame_timer ) <= GC_NPC_frames_duration / 3.0 )  // 1st frame
        {
            switch( _NPCs[i]->direction )
            {
                case UP:
                {
                    _NPCs[i]->up_frame_index = 0;
                    break;
                }

                case RIGHT:
                {
                    _NPCs[i]->right_frame_index = 0;
                    break;
                }

                case DOWN:
                {
                    _NPCs[i]->down_frame_index = 0;
                    break;
                }

                case LEFT:
                {
                    _NPCs[i]->left_frame_index = 0;
                    break;
                }
            }
        }
        else if ( time_left( _NPCs[i]->frame_timer ) <= 2.0 * GC_NPC_frames_duration / 3.0 )   // 2nd frame
        {
            switch( _NPCs[i]->direction )
            {
                case UP:
                {
                    _NPCs[i]->up_frame_index = 1;
                    break;
                }

                case RIGHT:
                {
                    _NPCs[i]->right_frame_index = 1;
                    break;
                }

                case DOWN:
                {
                    _NPCs[i]->down_frame_index = 1;
                    break;
                }

                case LEFT:
                {
                    _NPCs[i]->left_frame_index = 1;
                    break;
                }
            }
        }
        else    // 3rd frame
        {
            switch( _NPCs[i]->direction )
            {
                case UP:
                {
                    _NPCs[i]->up_frame_index = 2;
                    break;
                }

                case RIGHT:
                {
                    _NPCs[i]->right_frame_index = 2;
                    break;
                }

                case DOWN:
                {
                    _NPCs[i]->down_frame_index = 2;
                    break;
                }

                case LEFT:
                {
                    _NPCs[i]->left_frame_index = 2;
                    break;
                }
            }
        }

        if ( time_is_up( _NPCs[i]->frame_timer ) )
            reset_timer( _NPCs[i]->frame_timer );
    }
}


void update_NPCs( NPC** _NPCs, int _NPCCount, bomb* _pBomb, map* _pMap )
{
    // loop through all NPCs
    int i;
    for ( i = 0; i < _NPCCount; i++ )
    {
        // update NPC's coordinates atributes
        _NPCs[i]->right  = _NPCs[i]->left + GC_block_size;
        _NPCs[i]->bottom = _NPCs[i]->top  + GC_block_size;

        _NPCs[i]->i = ( ( (_NPCs[i]->top + GC_block_size/2) - GC_y_offset) / GC_block_size );
        _NPCs[i]->j = ( (_NPCs[i]->left + GC_block_size/2) / GC_block_size );

        // invoke NPC's artificial intelligence, but not every loop
        // delay the artificial intelligence, it mustn't run each loop
        if ( time_is_up( _NPCs[i]->AI_timer ) )
        {
            //_NPCs[i]->p_NPC_AI( _pGame );

            NPC_random_walk_AI( _NPCs[i], _pBomb, _NPCs, _NPCCount, _pMap );

            reset_timer( _NPCs[i]->AI_timer );
        }
        else
        {
            // delay the NPC's walk
            if ( time_is_up( _NPCs[i]->walk_timer ) )
            {
                NPC_walk( _NPCs[i], _pBomb, _NPCs, _NPCCount, _pMap, _NPCs[i]->direction );

                reset_timer( _NPCs[i]->walk_timer );
            }
        }
    }
}


void NPC_walk(  NPC* _pNPC, bomb* _pBomb, NPC** _NPCs, int _NPCCount, map* _pMap, int _dir )
{
    if ( NPC_can_walk( _pNPC, _pBomb, _NPCs, _NPCCount, _pMap, _dir ) )
    {
        switch ( _dir )
        {
            case UP:
            {
                _pNPC->top -= GC_NPC_walk_dist;
                break;
            }

            case RIGHT:
            {
                _pNPC->left += GC_NPC_walk_dist;
                break;
            }

            case DOWN:
            {
                _pNPC->top += GC_NPC_walk_dist;
                break;
            }

            case LEFT:
            {
                _pNPC->left -= GC_NPC_walk_dist;
                break;
            }
        }
    }
}


int NPC_can_walk( NPC* _pNPC, bomb* _pBomb, NPC** _NPCs, int _NPCCount, map* _pMap, int _dir )
{
    // NPC's collide with the map, with other NPCs(not yet) and with the bomb
    switch ( _dir )
    {
        case UP:
        {
            // change NPC direction even if he can't walk
            _pNPC->direction = UP;

            // check if upwards square is a destructible or undestructible block which means NPC can't walk there
            int upwards_square_is_blocked = ( _pMap->map_data[_pNPC->i - 1][_pNPC->j].block_type == DESTRUCTIBLE_BLOCK ||
                _pMap->map_data[_pNPC->i - 1][_pNPC->j].block_type == INDESTRUCTIBLE_BLOCK ) ? 1 : 0;

            int upwards_square_has_bomb = ( (_pNPC->i - 1) == _pBomb->i ) && ( _pNPC->j == _pBomb->j ) ? 1 : 0;

            // if upwards block is des/indes then check if NPC is colliding with or touching upwards block if he isn't, he can walk up
            if ( upwards_square_is_blocked )
            {
                rect NPC    = { _pNPC->left, _pNPC->top, _pNPC->right, _pNPC->bottom };

                rect block  = { _pMap->map_data[_pNPC->i - 1][_pNPC->j].left,
                                _pMap->map_data[_pNPC->i - 1][_pNPC->j].top,
                                _pMap->map_data[_pNPC->i - 1][_pNPC->j].right,
                                _pMap->map_data[_pNPC->i - 1][_pNPC->j].bottom };

                if ( collides( NPC, block ) || touches( NPC, block ) )
                    return 0;
                else
                    return 1;
            }
            else if ( upwards_square_has_bomb && _pBomb->active )
            {
                rect NPC  = { _pNPC->left, _pNPC->top, _pNPC->right, _pNPC->bottom };

                rect bomb = { _pBomb->left, _pBomb->top, _pBomb->right, _pBomb->bottom };

                if ( collides( NPC, bomb ) || touches( NPC, bomb ) )
                    return 0;
                else
                    return 1;

            }
            else
            {
                // left allign NPC if he already isn't
                _pNPC->left = _pMap->map_data[_pNPC->i][_pNPC->j].left;
                return 1;
            }

            break;
        }

        case RIGHT:
        {
            // change NPC direction even if he can't walk
            _pNPC->direction = RIGHT;

            // check if rightmost square is a destructible or undestructible block which means NPC can't walk there
            int rightmost_square_is_blocked = ( _pMap->map_data[_pNPC->i][_pNPC->j + 1].block_type == DESTRUCTIBLE_BLOCK ||
                _pMap->map_data[_pNPC->i][_pNPC->j + 1].block_type == INDESTRUCTIBLE_BLOCK ) ? 1 : 0;

            int rightmost_square_has_bomb = ( _pNPC->i == _pBomb->i ) && ( (_pNPC->j + 1) == _pBomb->j ) ? 1 : 0;

            if ( rightmost_square_is_blocked )
            {
                rect NPC = { _pNPC->left, _pNPC->top, _pNPC->right, _pNPC->bottom };

                rect block  = { _pMap->map_data[_pNPC->i][_pNPC->j + 1].left,
                                _pMap->map_data[_pNPC->i][_pNPC->j + 1].top,
                                _pMap->map_data[_pNPC->i][_pNPC->j + 1].right,
                                _pMap->map_data[_pNPC->i][_pNPC->j + 1].bottom };

                if ( collides( NPC, block ) || touches( NPC, block ) )
                    return 0;
                else
                    return 1;
            }
            else if ( rightmost_square_has_bomb && _pBomb->active )
            {
                rect NPC  = { _pNPC->left, _pNPC->top, _pNPC->right, _pNPC->bottom };

                rect bomb = { _pBomb->left, _pBomb->top, _pBomb->right, _pBomb->bottom };

                if ( collides( NPC, bomb ) || touches( NPC, bomb ) )
                    return 0;
                else
                    return 1;

            }
            else
            {
                // top allign NPC if he already isn't
                _pNPC->top = _pMap->map_data[_pNPC->i][_pNPC->j].top;
                return 1;
            }

            break;
        }

        case DOWN:
        {
            // change NPC direction even if he can't walk
            _pNPC->direction = DOWN;

            // check if downwards square is a destructible or undestructible block which means NPC can't walk there
            int downwards_square_is_blocked = ( _pMap->map_data[_pNPC->i + 1][_pNPC->j].block_type == DESTRUCTIBLE_BLOCK ||
                _pMap->map_data[_pNPC->i + 1][_pNPC->j].block_type == INDESTRUCTIBLE_BLOCK ) ? 1 : 0;

            int downwards_square_has_bomb = ( (_pNPC->i + 1) == _pBomb->i ) && ( _pNPC->j == _pBomb->j ) ? 1 : 0;


            if ( downwards_square_is_blocked )
            {
                rect NPC = { _pNPC->left, _pNPC->top, _pNPC->right, _pNPC->bottom };

                rect block  = { _pMap->map_data[_pNPC->i + 1][_pNPC->j].left,
                                _pMap->map_data[_pNPC->i + 1][_pNPC->j].top,
                                _pMap->map_data[_pNPC->i + 1][_pNPC->j].right,
                                _pMap->map_data[_pNPC->i + 1][_pNPC->j].bottom };

                if ( collides( NPC, block ) || touches( NPC, block ) )
                    return 0;
                else
                    return 1;
            }
            else if ( downwards_square_has_bomb && _pBomb->active )
            {
                rect NPC  = { _pNPC->left, _pNPC->top, _pNPC->right, _pNPC->bottom };

                rect bomb = { _pBomb->left, _pBomb->top, _pBomb->right, _pBomb->bottom };

                if ( collides( NPC, bomb ) || touches( NPC, bomb ) )
                    return 0;
                else
                    return 1;

            }
            else
            {
                // left allign NPC if he already isn't
                _pNPC->left = _pMap->map_data[_pNPC->i][_pNPC->j].left;
                return 1;
            }

            break;
        }

        case LEFT:
        {
            // change NPC direction even if he can't walk
            _pNPC->direction = LEFT;

            // check if leftmost square is a destructible or undestructible block which means NPC can't walk there
            int leftmost_square_is_blocked = ( _pMap->map_data[_pNPC->i][_pNPC->j - 1].block_type == DESTRUCTIBLE_BLOCK ||
                _pMap->map_data[_pNPC->i][_pNPC->j - 1].block_type == INDESTRUCTIBLE_BLOCK ) ? 1 : 0;

            int leftmost_square_has_bomb = ( _pNPC->i == _pBomb->i ) && ( (_pNPC->j - 1) == _pBomb->j ) ? 1 : 0;

            if ( leftmost_square_is_blocked )
            {
                rect NPC = { _pNPC->left, _pNPC->top, _pNPC->right, _pNPC->bottom };

                rect block  = { _pMap->map_data[_pNPC->i][_pNPC->j - 1].left,
                                _pMap->map_data[_pNPC->i][_pNPC->j - 1].top,
                                _pMap->map_data[_pNPC->i][_pNPC->j - 1].right,
                                _pMap->map_data[_pNPC->i][_pNPC->j - 1].bottom };

                if ( collides( NPC, block ) || touches( NPC, block ) )
                    return 0;
                else
                    return 1;
            }
            else if ( leftmost_square_has_bomb && _pBomb->active )
            {
                rect NPC  = { _pNPC->left, _pNPC->top, _pNPC->right, _pNPC->bottom };

                rect bomb = { _pBomb->left, _pBomb->top, _pBomb->right, _pBomb->bottom };

                if ( collides( NPC, bomb ) || touches( NPC, bomb ) )
                    return 0;
                else
                    return 1;

            }
            else
            {
                // top allign NPC if he already isn't
                _pNPC->top = _pMap->map_data[_pNPC->i][_pNPC->j].top;
                return 1;
            }

            break;
        }
    }
}


void NPC_random_walk_AI( NPC* _pNPC, bomb* _pBomb, NPC** _NPCs, int _NPCCount, map* _pMap )
{
    int NPC_can_walk_up    = NPC_can_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, UP );
    int NPC_can_walk_right = NPC_can_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, RIGHT );
    int NPC_can_walk_down  = NPC_can_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, DOWN );
    int NPC_can_walk_left  = NPC_can_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, LEFT );

    if ( NPC_can_walk_up )
    {
        if ( NPC_can_walk_right )
        {
            if ( NPC_can_walk_down )
            {
                if ( NPC_can_walk_left )
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, rand() % 4 );
                }
                else
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, rand() % 3 );
                }
            }
            else
            {
                if ( NPC_can_walk_left )
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, return_random_argument( 3, UP, RIGHT, LEFT ) );
                }
                else
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, rand() % 2 );
                }
            }
        }
        else
        {
            if ( NPC_can_walk_down )
            {
                if ( NPC_can_walk_left )
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, return_random_argument( 3, UP, DOWN, LEFT ) );
                }
                else
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, return_random_argument( 2, UP, DOWN ) );
                }
            }
            else
            {
                if ( NPC_can_walk_left )
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, return_random_argument( 2, UP, LEFT ) );
                }
                else
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, UP );
                }
            }
        }
    }
    else
    {
        if ( NPC_can_walk_right )
        {
            if ( NPC_can_walk_down )
            {
                if ( NPC_can_walk_left )
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, rand() % 3 + 1 );
                }
                else
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, return_random_argument( 2, RIGHT, DOWN ) );
                }
            }
            else
            {
                if ( NPC_can_walk_left )
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, return_random_argument( 2, RIGHT, LEFT ) );
                }
                else
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, RIGHT );
                }
            }
        }
        else
        {
            if ( NPC_can_walk_down )
            {
                if ( NPC_can_walk_left )
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, rand() % 2 + 2 );
                }
                else
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, DOWN );
                }
            }
            else
            {
                if ( NPC_can_walk_left )
                {
                    NPC_walk( (NPC*)_pNPC, (bomb*)_pBomb, (NPC**)_NPCs, _NPCCount, (map*)_pMap, LEFT );
                }
                else
                {
                    ; // can't go anywhere
                }
            }
        }
    }
}

/*      First AI I wrote, all NPCs tended, after some time, to walk only on the borders of the map.

switch( (NPC*)_pNPC->direction )
{
    case UP:
    {
        if ( NPC_can_walk( (NPC*)_pNPC, (map*)_pMap, UP ) )
            NPC_walk( (NPC*)_pNPC, UP );
        else
            ((NPC*)_pNPC)->direction = rand() % 4;

        break;
    }


    case RIGHT:
    {
        if ( NPC_can_walk( (NPC*)_pNPC, (map*)_pMap, RIGHT ) )
            NPC_walk( (NPC*)_pNPC, RIGHT );
        else
            ((NPC*)_pNPC)->direction = rand() % 4;

        break;
    }

    case DOWN:
    {
        if ( NPC_can_walk( (NPC*)_pNPC, (map*)_pMap, DOWN ) )
            NPC_walk( (NPC*)_pNPC, DOWN );
        else
            ((NPC*)_pNPC)->direction = rand() % 4;

        break;
    }

    case LEFT:
    {
        if ( NPC_can_walk( (NPC*)_pNPC, (map*)_pMap, LEFT ) )
            NPC_walk( (NPC*)_pNPC, LEFT );
        else
            ((NPC*)_pNPC)->direction = rand() % 4;

        break;
    }
}

*/
