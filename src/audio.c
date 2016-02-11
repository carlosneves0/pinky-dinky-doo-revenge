

#include "audio.h"
#include "game.h"


void play_music( const char* _audioFileName )
{
#ifndef NO_WIN32_SOUND
    PlaySound( _audioFileName, NULL, SND_ASYNC | SND_LOOP );
#endif
}


void play_sound( const char* _audioFileName )
{
#ifndef NO_WIN32_SOUND
    PlaySound( _audioFileName, NULL, SND_ASYNC );
#endif
}


void pause_audio( void )
{
#ifndef NO_WIN32_SOUND
    PlaySound( NULL, NULL, SND_ASYNC );
#endif
}
