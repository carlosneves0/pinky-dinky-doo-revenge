#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED


// ---------------------------------------------------------------------------
//                          Struct declaration
// ---------------------------------------------------------------------------
struct _tagStructButton
{
    int x;
    int y;
    int width;
    int height;
    int bool_is_selected;
    void* p_normal_img;
    void* p_selected_img;
};


// ---------------------------------------------------------------------------
//                          Type definition: button
// ---------------------------------------------------------------------------
typedef struct _tagStructButton     button;


// ---------------------------------------------------------------------------
//                          Functions declarations
// ---------------------------------------------------------------------------
button* load_button( int _buttonX, int _buttonY, int _buttonWidth, int _buttonHeight, const char* _normalImg, const char* _selectedImg );

void unload_button( button* _pButton );

void render_button( button* _pButton );


#endif // BUTTON_H_INCLUDED
