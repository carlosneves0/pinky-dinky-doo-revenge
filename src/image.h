#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

/// Images are void* ///

void* load_image( const char* _imgFileName, int _imgWidth, int _imgHeight );

void unload_image( void* _ptrImage );

void draw_image( void* _img, int _posX, int _posY );


#endif // IMAGE_H_INCLUDED
