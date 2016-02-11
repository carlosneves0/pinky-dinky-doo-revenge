

#include "game.h"
#include "state_in_game.h"


void init_in_game_state( game* _pGame )
{
    // allocate the necessary memory for the in_game_state struct
    _pGame->p_current_state = malloc( sizeof( in_game_state ) );

    // game is not paused
    ((in_game_state*)_pGame->p_current_state)->bool_paused = 0;

    // load esc menu image
    ((in_game_state*)_pGame->p_current_state)->p_esc_menu_img = load_image( GC_ig_esc_menu_img, GC_ig_esc_menu_width, GC_ig_esc_menu_height );

    // init current game state flag variable
    ((in_game_state*)_pGame->p_current_state)->game_state = PLAYING;

    // esc menu is not active
    ((in_game_state*)_pGame->p_current_state)->bool_menu_is_active = 0;

    // create the top bar
    ((in_game_state*)_pGame->p_current_state)->p_top_bar = construct_top_bar();

    // load esc menu buttons
    ((in_game_state*)_pGame->p_current_state)->p_continue = load_button( GC_ig_continue_x,
                                                                        GC_ig_continue_y,
                                                                        GC_button_width,
                                                                        GC_button_height,
                                                                        GC_ig_continue_nr_img,
                                                                        GC_ig_continue_se_img );

     ((in_game_state*)_pGame->p_current_state)->p_main_menu = load_button( GC_ig_mm_x,
                                                                          GC_ig_mm_y,
                                                                          GC_button_width,
                                                                          GC_button_height,
                                                                          GC_ig_mm_nr_img,
                                                                          GC_ig_mm_se_img );

    ((in_game_state*)_pGame->p_current_state)->p_exit = load_button( GC_ig_exit_x,
                                                                    GC_ig_exit_y,
                                                                    GC_button_width,
                                                                    GC_button_height,
                                                                    GC_mm_exit_nr_img,
                                                                    GC_mm_exit_se_img );

    // pause main menu backgorund music
    pause_audio();

    _pGame->main_menu_music_is_on = 0;

    // selected button in esc menu is "continue"
    ((in_game_state*)_pGame->p_current_state)->selected_button = CONTINUE_BUTTON;
    ((in_game_state*)_pGame->p_current_state)->p_continue->bool_is_selected = 1;

    // seed the random number generator
    srand( time( NULL ) );

    // construct the map struct, load a random map file from "maps\" directoty
    ((in_game_state*)_pGame->p_current_state)->p_map = construct_map( rand() % GC_number_of_maps );

    // construct the NPCs( pacmen ) based on how many 'N' characters there are in the map( max being GC_max_NPC_count )
    matrix_point* p_NPCs_coords = (matrix_point*)malloc( GC_max_NPC_count * sizeof( matrix_point ) );

    ((in_game_state*)_pGame->p_current_state)->NPC_count = find_NPCs_in_map( ((in_game_state*)_pGame->p_current_state)->p_map, p_NPCs_coords );

    ((in_game_state*)_pGame->p_current_state)->pp_NPCs = (NPC**)malloc( ((in_game_state*)_pGame->p_current_state)->NPC_count * sizeof( NPC ) );

    for ( int i = 0; i < ((in_game_state*)_pGame->p_current_state)->NPC_count; i++ )
        ((in_game_state*)_pGame->p_current_state)->pp_NPCs[i] = construct_NPC( p_NPCs_coords[i].i, p_NPCs_coords[i].j );

    free( p_NPCs_coords );

    // construct the player
    ((in_game_state*)_pGame->p_current_state)->p_player = construct_player();

    ((in_game_state*)_pGame->p_current_state)->game_ended_timer = create_timer( GC_game_ended_duration );

    ((in_game_state*)_pGame->p_current_state)->timer_set = 0;

    // Configure the text that will be outputed(WinBGIm); this is only for the "PAUSED GAME" that appears when game's paused
    settextjustify( CENTER_TEXT, CENTER_TEXT );
    settextstyle( SMALL_FONT, HORIZ_DIR, 9 );
}


void end_in_game_state( game* _pGame )
{
    destroy_top_bar( ((in_game_state*)_pGame->p_current_state)->p_top_bar );

    unload_image( ((in_game_state*)_pGame->p_current_state)->p_esc_menu_img );

    unload_button( ((in_game_state*)_pGame->p_current_state)->p_continue  );
    unload_button( ((in_game_state*)_pGame->p_current_state)->p_main_menu );
    unload_button( ((in_game_state*)_pGame->p_current_state)->p_exit      );

    destroy_map( ((in_game_state*)_pGame->p_current_state)->p_map );

    for ( int i = 0; i < ((in_game_state*)_pGame->p_current_state)->NPC_count; i++ )
        destroy_NPC( ((in_game_state*)_pGame->p_current_state)->pp_NPCs[i] );

    free( ((in_game_state*)_pGame->p_current_state)->pp_NPCs );

    destroy_player( ((in_game_state*)_pGame->p_current_state)->p_player );

    destroy_timer( ((in_game_state*)_pGame->p_current_state)->game_ended_timer );

    free( _pGame->p_current_state );

    _pGame->p_current_state = NULL;
}


void in_game_handle_input( game* _pGame, int _pressedKey )
{
    if ( ((in_game_state*)_pGame->p_current_state)->bool_menu_is_active )
    {
        switch ( _pressedKey )
        {
            case KEY_UP:
            case 'W':
            case 'w':
            {
                // switch selected button( or not if continue button is the one which is selected ):
                if ( ((in_game_state*)_pGame->p_current_state)->selected_button == CONTINUE_BUTTON )
                    ; // do nothing
                else if (  ((in_game_state*)_pGame->p_current_state)->selected_button == MAIN_MENU_BUTTON )
                {
                    ((in_game_state*)_pGame->p_current_state)->selected_button = CONTINUE_BUTTON;
                    ((in_game_state*)_pGame->p_current_state)->p_continue->bool_is_selected  = 1;
                    ((in_game_state*)_pGame->p_current_state)->p_main_menu->bool_is_selected = 0;
                }
                else // EXIT_BUTTON
                {
                    ((in_game_state*)_pGame->p_current_state)->selected_button = MAIN_MENU_BUTTON;
                    ((in_game_state*)_pGame->p_current_state)->p_main_menu->bool_is_selected = 1;
                    ((in_game_state*)_pGame->p_current_state)->p_exit->bool_is_selected      = 0;
                }

                break;
            }

            // player walk down
            case KEY_DOWN:
            case 'S':
            case 's':
            {
                // switch selected button( or not if  exit button is the one which is selected ):
                if ( ((in_game_state*)_pGame->p_current_state)->selected_button == CONTINUE_BUTTON )
                {
                    ((in_game_state*)_pGame->p_current_state)->selected_button = MAIN_MENU_BUTTON;
                    ((in_game_state*)_pGame->p_current_state)->p_continue->bool_is_selected  = 0;
                    ((in_game_state*)_pGame->p_current_state)->p_main_menu->bool_is_selected = 1;
                }
                else if (  ((in_game_state*)_pGame->p_current_state)->selected_button == MAIN_MENU_BUTTON )
                {
                    ((in_game_state*)_pGame->p_current_state)->selected_button = EXIT_BUTTON;
                    ((in_game_state*)_pGame->p_current_state)->p_main_menu->bool_is_selected = 0;
                    ((in_game_state*)_pGame->p_current_state)->p_exit->bool_is_selected      = 1;
                }
                else // EXIT_BUTTON
                    ; // do nothing

                break;
            }

            // KEY_RETURN
            case '\r':
            {
                // continue game, switch current state( to main menu ) or exit game based on which button is selected
                if ( ((in_game_state*)_pGame->p_current_state)->selected_button == CONTINUE_BUTTON )
                {
                    // unpause game if player is alive and deactivate escape menu
                    if ( ((in_game_state*)_pGame->p_current_state)->p_player->alive )
                        ((in_game_state*)_pGame->p_current_state)->bool_paused = !((in_game_state*)_pGame->p_current_state)->bool_paused;
                    ((in_game_state*)_pGame->p_current_state)->bool_menu_is_active = 0;
                }
                else if (  ((in_game_state*)_pGame->p_current_state)->selected_button == MAIN_MENU_BUTTON )
                {
                    switch_to_state( _pGame, MAIN_MENU );
                }
                else // EXIT_BUTTON
                {
                    _pGame->bool_exit = 1; // exit request
                }

                break;
            }

            // Esc menu
            case '\e':
            {
                // unpause game if game is not over == player is alive
                if ( ((in_game_state*)_pGame->p_current_state)->p_player->alive )
                    ((in_game_state*)_pGame->p_current_state)->bool_paused = !((in_game_state*)_pGame->p_current_state)->bool_paused;

                // deactivate escape menu
                ((in_game_state*)_pGame->p_current_state)->bool_menu_is_active = 0;

                break;
            }
        }   // switch
    }
    else
    {
        if ( !((in_game_state*)_pGame->p_current_state)->p_player->alive )
        {
            // Esc menu
            if ( _pressedKey == '\e' )
            {
                // activate the escape menu
                ((in_game_state*)_pGame->p_current_state)->bool_menu_is_active = 1;
            }

            return;
        }

        switch ( _pressedKey )
        {
            // player walk up
            case KEY_UP:
            case 'W':
            case 'w':
            {
                if ( !paused( _pGame ) )
                    player_walk( ((in_game_state*)_pGame->p_current_state)->p_player, ((in_game_state*)_pGame->p_current_state)->p_map, UP );

                break;
            }

            // player walk right
            case KEY_RIGHT:
            case 'D':
            case 'd':
            {
                if ( !paused( _pGame ) )
                    player_walk( ((in_game_state*)_pGame->p_current_state)->p_player, ((in_game_state*)_pGame->p_current_state)->p_map, RIGHT );

                break;
            }

            // player walk down
            case KEY_DOWN:
            case 'S':
            case 's':
            {
                if ( !paused( _pGame ) )
                    player_walk( ((in_game_state*)_pGame->p_current_state)->p_player, ((in_game_state*)_pGame->p_current_state)->p_map, DOWN );

                break;
            }

            // player walk left
            case KEY_LEFT:
            case 'A':
            case 'a':
            {
                if ( !paused( _pGame ) )
                    player_walk( ((in_game_state*)_pGame->p_current_state)->p_player, ((in_game_state*)_pGame->p_current_state)->p_map, LEFT );

                break;
            }

            // player drop bomb
            case ' ':
            {
                if ( !paused( _pGame ) )
                    player_drop_bomb( (void*)_pGame );

                break;
            }

            // Pause game
            //case 'P':
            case 'p':
            {
                // if paused, unpause; if unpaused, pause
                ((in_game_state*)_pGame->p_current_state)->bool_paused = !((in_game_state*)_pGame->p_current_state)->bool_paused;

                break;
            }

            // Esc menu
            case '\e':
            {
                // if game not already paused, pause it
                if ( !paused( _pGame ) )
                    ((in_game_state*)_pGame->p_current_state)->bool_paused = !((in_game_state*)_pGame->p_current_state)->bool_paused;

                // activate the escape menu
                ((in_game_state*)_pGame->p_current_state)->bool_menu_is_active = 1;

                break;
            }
        }   // switch
    } // if else
}


void render_in_game( game* _pGame )
{
    cleardevice();

    render_map( ((in_game_state*)_pGame->p_current_state)->p_map );

    render_bomb( ((in_game_state*)_pGame->p_current_state)->p_player->p_bomb );

    render_NPCs( ((in_game_state*)_pGame->p_current_state)->pp_NPCs, ((in_game_state*)_pGame->p_current_state)->NPC_count );

    render_player( ((in_game_state*)_pGame->p_current_state)->p_player );

    render_explosion( ((in_game_state*)_pGame->p_current_state)->p_player->p_bomb,
                     ((in_game_state*)_pGame->p_current_state)->p_map,
                     (void*)((in_game_state*)_pGame->p_current_state)->p_player,
                     (void**)((in_game_state*)_pGame->p_current_state)->pp_NPCs,
                     ((in_game_state*)_pGame->p_current_state)->NPC_count );

    render_top_bar( ((in_game_state*)_pGame->p_current_state)->p_top_bar, ((in_game_state*)_pGame->p_current_state)->p_player->num_lives );

    if ( paused( _pGame ) )
        outtextxy( GC_window_width / 2, GC_window_height * 0.85, "GAME PAUSED" );

    if ( ((in_game_state*)_pGame->p_current_state)->game_state == GAME_OVER )
    {
        outtextxy( GC_window_width / 2, GC_window_height / 2, "GAME OVER" );
        handle_game_ended( _pGame );
    }
    else if ( ((in_game_state*)_pGame->p_current_state)->game_state == VICTORY )
    {
        outtextxy( GC_window_width / 2, GC_window_height / 2, "VICTORIOUS" );
        handle_game_ended( _pGame );
    }

    render_esc_menu( _pGame );
}


void update_in_game( game* _pGame )
{
    if ( ((in_game_state*)_pGame->p_current_state)->bool_paused )
        return;
    else
    {
        if ( !((in_game_state*)_pGame->p_current_state)->p_player->alive )
        {
            ((in_game_state*)_pGame->p_current_state)->game_state = GAME_OVER;
            if ( !((in_game_state*)_pGame->p_current_state)->timer_set )
            {
                pause_audio();
                play_sound( GC_game_over_sound );
                reset_timer( ((in_game_state*)_pGame->p_current_state)->game_ended_timer );
                ((in_game_state*)_pGame->p_current_state)->timer_set = 1;
            }
        }

        if ( player_victory( (in_game_state*)_pGame->p_current_state ) )
        {
            ((in_game_state*)_pGame->p_current_state)->game_state = VICTORY;
            if ( !((in_game_state*)_pGame->p_current_state)->timer_set )
            {
                pause_audio();
                play_sound( GC_victory_sound );
                reset_timer( ((in_game_state*)_pGame->p_current_state)->game_ended_timer );
                ((in_game_state*)_pGame->p_current_state)->timer_set = 1;
            }
        }

        update_player( ((in_game_state*)_pGame->p_current_state)->p_player );

        update_NPCs( ((in_game_state*)_pGame->p_current_state)->pp_NPCs,
                    ((in_game_state*)_pGame->p_current_state)->NPC_count,
                    ((in_game_state*)_pGame->p_current_state)->p_player->p_bomb,
                    ((in_game_state*)_pGame->p_current_state)->p_map );

        if ( player_NPC_collision( ((in_game_state*)_pGame->p_current_state)->p_player,
                                  ((in_game_state*)_pGame->p_current_state)->pp_NPCs,
                                  ((in_game_state*)_pGame->p_current_state)->NPC_count ) && ((in_game_state*)_pGame->p_current_state)->p_player->alive )
        {
            pause_audio();
            play_sound( GC_player_death_sound );
            ((in_game_state*)_pGame->p_current_state)->p_player->alive = 0;
            ((in_game_state*)_pGame->p_current_state)->p_player->cause_of_death = DEATH_BY_PAC_MAN;
        }
    }
}


inline int paused( game* _pGame )
{
    return ((in_game_state*)_pGame->p_current_state)->bool_paused ? 1 : 0;
}


void render_esc_menu( game* _pGame )
{
    if (  ((in_game_state*)_pGame->p_current_state)->bool_menu_is_active )
    {
        // draw escape menu image
        draw_image( ((in_game_state*)_pGame->p_current_state)->p_esc_menu_img, GC_ig_esc_menu_x, GC_ig_esc_menu_y );

        // draw continue button
        render_button( ((in_game_state*)_pGame->p_current_state)->p_continue );

        // draw main menu button
        render_button( ((in_game_state*)_pGame->p_current_state)->p_main_menu );

        // draw exit button
        render_button( ((in_game_state*)_pGame->p_current_state)->p_exit );
    }
}


int find_NPCs_in_map( map* _map, matrix_point* _pPointStruct )
{
    int temp_NPC_count = 0;

    int i, j;
    for ( i = 0; i < GC_map_lin; i++ )
    {
        for ( j = 0; j < GC_map_col; j++ )
        {
            if ( _map->map_data[i][j].block_type == NPC_RESPAWN_BLOCK )
            {
                _pPointStruct[temp_NPC_count].i   = j;
                _pPointStruct[temp_NPC_count++].j = i;
            }
        }
    }

    return temp_NPC_count;
}


int player_NPC_collision( player* _pPlayer, NPC** _NPCs, int _NPCCount )
{
    rect player = { _pPlayer->left, _pPlayer->top, _pPlayer->right, _pPlayer->bottom };

    int is_colliding = 0;

    int i;
    for ( i = 0; i < _NPCCount; i++ )
    {
        // if NPC isn't alive skip him
        if ( !_NPCs[i]->alive )
            continue;

        rect NPC_i = { _NPCs[i]->left, _NPCs[i]->top, _NPCs[i]->right, _NPCs[i]->bottom };

    //  rectangle collision
        if ( collides( player, NPC_i ) )
            is_colliding = 1;
    }

    return is_colliding;
}


int player_victory( in_game_state* _pInGameState )
{
    NPC** NPCs    = _pInGameState->pp_NPCs;
    int NPC_count = _pInGameState->NPC_count;

    int player_won = 1;
    int i;
    for ( i = 0; i < NPC_count; i++ )
    {
        if ( NPCs[i]->alive )
            player_won = 0;
    }

    return player_won;
}


void handle_game_ended( game* _pGame )
{
    settextstyle( SMALL_FONT, HORIZ_DIR, 8 );

    outtextxy( GC_window_width / 2, GC_window_height * 0.75, "press any key to play again..." );

    char countdown[16];

    if ( (int)time_left( ((in_game_state*)_pGame->p_current_state)->game_ended_timer ) >= 0  )
    {
        snprintf( countdown, 16, "%d", (int)time_left( ((in_game_state*)_pGame->p_current_state)->game_ended_timer )  );

        outtextxy( GC_window_width / 2, GC_window_height * 0.8, countdown );
    }

    settextstyle( SMALL_FONT, HORIZ_DIR, 9 );

    if ( kbhit() && time_is_up( ((in_game_state*)_pGame->p_current_state)->game_ended_timer ) )
    {
        cleardevice();
        switch_to_state( _pGame, IN_GAME );
    }
}
