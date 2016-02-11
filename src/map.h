#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED


// ---------------------------------------------------------------------------
//                          Struct declaration: struct _tagMapNodeStruct
// ---------------------------------------------------------------------------
struct _tagMapNodeStruct
{
    int block_type;
    int has_NPC;
    int has_player;
    int left;
    int top;
    int right;
    int bottom;
};


// ---------------------------------------------------------------------------
//                          Type definition: map_node
// ---------------------------------------------------------------------------
typedef struct _tagMapNodeStruct    map_node;


// ---------------------------------------------------------------------------
//                          Struct declaration: struct _tagMapStruct
// ---------------------------------------------------------------------------
struct _tagMapStruct
{
    int lin;
    int col;

    void* p_block_de_img;   // Destructible block image/texture
    void* p_block_in_img;   // Indestructible block image/texture

    map_node** map_data;    // loaded from .txt files ( directory: \maps\*.txt )
};


// ---------------------------------------------------------------------------
//                          Type definition: map
// ---------------------------------------------------------------------------
typedef struct _tagMapStruct        map;



// ---------------------------------------------------------------------------
//                          Functions declarations
// ---------------------------------------------------------------------------
map* construct_map( int _whichMapToLoad );
void destroy_map( map* _pMap );

char** load_map_from_file( const char* _fileName ); // for .txt files, implement one for .bin/.dat files?
void unload_char_map( char** _map );

map_node** construct_enhanced_map( char** _charMap );
void unload_enhanced_map( map_node** _map );

void render_map( map* _pMap );


#endif // MAP_H_INCLUDED
