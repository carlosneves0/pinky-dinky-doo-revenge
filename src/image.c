

#include "game.h"
#include "image.h"


void* load_image( const char* _imgFileName, int _imgWidth, int _imgHeight )
{
    readimagefile( _imgFileName, 0, 0, _imgWidth, _imgHeight );

    unsigned int img_size = imagesize( 0, 0, _imgWidth, _imgHeight );

    void* p_temp_img = malloc( img_size );

    getimage( 0, 0, _imgWidth, _imgHeight, p_temp_img );

    return p_temp_img;
}


void unload_image( void* _ptrImage )
{
    if ( _ptrImage )
    {
        free( _ptrImage );
        _ptrImage = NULL;
    }
}


void draw_image( void* _img, int _posX, int _posY )
{
    putimage( _posX, _posY, _img, COPY_PUT );
}
