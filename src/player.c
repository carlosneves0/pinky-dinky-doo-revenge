

#include "game.h"
#include "player.h"


player* construct_player()
{
    // allocate memory for the player struct
    player* p_temp_player = (player*)malloc( sizeof( player ) );

    // load the images of the player's 4 frames
    p_temp_player->p_up_img    = load_image( GC_player_up_img, GC_block_size, GC_block_size );
    p_temp_player->p_right_img = load_image( GC_player_right_img, GC_block_size, GC_block_size );
    p_temp_player->p_down_img  = load_image( GC_player_down_img, GC_block_size, GC_block_size );
    p_temp_player->p_left_img  = load_image( GC_player_left_img, GC_block_size, GC_block_size );

    p_temp_player->p_dead_by_pac_man_img   = load_image( GC_player_dead_by_pac_man_img, GC_block_size, GC_block_size );
    p_temp_player->p_dead_by_explosion_img = load_image( GC_player_dead_by_explosion_img, GC_block_size, GC_block_size );

    // set player initial postion in the matrix map to be (1,1)
    p_temp_player->left = 1 * GC_block_size;
    p_temp_player->top  = 1 * GC_block_size + GC_y_offset;

    // set player inital direction to right and set walk_counter to anything bigger than 4 so player won't start walking right
    p_temp_player->direction    = RIGHT;

    // initalize some player's info
    p_temp_player->alive = 1;
    p_temp_player->num_lives      = GC_player_num_lives;

    p_temp_player->how_many_bombs = 1;

    p_temp_player->p_bomb = construct_bomb();

    return p_temp_player;
}


void destroy_player( player* _pPlayer )
{
    if ( _pPlayer )
    {
        unload_image( _pPlayer->p_up_img    );
        unload_image( _pPlayer->p_right_img );
        unload_image( _pPlayer->p_down_img  );
        unload_image( _pPlayer->p_left_img  );
        unload_image( _pPlayer->p_dead_by_pac_man_img  );

        destroy_bomb( _pPlayer->p_bomb );

        free( _pPlayer );
        _pPlayer = NULL;
    }
}


void render_player( player* _pPlayer )
{
    if ( !_pPlayer->alive )
    {
        switch( _pPlayer->cause_of_death )
        {
            case DEATH_BY_PAC_MAN:
            {
                draw_image( _pPlayer->p_dead_by_pac_man_img, _pPlayer->left, _pPlayer->top );
                break;
            }

            case DEATH_BY_EXPLOSION:
            {
                draw_image( _pPlayer->p_dead_by_explosion_img, _pPlayer->left, _pPlayer->top );
                break;
            }
        }

        return;
    }

    switch ( _pPlayer->direction )
    {
        case UP:
        {
            draw_image( _pPlayer->p_up_img, _pPlayer->left, _pPlayer->top );

            break;
        }

        case RIGHT:
        {
            draw_image( _pPlayer->p_right_img, _pPlayer->left, _pPlayer->top );

            break;
        }

        case DOWN:
        {
            draw_image( _pPlayer->p_down_img, _pPlayer->left, _pPlayer->top );

            break;
        }

        case LEFT:
        {
            draw_image( _pPlayer->p_left_img, _pPlayer->left, _pPlayer->top );

            break;
        }
    }
}


void update_player( player* _pPlayer )
{
    // update player's coordinates in the map matrix and also it's right and bottom coordinates in pixels in the screen
    _pPlayer->right  = _pPlayer->left + GC_block_size;
    _pPlayer->bottom = _pPlayer->top  + GC_block_size;

    _pPlayer->i = ( ( (_pPlayer->top + GC_block_size/2) - GC_y_offset) / GC_block_size );
    _pPlayer->j = ( (_pPlayer->left + GC_block_size/2) / GC_block_size );
}


void player_walk( player* _pPlayer, map* _pMap, int _dir )
{
    if ( player_can_walk( _pPlayer, _pMap, _dir ) )
    {
        switch ( _dir )
        {
            case UP:
            {
                _pPlayer->top -= GC_player_walk_dist;
                break;
            }

            case RIGHT:
            {
                _pPlayer->left += GC_player_walk_dist;
                break;
            }

            case DOWN:
            {
                _pPlayer->top += GC_player_walk_dist;
                break;
            }

            case LEFT:
            {
                _pPlayer->left -= GC_player_walk_dist;
                break;
            }
        }
    }
}


int player_can_walk( player* _pPlayer, map* _pMap, int _dir )
{
    switch ( _dir )
    {
        case UP:
        {
            // change player direction even if he can't walk
            _pPlayer->direction = UP;

            // check if upwards square is a destructible or undestructible block which means player can't walk there
            int upwards_square_is_blocked = ( _pMap->map_data[_pPlayer->i - 1][_pPlayer->j].block_type == DESTRUCTIBLE_BLOCK ||
                _pMap->map_data[_pPlayer->i - 1][_pPlayer->j].block_type == INDESTRUCTIBLE_BLOCK ) ? 1 : 0;

            // if upwards block is des/indes then check if player is colliding with or touching upwards block if he isn't, he can walk up
            if ( upwards_square_is_blocked )
            {
                rect player = { _pPlayer->left, _pPlayer->top, _pPlayer->right, _pPlayer->bottom };

                rect block  = { _pMap->map_data[_pPlayer->i - 1][_pPlayer->j].left,
                                _pMap->map_data[_pPlayer->i - 1][_pPlayer->j].top,
                                _pMap->map_data[_pPlayer->i - 1][_pPlayer->j].right,
                                _pMap->map_data[_pPlayer->i - 1][_pPlayer->j].bottom };

                if ( collides( player, block ) || touches( player, block ) )
                    return 0;
                else
                    return 1;
            }
            else
            {
                // left allign player if he already isn't
                _pPlayer->left = _pMap->map_data[_pPlayer->i][_pPlayer->j].left;
                return 1;
            }

            break;
        }

        case RIGHT:
        {
            // change player direction even if he can't walk
            _pPlayer->direction = RIGHT;

            // check if rightmost square is a destructible or undestructible block which means player can't walk there
            int rightmost_square_is_blocked = ( _pMap->map_data[_pPlayer->i][_pPlayer->j + 1].block_type == DESTRUCTIBLE_BLOCK ||
                _pMap->map_data[_pPlayer->i][_pPlayer->j + 1].block_type == INDESTRUCTIBLE_BLOCK ) ? 1 : 0;

            if ( rightmost_square_is_blocked )
            {
                rect player = { _pPlayer->left, _pPlayer->top, _pPlayer->right, _pPlayer->bottom };

                rect block  = { _pMap->map_data[_pPlayer->i][_pPlayer->j + 1].left,
                                _pMap->map_data[_pPlayer->i][_pPlayer->j + 1].top,
                                _pMap->map_data[_pPlayer->i][_pPlayer->j + 1].right,
                                _pMap->map_data[_pPlayer->i][_pPlayer->j + 1].bottom };

                if ( collides( player, block ) || touches( player, block ) )
                    return 0;
                else
                    return 1;
            }
            else
            {
                // top allign player if he already isn't
                _pPlayer->top = _pMap->map_data[_pPlayer->i][_pPlayer->j].top;
                return 1;
            }

            break;
        }

        case DOWN:
        {
            // change player direction even if he can't walk
            _pPlayer->direction = DOWN;

            // check if downwards square is a destructible or undestructible block which means player can't walk there
            int downwards_square_is_blocked = ( _pMap->map_data[_pPlayer->i + 1][_pPlayer->j].block_type == DESTRUCTIBLE_BLOCK ||
                _pMap->map_data[_pPlayer->i + 1][_pPlayer->j].block_type == INDESTRUCTIBLE_BLOCK ) ? 1 : 0;


            if ( downwards_square_is_blocked )
            {
                rect player = { _pPlayer->left, _pPlayer->top, _pPlayer->right, _pPlayer->bottom };

                rect block  = { _pMap->map_data[_pPlayer->i + 1][_pPlayer->j].left,
                                _pMap->map_data[_pPlayer->i + 1][_pPlayer->j].top,
                                _pMap->map_data[_pPlayer->i + 1][_pPlayer->j].right,
                                _pMap->map_data[_pPlayer->i + 1][_pPlayer->j].bottom };

                if ( collides( player, block ) || touches( player, block ) )
                    return 0;
                else
                    return 1;
            }
            else
            {
                // left allign player if he already isn't
                _pPlayer->left = _pMap->map_data[_pPlayer->i][_pPlayer->j].left;
                return 1;
            }

            break;
        }

        case LEFT:
        {
            // change player direction even if he can't walk
            _pPlayer->direction = LEFT;

            // check if leftmost square is a destructible or undestructible block which means player can't walk there
            int leftmost_square_is_blocked = ( _pMap->map_data[_pPlayer->i][_pPlayer->j - 1].block_type == DESTRUCTIBLE_BLOCK ||
                _pMap->map_data[_pPlayer->i][_pPlayer->j - 1].block_type == INDESTRUCTIBLE_BLOCK ) ? 1 : 0;

            if ( leftmost_square_is_blocked )
            {
                rect player = { _pPlayer->left, _pPlayer->top, _pPlayer->right, _pPlayer->bottom };

                rect block  = { _pMap->map_data[_pPlayer->i][_pPlayer->j - 1].left,
                                _pMap->map_data[_pPlayer->i][_pPlayer->j - 1].top,
                                _pMap->map_data[_pPlayer->i][_pPlayer->j - 1].right,
                                _pMap->map_data[_pPlayer->i][_pPlayer->j - 1].bottom };

                if ( collides( player, block ) || touches( player, block ) )
                    return 0;
                else
                    return 1;
            }
            else
            {
                // top allign player if he already isn't
                _pPlayer->top = _pMap->map_data[_pPlayer->i][_pPlayer->j].top;
                return 1;
            }

            break;
        }
    }
}


void player_drop_bomb( void* _pVoidGame )
{
    player* p_player = ((in_game_state*)((game*)_pVoidGame)->p_current_state)->p_player;

    if ( !p_player->p_bomb->active )
    {
        p_player->p_bomb->left   = p_player->j * GC_block_size;

        p_player->p_bomb->top    = p_player->i * GC_block_size + GC_y_offset;

        p_player->p_bomb->right  = p_player->p_bomb->left + GC_block_size;

        p_player->p_bomb->bottom = p_player->p_bomb->top  + GC_block_size;

        p_player->p_bomb->i = p_player->i;

        p_player->p_bomb->j = p_player->j;

        p_player->p_bomb->active = 1;

        explode( _pVoidGame );

        pause_audio();

        play_sound( GC_bomb_sound );

        reset_timer( p_player->p_bomb->bomb_timer );
    }
}
