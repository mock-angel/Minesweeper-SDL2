
#ifndef INCLUDED_RECT
#define INCLUDED_RECT
#include <mutex>
#include<SDL2/SDL.h>

class Rect : public SDL_Rect
{
    std::mutex m_rectLock;
public:
    Rect(){
        x = 0;
        y = 0;
        w = 0;
        h = 0;
    }

    Rect(const Rect &t_rect){
        x = t_rect.x;
        y = t_rect.y;
        w = t_rect.w;
        h = t_rect.h;

    }

    Rect(int t_x, int t_y, int t_w, int t_h){x = t_x; y = t_y; w = t_w; h = t_h;}
    void move(int t_x, int t_y);
    void makeCenter(int t_x, int t_y);

    void dissolve();
    //Thread safety.
    void lock();
    void unlock();
};

#endif // INCLUDED_RECT
