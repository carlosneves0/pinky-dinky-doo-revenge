

#include "game.h"
#include "bomb.h"


bomb* construct_bomb()
{
    bomb* p_temp_bomb = (bomb*)malloc( sizeof( bomb ) );

    p_temp_bomb->left = -32;
    p_temp_bomb->top = -32;

    p_temp_bomb->range   = GC_explosion_range;
    p_temp_bomb->explode = 0;
    p_temp_bomb->active  = 0;

    p_temp_bomb->p_blocks_that_will_explode = NULL;  // i,j coordinates in map's matrix
    p_temp_bomb->blocks_count = 0;

    p_temp_bomb->bomb_img = load_image( GC_bomb_img, GC_block_size, GC_block_size );

    // load explosion frames images
    p_temp_bomb->explosion_frames = (void**)malloc( GC_bomb_explosion_frames_num * sizeof( void* ) );

    int i;
    for ( i = 0; i < GC_bomb_explosion_frames_num; i++ )
        p_temp_bomb->explosion_frames[i] = load_image( GC_bomb_explosion_frames[i], GC_block_size, GC_block_size );

    p_temp_bomb->bomb_timer = create_timer( GC_bomb_duration );

    p_temp_bomb->explosion_timer = create_timer( GC_explosion_duration );

    return p_temp_bomb;
}


void destroy_bomb( bomb* _pBomb )
{
    if ( _pBomb )
    {
        if ( _pBomb->p_blocks_that_will_explode )
        {
            free( _pBomb->p_blocks_that_will_explode );
            _pBomb->p_blocks_that_will_explode = NULL;
        }

        unload_image( _pBomb->bomb_img );

        int i;
        for ( i = 0; i < GC_bomb_explosion_frames_num; i++ )
            unload_image( _pBomb->explosion_frames[i] );

        free ( _pBomb->explosion_frames );

        destroy_timer( _pBomb->bomb_timer );
        destroy_timer( _pBomb->explosion_timer );

        free( _pBomb );
        _pBomb = NULL;
    }
}


void render_bomb( bomb* _pBomb )
{
    if ( _pBomb->active && !time_is_up( _pBomb->bomb_timer ) )
    {
        draw_image( _pBomb->bomb_img, _pBomb->left, _pBomb->top );

        _pBomb->explode  = 1;
    }
}


void render_explosion( bomb* _pBomb, map* _pMap, void* _pVoidPlayer, void** _voidNPCs, int _NPCCount )
{
    if ( time_is_up( _pBomb->bomb_timer ) )
    {
        if ( _pBomb->explode )
        {
            play_sound( GC_explosion_sound );
            reset_timer( _pBomb->explosion_timer );
        }

        int explosion_frame = (int)(time_left( _pBomb->explosion_timer ) * 5.0 ) - 1;

        if ( explosion_frame < 0 )  // means explosion ended
        {
            _pBomb->active = 0;
            return;
        }

        if ( !time_is_up( _pBomb->explosion_timer ) )
        {
            // render explosion animation
            int i;
            for ( i = 0; i < _pBomb->blocks_count; i++ )
            {
                int x_in_pixels = _pBomb->p_blocks_that_will_explode[i].j * GC_block_size;
                int y_in_pixels = _pBomb->p_blocks_that_will_explode[i].i * GC_block_size + GC_y_offset;
                draw_image( _pBomb->explosion_frames[explosion_frame], x_in_pixels, y_in_pixels );
            }

            // update map
            explode_destructibles( _pBomb, _pMap );

            // kill NPCs and/or player if affected by the explosion
            explode_NPCs( _pBomb, _voidNPCs, _NPCCount );

            explode_player( _pBomb, _pVoidPlayer );
        }

        _pBomb->explode = 0;
    }
}


// explode calculates which blocks will explode and takes care of the vector of matrix_point's
void explode( void* _pVoidGame )
{
    bomb*   p_bomb    = ((in_game_state*)((game*)_pVoidGame)->p_current_state)->p_player->p_bomb;
    map*    p_map     = ((in_game_state*)((game*)_pVoidGame)->p_current_state)->p_map;

    // check if p_blocks_that_will_explode already points to something
    // if it does point to something, this means it points to outdated information
    if ( p_bomb->p_blocks_that_will_explode )
    {
        free( p_bomb->p_blocks_that_will_explode );
        p_bomb->p_blocks_that_will_explode = NULL;
    }

    // allocate a vector of matrix_point's with the maximum number of blocks that can explode at a time:
    //            (4 directions) times (explosion_range) plus (1 center block) == 13 if range == 3
    // this vector will, when this function return, hold the coordinates of the points in the map matrix that will explode
    p_bomb->p_blocks_that_will_explode = (matrix_point*)malloc( (4 * p_bomb->range + 1) * sizeof( matrix_point ) );

    p_bomb->blocks_count = 0;

    int bomb_i_in_matrix = ( ( (p_bomb->top + GC_block_size/2) - GC_y_offset) / GC_block_size );
    int bomb_j_in_matrix = ( (p_bomb->left + GC_block_size/2) / GC_block_size );

    // center block will always be empty, cause that's the only place where the player can walk on to drop the bomb, so add center block to matrix_point's vector
    p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count  ].i = bomb_i_in_matrix;
    p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count++].j = bomb_j_in_matrix;

    // checking first direction: UP
    int i, j;
    for ( i = (bomb_i_in_matrix - 1), j = bomb_j_in_matrix; i > bomb_i_in_matrix - p_bomb->range; i-- )
    {
        // do not go further than the matrix allows
        if ( i < 0 )
            break;

        if ( p_map->map_data[i][j].block_type == INDESTRUCTIBLE_BLOCK ) // stop here, cause explosions stop at indestructible_blocks
            break;
        else if (  p_map->map_data[i][j].block_type == DESTRUCTIBLE_BLOCK ) // explode block and stop the explosion here
        {
            // add block to matrix_point's vector
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count  ].i = i;
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count++].j = j;

            // stop explosion from going up, break the for loop
            break;
        }
        else // all toher block types are explodables and don't stop the explosion
        {
            // add block to matrix_point's vector
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count  ].i = i;
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count++].j = j;
        }
    }

    // checking second direction: RIGHT
    for ( i = bomb_i_in_matrix, j = (bomb_j_in_matrix + 1); j < bomb_j_in_matrix + p_bomb->range; j++ )
    {
        // do not go further than the matrix allows
        if ( j == GC_map_col )
            break;

        if ( p_map->map_data[i][j].block_type == INDESTRUCTIBLE_BLOCK ) // stop here, cause explosions stop at indestructible_blocks
            break;
        else if (  p_map->map_data[i][j].block_type == DESTRUCTIBLE_BLOCK ) // explode block and stop the explosion here
        {
            // add block to matrix_point's vector
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count  ].i = i;
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count++].j = j;

            // stop explosion from going right, break the for loop
            break;
        }
        else // all toher block types are explodables and don't stop the explosion
        {
            // add block to matrix_point's vector
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count  ].i = i;
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count++].j = j;
        }
    }

    // checking second direction: DOWN
    for ( i = (bomb_i_in_matrix + 1), j = bomb_j_in_matrix; i < bomb_i_in_matrix + p_bomb->range; i++ )
    {
        // do not go further than the matrix allows
        if ( i == GC_map_lin )
            break;

        if ( p_map->map_data[i][j].block_type == INDESTRUCTIBLE_BLOCK ) // stop here, cause explosions stop at indestructible_blocks
            break;
        else if (  p_map->map_data[i][j].block_type == DESTRUCTIBLE_BLOCK ) // explode block and stop the explosion here
        {
            // add block to matrix_point's vector
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count  ].i = i;
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count++].j = j;

            // stop explosion from going down, break the for loop
            break;
        }
        else // all toher block types are explodables and don't stop the explosion
        {
            // add block to matrix_point's vector
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count  ].i = i;
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count++].j = j;
        }
    }

    // checking second direction: LEFT
    for ( i = bomb_i_in_matrix, j = (bomb_j_in_matrix - 1); j > bomb_j_in_matrix - p_bomb->range; j-- )
    {
        // do not go further than the matrix allows
        if ( j < 0 )
            break;

        if ( p_map->map_data[i][j].block_type == INDESTRUCTIBLE_BLOCK ) // stop here, cause explosions stop at indestructible_blocks
            break;
        else if (  p_map->map_data[i][j].block_type == DESTRUCTIBLE_BLOCK ) // explode block and stop the explosion here
        {
            // add block to matrix_point's vector
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count  ].i = i;
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count++].j = j;

            //stop explosion from going left, break the for loop
            break;
        }
        else // all toher block types are explodables and don't stop the explosion
        {
            // add block to matrix_point's vector
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count  ].i = i;
            p_bomb->p_blocks_that_will_explode[p_bomb->blocks_count++].j = j;
        }
    }
}


void explode_destructibles( bomb* _pBomb, map* _pMap  )
{
    int i;
    for ( i = 0; i < _pBomb->blocks_count; i++ )
    {
        int i_in_matrix = _pBomb->p_blocks_that_will_explode[i].i;
        int j_in_matrix = _pBomb->p_blocks_that_will_explode[i].j;

        if ( _pMap->map_data[i_in_matrix][j_in_matrix].block_type == DESTRUCTIBLE_BLOCK )
            _pMap->map_data[i_in_matrix][j_in_matrix].block_type = NULL_BLOCK;
    }
}


void explode_player( bomb* _pBomb, void* _pVoidPlayer )
{
    player* p_player = (player*)_pVoidPlayer;

    int i;
    for ( i = 0; i < _pBomb->blocks_count; i++ )
    {
        rect exploding_i_block = { _pBomb->p_blocks_that_will_explode[i].j * GC_block_size,
                                    _pBomb->p_blocks_that_will_explode[i].i * GC_block_size + GC_y_offset,
                                    _pBomb->p_blocks_that_will_explode[i].j * GC_block_size + GC_block_size,
                                    _pBomb->p_blocks_that_will_explode[i].i * GC_block_size + GC_y_offset + GC_block_size };

        if ( collides( { p_player->left, p_player->top, p_player->right, p_player->bottom }, exploding_i_block ) && p_player->alive )
        {
            p_player->alive = 0;
            p_player->cause_of_death = DEATH_BY_EXPLOSION;
        }
    }
}


void explode_NPCs( bomb* _pBomb, void** _voidNPCs, int _NPCCount )
{
    NPC** NPCs = (NPC**)_voidNPCs;

    int i, n;
    for ( i = 0; i < _pBomb->blocks_count; i++ )
    {
        int i_in_matrix = _pBomb->p_blocks_that_will_explode[i].i;
        int j_in_matrix = _pBomb->p_blocks_that_will_explode[i].j;

        for ( n = 0; n < _NPCCount; n++ )
        {
            if ( NPCs[n]->i == i_in_matrix && NPCs[n]->j == j_in_matrix )
                NPCs[n]->alive = 0;
        }
    }
}
