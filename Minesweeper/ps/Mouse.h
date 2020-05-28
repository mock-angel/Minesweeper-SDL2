#ifndef INCLUDED_MOUSE
#define INCLUDED_MOUSE

#include "Rect.h"

class Mouse{ // Dangerous, anyone could access since its not private.
public:
    //Rect m_rect;
    int x = 0;
    int y = 0;
    Mouse(){};
    bool isCollided(Rect* t_rect){
        //printf("%d, %d,  %d, %d   -- %d, %d\n", t_rect->x,t_rect->y,t_rect->w,t_rect->h, x, y); --test
        if((x<t_rect->x) || (y<t_rect->y) || (x>(t_rect->w + t_rect->x)) || (y>(t_rect->h + t_rect->y)) )
            return false;
        else return true;
    };
};
#endif // INCLUDED_MOUSE
