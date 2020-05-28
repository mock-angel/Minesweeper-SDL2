#ifndef INCLUDED_TEXTURE
#define INCLUDED_TEXTURE
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//SDL_Texture* loadTexture( SDL_Renderer* t_renderer, std::string path );
SDL_Surface* loadSurfaceOptimised( SDL_Surface* t_screenSurface,  std::string path );
SDL_Surface* loadSurface( std::string path );
SDL_Texture* loadTexture( SDL_Renderer* t_renderer,  std::string path );
SDL_Surface* loadText( const char* text );
SDL_Surface* loadText( std::string text );


#endif // INCLUDED_TEXTURE_
//SDL_DestroyTexture
