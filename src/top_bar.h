#ifndef TOP_BAR_H_INCLUDED
#define TOP_BAR_H_INCLUDED


struct _tagStructInGameTopBar
{
    void* bg_top_bar_img;
    void* alive_pink_img;
    void* dead_pink_img;

    // clock* game_clock;
    // int score
};

typedef struct _tagStructInGameTopBar    top_bar;


top_bar* construct_top_bar();

void destroy_top_bar( top_bar* _pTopBar );

void render_top_bar( top_bar *_pTopBar, int _playerNumLives );

void render_life_icons( top_bar *_pTopBar, int _playerNumLives );


#endif // TOP_BAR_H_INCLUDED
