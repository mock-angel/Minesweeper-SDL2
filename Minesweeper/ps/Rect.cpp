#include "Rect.h"

void Rect::move(int t_x, int t_y){
    x += t_x;
    y += t_y;
}
void Rect::makeCenter(int t_cx, int t_cy){
    x = t_cx - w/2;
    y = t_cy - h/2;
}
void Rect::lock(){
    m_rectLock.lock();
}
void Rect::unlock(){
    m_rectLock.unlock();
}
void Rect::dissolve(){
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}
