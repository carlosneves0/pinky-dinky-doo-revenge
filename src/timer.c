

#include "game.h"
#include "timer.h"


timer* create_timer( double _durationInSecs )
{
    timer* p_temp_timer = (timer*)malloc( sizeof( timer ) );

    p_temp_timer->init_t = clock();

    p_temp_timer->delta_t = _durationInSecs;

    return p_temp_timer;
}


void destroy_timer( timer* _pTimer )
{
    if ( _pTimer )
    {
        free( _pTimer );
        _pTimer = NULL;
    }
}


void reset_timer( timer* _pTimer )
{
    _pTimer->init_t = clock();
}


int time_is_up( timer* _pTimer )
{
    return (double)( clock() - _pTimer->init_t )/CLOCKS_PER_SEC >= _pTimer->delta_t ? 1 : 0; //difftime( time( NULL ), _pTimer->init_t ) >= _pTimer->delta_t ? 1 : 0 ;
}


double time_left( timer* _pTimer )
{
    return _pTimer->delta_t - (double)( clock() - _pTimer->init_t )/CLOCKS_PER_SEC;
}
