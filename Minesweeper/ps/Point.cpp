#include "Point.h"

void Point::move(int t_x, int t_y){
    x += t_x;
    y += t_y;
}
void Point::lock(){
    m_pointLock.lock();
}
void Point::unlock(){
    m_pointLock.unlock();
}
void Point::dissolve(){
    x = 0;
    y = 0;
}
