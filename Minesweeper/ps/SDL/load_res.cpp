#include "SDL/load_res.h"
# include <SDL2/SDL_ttf.h>
SDL_Surface* loadSurfaceOptimised( SDL_Surface* t_screenSurface,  std::string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, t_screenSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

SDL_Surface* loadSurface( std::string path )
{

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }

    return loadedSurface;
}

SDL_Texture* loadTexture( SDL_Renderer* t_renderer,  std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( t_renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

SDL_Surface* loadText( const char* text )
{
    TTF_Font* font = TTF_OpenFont("resources/Roboto-Regular.ttf", 24);
    //TTF_Font* font = TTF_OpenFont("/home/anantha/Desktop/project/Minesweeper/resources/Roboto-Regular.ttf", 24);
    //printf("hell%s\n",SDL_GetError());
    SDL_Color White = {255, 255, 255};
    SDL_Color Black = {0, 0, 0};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, White);
    TTF_CloseFont(font);

    return surfaceMessage;

}
