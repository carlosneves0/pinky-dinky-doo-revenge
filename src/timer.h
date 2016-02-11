#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED


#include <time.h>


struct _tagStructTimer
{
    clock_t init_t;
    double delta_t;
};


typedef struct _tagStructTimer timer;


timer* create_timer( double _durationInSecs );

void destroy_timer( timer* _pTimer );

void reset_timer( timer* _pTimer );

int time_is_up( timer* _pTimer );

double time_left( timer* _pTimer );


#endif // TIMER_H_INCLUDED
