#ifndef INCLUDED_COLOR
#define INCLUDED_COLOR

#include "types.h"

struct ColorRGB{
    u8 r = 0;
    u8 g = 0;
    u8 b = 0;
    SDL_Color SDLColor;
    ColorRGB(){}
    ColorRGB(u8 t_r, u8 t_g, u8 t_b){
        r = t_r;
        g = t_g;
        b = t_b;
        SDLColor = {r, g, b};
    }

};

struct ColorRGBA: ColorRGB{
    u8 a = 0xFF;
    ColorRGBA() {}
    ColorRGBA(u8 t_r, u8 t_g, u8 t_b, u8 t_a):ColorRGB(t_r, t_g, t_b){
        a = t_a;
    }
};

#endif // INCLUDED_COLOR
