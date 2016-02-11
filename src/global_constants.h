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
//                          Macro Guard
// ---------------------------------------------------------------------------
#ifndef GLOBAL_CONSTANTS_H_INCLUDED
#define GLOBAL_CONSTANTS_H_INCLUDED


// ---------------------------------------------------------------------------
//                          Global Constants
// ---------------------------------------------------------------------------


static const char* GC_game_name = "Pinky Dink Doo: revenge!";

//static const double GC_FPS = 30.0;
//static const double GC_frame_duration = 1.0 / GC_FPS;

static const int GC_game_ended_duration = 5.0;

static const int GC_window_width  = 480;
static const int GC_window_height = 464;

/* This means game blocks/squares are 32 pixels x 32 pixels */
static const int GC_block_size = 32;

/* For Background Images */
static const int GC_bg_img_x = 0;
static const int GC_bg_img_y = 0;

static const int GC_bg_img_width  = GC_window_width;
static const int GC_bg_img_height = GC_window_height;


/* For user interface buttons */
static const int GC_button_width  = 140;
static const int GC_button_height = 40;


/* Main Menu State */
/* Main Menu Background image */
static const char* GC_mm_background_img = "img\\ui\\mm_bg.bmp";


/* Main Menu play button */
static const char* GC_mm_play_nr_img = "img\\ui\\mm_play_nr.bmp";
static const char* GC_mm_play_se_img = "img\\ui\\mm_play_se.bmp";

static const int GC_mm_play_button_x = GC_window_width / 2 - GC_button_width / 2;
static const int GC_mm_play_button_y = (const int)(0.45 * GC_window_height);


/* Main Menu controls button */
static const char* GC_mm_controls_nr_img = "img\\ui\\mm_controls_nr.bmp";
static const char* GC_mm_controls_se_img = "img\\ui\\mm_controls_se.bmp";

static const int GC_mm_controls_button_x = GC_window_width / 2 - GC_button_width / 2;
static const int GC_mm_controls_button_y = GC_mm_play_button_y + 60;


/* Main Menu credits button */
static const char* GC_mm_credits_nr_img = "img\\ui\\mm_credits_nr.bmp";
static const char* GC_mm_credits_se_img = "img\\ui\\mm_credits_se.bmp";

static const int GC_mm_credits_button_x = GC_window_width / 2 - GC_button_width / 2;
static const int GC_mm_credits_button_y = GC_mm_controls_button_y + 60;


/* Main Menu exit button */
static const char* GC_mm_exit_nr_img = "img\\ui\\mm_exit_nr.bmp";
static const char* GC_mm_exit_se_img = "img\\ui\\mm_exit_se.bmp";

static const int GC_mm_exit_button_x = GC_window_width / 2 - GC_button_width / 2;
static const int GC_mm_exit_button_y = GC_mm_credits_button_y + 60;


/* Controls and Credits Menus back button */
static const char* GC_c_back_se_img = "img\\ui\\c_back_se.bmp";

static const int GC_c_back_button_x = GC_window_width / 2 - GC_button_width / 2;
static const int GC_c_back_button_y = (const int)(0.85 * GC_window_height);


/* Controls Menu State */
/* Controls Menu Background image */
static const char* GC_co_background_img = "img\\ui\\co_bg.bmp";


/* Credits Menu State */
/* Credits Menu Background image */
static const char* GC_cr_background_img = "img\\ui\\cr_bg.bmp";


/* InGame State */
static const int GC_y_offset = 48; // pixels; this offset is for the map, to leave a space on the top of the window for lifes, time, info...

/* In Game Escape Menu */
static const char* GC_ig_esc_menu_img = "img\\ui\\ig_em.bmp";
static const int GC_ig_esc_menu_width  = 160;
static const int GC_ig_esc_menu_height = 160;

static const int GC_ig_esc_menu_x = (GC_window_width - GC_ig_esc_menu_width) / 2;
static const int GC_ig_esc_menu_y = (GC_window_height - GC_ig_esc_menu_height) / 2;

/* In Game Escape Menu Continue button */
static const char* GC_ig_continue_nr_img = "img\\ui\\ig_continue_nr.bmp";
static const char* GC_ig_continue_se_img = "img\\ui\\ig_continue_se.bmp";

static const int GC_ig_continue_x = GC_ig_esc_menu_x + 10;
static const int GC_ig_continue_y = GC_ig_esc_menu_y + 10;

/* In Game Escape Menu Main Menu button */
static const char* GC_ig_mm_nr_img = "img\\ui\\ig_mm_nr.bmp";
static const char* GC_ig_mm_se_img = "img\\ui\\ig_mm_se.bmp";

static const int GC_ig_mm_x = GC_ig_esc_menu_x + 10;
static const int GC_ig_mm_y = GC_ig_continue_y + 50;

/* In Game Escape Menu Exit button */
static const int GC_ig_exit_x = GC_ig_esc_menu_x + 10;
static const int GC_ig_exit_y = GC_ig_mm_y + 50;

/* In Game Top Bar */
static const char* GC_top_bar_bg_img = "img\\ui\\ig_tb.bmp";
static const char* GC_alive_pink_img = "img\\ui\\pla.bmp";
static const char* GC_dead_pink_img  = "img\\ui\\pld.bmp";

static const int GC_top_bar_bg_x = 0;
static const int GC_top_bar_bg_y = 0;

static const int GC_top_bar_bg_width  = GC_window_width;
static const int GC_top_bar_bg_height = GC_y_offset;

static const int GC_alive_pink_width  = GC_block_size / 2;
static const int GC_alive_pink_height = GC_block_size / 2;

static const int GC_dead_pink_width  = GC_block_size / 2;
static const int GC_dead_pink_height = GC_block_size / 2;

static const int GC_life_x = 223;
static const int GC_life_y = 23;
//static const int GC_dist_between_pinks = 10;


/* Bomb */
static const char* GC_bomb_img = "img\\graphics\\bomb.bmp";

static const char* GC_bomb_explosion_frames[] = { "img\\graphics\\expl10.bmp", "img\\graphics\\expl9.bmp", "img\\graphics\\expl8.bmp", "img\\graphics\\expl7.bmp"
                                                    "img\\graphics\\expl6.bmp", "img\\graphics\\expl5.bmp", "img\\graphics\\expl4.bmp", "img\\graphics\\expl3.bmp",
                                                    "img\\graphics\\expl2.bmp", "img\\graphics\\expl1.bmp" };

static const int GC_bomb_explosion_frames_num = 10;

static const int GC_explosion_range = 3; // blocks

static const double GC_bomb_duration = 2.5;   // seconds
static const double GC_explosion_duration = 1.0;   // seconds


/* Player */
static const char* GC_player_up_img    = "img\\graphics\\pl1.bmp";
static const char* GC_player_right_img = "img\\graphics\\pl2.bmp";
static const char* GC_player_down_img  = "img\\graphics\\pl3.bmp";
static const char* GC_player_left_img  = "img\\graphics\\pl4.bmp";

static const char* GC_player_dead_by_pac_man_img   = "img\\graphics\\pld_pm.bmp";
static const char* GC_player_dead_by_explosion_img = "img\\graphics\\pld_ex.bmp";

static const int GC_player_walk_dist = 4; // pixels

static const int GC_player_num_lives = 3;

/* NPC */
static const char* GC_pac_man_up_frames[]    = { "img\\graphics\\pm_up_1.bmp", "img\\graphics\\pm_up_2.bmp", "img\\graphics\\pm_up_3.bmp" };
static const char* GC_pac_man_right_frames[] = { "img\\graphics\\pm_ri_1.bmp", "img\\graphics\\pm_ri_2.bmp", "img\\graphics\\pm_ri_3.bmp" };
static const char* GC_pac_man_down_frames[]  = { "img\\graphics\\pm_do_1.bmp", "img\\graphics\\pm_do_2.bmp", "img\\graphics\\pm_do_3.bmp" };
static const char* GC_pac_man_left_frames[]  = { "img\\graphics\\pm_le_1.bmp", "img\\graphics\\pm_le_2.bmp", "img\\graphics\\pm_le_3.bmp" };

static const int GC_NPC_frames = 3;

static const int GC_max_NPC_count = 8;

static const int GC_NPC_walk_dist = 1;

static const double GC_NPC_walk_duration = 0.0096; // seconds

static const double GC_NPC_AI_delay = 0.64; // seconds

static const double GC_NPC_frames_duration = 0.9; // seconds

/* Map */
static const int GC_number_of_maps = 5;

static const char* GC_map_dir[] = { "maps\\0.txt", "maps\\1.txt", "maps\\2.txt", "maps\\3.txt", "maps\\4.txt" };

static const int GC_map_lin = 13;
static const int GC_map_col = 15;


/* Map graphics */
static const char* GC_block_de_img = "img\\graphics\\bl_de.bmp";

static const char* GC_block_in_img = "img\\graphics\\bl_in.bmp";


/* Audio */
static const char* GC_mm_bg_music = "audio\\main_menu.wav";

static const char* GC_co_bg_music = GC_mm_bg_music;

static const char* GC_cr_bg_music = "audio\\credits.wav";

static const char* GC_game_over_sound = "audio\\game_over.wav";

static const char* GC_victory_sound = "audio\\victory.wav";

static const char* GC_player_death_sound = "audio\\player_death.wav";

static const char* GC_explosion_sound = "audio\\boom.wav";

static const char* GC_bomb_sound = "audio\\bomb.wav";


#endif // GLOBAL_CONSTANTS_H_INCLUDED
