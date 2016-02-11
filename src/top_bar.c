

#include "game.h"
#include "global_constants.h"
#include "top_bar.h"


top_bar* construct_top_bar()
{
    top_bar* p_temp_top_bar = (top_bar*)malloc( sizeof( top_bar ) );

    p_temp_top_bar->bg_top_bar_img = load_image( GC_top_bar_bg_img, GC_top_bar_bg_width, GC_top_bar_bg_height );
    p_temp_top_bar->alive_pink_img = load_image( GC_alive_pink_img, GC_alive_pink_width, GC_alive_pink_height );
    p_temp_top_bar->dead_pink_img  = load_image( GC_dead_pink_img, GC_dead_pink_width, GC_dead_pink_height );

    return p_temp_top_bar;
}


void destroy_top_bar( top_bar* _pTopBar )
{
    unload_image( _pTopBar->bg_top_bar_img     );
    unload_image( _pTopBar->alive_pink_img );
    unload_image( _pTopBar->dead_pink_img  );

    free( _pTopBar );
    _pTopBar = NULL;
}


void render_life_icons( top_bar *_pTopBar, int _playerNumLives )
{
    int i;
    for ( i = 0; i < GC_player_num_lives; i++ )
    {
        if ( _playerNumLives-- )
            draw_image( _pTopBar->alive_pink_img, GC_life_x + ( GC_alive_pink_width * i), GC_life_y );
        else
            draw_image( _pTopBar->dead_pink_img, GC_life_x + ( GC_alive_pink_width * i), GC_life_y );
    }
}


void render_top_bar( top_bar *_pTopBar, int _playerNumLives )
{

    draw_image( _pTopBar->bg_top_bar_img, GC_top_bar_bg_x, GC_top_bar_bg_y );

    //render_clock

    //render_score

    render_life_icons( _pTopBar, _playerNumLives );
}
