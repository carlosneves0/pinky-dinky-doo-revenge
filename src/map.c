

#include "game.h"
#include "map.h"


map* construct_map( int _whichMapToLoad )
{
    // allocate memory for the map struct
    map* p_temp_map = (map*)malloc( sizeof( map ) );

    // initialize the map size(lin x col) with the global constants map_lin and map_col
    p_temp_map->lin = GC_map_lin;
    p_temp_map->col = GC_map_col;

    // load destructible and indestructible blocks images/textures
    p_temp_map->p_block_de_img = load_image( GC_block_de_img, GC_block_size, GC_block_size );
    p_temp_map->p_block_in_img = load_image( GC_block_in_img, GC_block_size, GC_block_size );

    // load a map from "maps\" directory
    char** temp_char_map = load_map_from_file( GC_map_dir[_whichMapToLoad] );

    // construct enhanced map based on char** map, that is, construct a matrix of map_nodes
    p_temp_map->map_data = construct_enhanced_map( temp_char_map );

    unload_char_map( temp_char_map );

    return p_temp_map;
}


void destroy_map( map* _pMap )
{
    if ( _pMap )
    {
        unload_image( _pMap->p_block_de_img );
        unload_image( _pMap->p_block_in_img );

        unload_enhanced_map( _pMap->map_data );

        free( _pMap );
        _pMap = NULL;
    }
}


char** load_map_from_file( const char* _fileName ) // for .txt files
{
    FILE* file = fopen( _fileName, "r" );

    if (!file)
        return NULL;

    char** map_temp = (char **)malloc( GC_map_lin * sizeof(char*) );

    if ( !map_temp )
        return NULL;

    int i;
    for ( i = 0; i < GC_map_lin; i++ )
    {
        map_temp[i] = (char *)malloc( GC_map_col * sizeof(char) + 2 ); // + 2 for '\n' and '\0' that fgets may append

        if ( !map_temp[i] )
        {
            fclose( file );
            return NULL;
        }

        if ( fgets( map_temp[i], GC_map_col + 2, file ) == NULL )
            return NULL;
        else
        {
             if ( strlen( map_temp[i] ) > 1 )
             {
                 //int size = strlen( map_temp[i] );
                 map_temp[i][strcspn( map_temp[i], "\n" )] = '\0';
             }
             else
             {
                 free( map_temp[i] );
                 map_temp[i] = NULL;
                 i--;
                 continue;
             }
         }
    }

    fclose(file);

    return map_temp;
}


void unload_char_map( char** _map )
{
    if ( _map )
    {
        int i;
        for ( i = 0; i < GC_map_lin; i++ )
            if ( _map[i] )
                free( _map[i] );

        free( _map );
        _map = NULL;
    }
}


map_node** construct_enhanced_map( char** _charMap )
{
    map_node** temp_map = (map_node**)malloc( GC_map_lin * sizeof( map_node* ) );

    int i, j;
    for ( i = 0; i < GC_map_lin; i++ )
        temp_map[i] = (map_node*)malloc( GC_map_col * sizeof( map_node ) );

    for ( i = 0; i < GC_map_lin; i++ )
    {
        for ( j = 0; j < GC_map_col; j++ )
        {
            if ( (int)_charMap[i][j] == NULL_BLOCK )
            {
                temp_map[i][j].block_type = NULL_BLOCK;

                temp_map[i][j].has_NPC    = 0;
                temp_map[i][j].has_player = 0;

                temp_map[i][j].left   = j * GC_block_size;
                temp_map[i][j].top    = ( i * GC_block_size ) + GC_y_offset;
                temp_map[i][j].right  = temp_map[i][j].left + GC_block_size;
                temp_map[i][j].bottom = temp_map[i][j].top + GC_block_size;
            }
            else if ( (int)_charMap[i][j] == DESTRUCTIBLE_BLOCK )
            {
                temp_map[i][j].block_type = DESTRUCTIBLE_BLOCK;

                temp_map[i][j].has_NPC    = 0;
                temp_map[i][j].has_player = 0;

                temp_map[i][j].left   = j * GC_block_size;
                temp_map[i][j].top    = ( i * GC_block_size ) + GC_y_offset;
                temp_map[i][j].right  = temp_map[i][j].left + GC_block_size;
                temp_map[i][j].bottom = temp_map[i][j].top + GC_block_size;
            }
            else if ( (int)_charMap[i][j] == INDESTRUCTIBLE_BLOCK )
            {
                temp_map[i][j].block_type = INDESTRUCTIBLE_BLOCK;

                temp_map[i][j].has_NPC    = 0;
                temp_map[i][j].has_player = 0;

                temp_map[i][j].left   = j * GC_block_size;
                temp_map[i][j].top    = ( i * GC_block_size ) + GC_y_offset;
                temp_map[i][j].right  = temp_map[i][j].left + GC_block_size;
                temp_map[i][j].bottom = temp_map[i][j].top + GC_block_size;
            }
            else if ( (int)_charMap[i][j] == PLAYER_RESPAWN_BLOCK )
            {
                temp_map[i][j].block_type = PLAYER_RESPAWN_BLOCK;

                temp_map[i][j].has_NPC    = 0;
                temp_map[i][j].has_player = 1;


                temp_map[i][j].left   = j * GC_block_size;
                temp_map[i][j].top    = ( i * GC_block_size ) + GC_y_offset;
                temp_map[i][j].right  = temp_map[i][j].left + GC_block_size;
                temp_map[i][j].bottom = temp_map[i][j].top + GC_block_size;
            }
            else                     // NPC_RESPAWN_BLOCK
            {
                temp_map[i][j].block_type = NPC_RESPAWN_BLOCK;

                temp_map[i][j].has_NPC    = 1;
                temp_map[i][j].has_player = 0;


                temp_map[i][j].left   = j * GC_block_size;
                temp_map[i][j].top    = ( i * GC_block_size ) + GC_y_offset;
                temp_map[i][j].right  = temp_map[i][j].left + GC_block_size;
                temp_map[i][j].bottom = temp_map[i][j].top + GC_block_size;
            }
        }
    }

    return temp_map;
}


void unload_enhanced_map( map_node** _map )
{
    if ( _map )
    {
        int i;
        for ( i = 0; i < GC_map_lin; i++ )
            if ( _map[i] )
                free( _map[i] );

        free( _map );
        _map = NULL;
    }
}


void render_map( map* _pMap )
{
    int i, j;
    for( i = 0; i < GC_map_lin; i++ )
    {
        for( j = 0; j < GC_map_col; j++ )
        {
            if ( _pMap->map_data[i][j].block_type == DESTRUCTIBLE_BLOCK )
            {
                int x = _pMap->map_data[i][j].left;
                int y = _pMap->map_data[i][j].top;
                draw_image( _pMap->p_block_de_img, _pMap->map_data[i][j].left, _pMap->map_data[i][j].top );
            }
            else if ( _pMap->map_data[i][j].block_type == INDESTRUCTIBLE_BLOCK )
            {
                int x = _pMap->map_data[i][j].left;
                int y = _pMap->map_data[i][j].top;
                draw_image( _pMap->p_block_in_img, _pMap->map_data[i][j].left, _pMap->map_data[i][j].top );
            }
        }
    }
}
