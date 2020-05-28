#ifndef GUIWINDOW
#define GUIWINDOW

#include<SDL2/SDL_image.h>
#include <mutex>

#include "precompiled.h"

#include "GUI.h"
# include <SDL2/SDL_ttf.h>

SDL_HitTestResult hitTest(SDL_Window *window, const SDL_Point *pt, void *data);


class WindowBackground{  //Background Image.
    ColorRGBA m_bgColor;
    SDL_Renderer* m_renderer = NULL;
    //SDL_Texture* m_bgTexture = NULL; //Graphics Processor.
    //SDL_Surface* m_bgSurface = NULL; //CPU
    //Rect* m_rect = NULL;
public:
    /*  Setters  */
    /*void setBackgroundSurface(SDL_Surface* t_surface){
        m_bgSurface = t_surface;
    }
    void setBackgroundTexture(SDL_Texture* t_texture){
        m_bgTexture = t_texture;
    }*/
    void setRenderer(SDL_Renderer* t_renderer){
        m_renderer = t_renderer;
    }
    SDL_Renderer* getRenderer(){
        return m_renderer;
    }
    void setBackgroundColor(ColorRGBA t_bgColor){
        m_bgColor = t_bgColor;
        SDL_SetRenderDrawColor( m_renderer, m_bgColor.r, m_bgColor.g, m_bgColor.b, m_bgColor.a );
    }
    /*  Renderer.  */
    /*void draw(SDL_Surface* t_surface){
        SDL_BlitSurface(m_spriteSurface, NULL, t_surface, m_rect);
    };
    void render(SDL_Texture* t_texture){
        SDL_SetRenderTarget( m_cRenderer, t_texture );
        //SDL_RenderClear( gRenderer );
        SDL_RenderCopy(m_cRenderer, m_spriteTexture, m_rect, m_rect);
        SDL_SetRenderTarget( m_cRenderer, NULL );
    };*/
    void clearRenderer(){
        SDL_RenderClear( m_renderer );
    }
};

class GUIWindow : public WindowBackground{
public:

    //Intializes internals.
    GUIWindow();
    ~GUIWindow();

    /*  Setters.  */
    void setFlags(Uint32 t_flags);
    /*  Mutators.  */

    //Creates window
    bool init();

    //Handles window events.
    void handleEvent( SDL_Event& e );

    //Focuses on window.
    void focus();

    //Shows windows contents.
    virtual void render();

    //Updates windows contents.
    virtual void update();

    //Deallocates internals. -- end of execution.
    void free();

    /*  Getters.  */

    unsigned int getWindowId();

    //Window dimensions.
    int getWidth();
    int getHeight();

    //Window focii.             --Focus calls.
    bool hasMouseFocus();
    bool hasKeyboardFocus();
    bool isMinimized();

    bool isShown();
    bool isClosed();

    Mouse m_mouse;

    GUISpriteHandler* sprites = NULL;
    GUISpriteHandler* getSpriteContainer();
    ///SceneHandler* sprites = NULL;
    ///SceneHandler* getSpriteContainer();

    //Threads.
    virtual void updateThread();
    virtual void renderThread();
    //void eventThread();

    virtual void draw() = 0;
    //std::mutex m_eventLock;
    std::mutex m_textureLock, m_surfaceLock;
    std::mutex m_updateLock, m_renderLock;

    std::vector<Rect> m_hitTestDragRects;

protected:
    SDL_Renderer* m_renderer = NULL;

private:
    //Window data.
    SDL_Window* m_window = NULL;

    SDL_Texture* m_screenTexture = NULL; //Graphics Processor.
    SDL_Surface* m_screenSurface = NULL; //CPU.

    // Contains all sprites.
    GUISpriteGroup* m_sprites = NULL;

    unsigned int m_windowId;

    //Window dimensions.
    int m_width = 470;
    int m_height = 470;

    //Window focus.
    bool m_mouseFocus  = true;              //!< Stores mouse focus state: true if mouse is focused on the window.
    bool m_keyboardFocus = true;            //!< Stores keyboard focus state: true if keyboard is focused on the window.
    bool m_fullScreen  = false;             //!< : true if window is fullscreen.
    bool m_minimized  = false;              //!< : true if window is minimised, false if window is restored/visible.

    //Displayed.
    bool m_shown;                           //!<
    bool m_closed;                          //!< Says if window is still active.

    // Window flags.
    Uint32 m_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE; //!< flags set during initialisation of window.

    virtual void init_sprites() = 0;



};
#endif // GUIWINDOW







