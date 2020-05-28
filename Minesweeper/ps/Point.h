#ifndef INCLUDED_POINT
#define INCLUDED_POINT

#include <mutex>
#include<SDL2/SDL.h>

class Point : public SDL_Point
{
    std::mutex m_pointLock;
public:
    Point(){
        x = 0;
        y = 0;
    }
    Point(int t_x, int t_y){x = t_x; y = t_y;}
    void move(int t_x, int t_y);

    void dissolve();
    //Thread safety.
    void lock();
    void unlock();
};
#endif // INCLUDED_POINT
