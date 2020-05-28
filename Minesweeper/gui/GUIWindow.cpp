#include<SDL2/SDL.h>

#include "precompiled.h"

#include "GUIWindow.h"

// Constructor.
GUIWindow::GUIWindow(){
    sprites = new GUISpriteHandler(this);
    m_hitTestDragRects.push_back(Rect(0, 0, m_width, 30));
}

GUIWindow::~GUIWindow(){
    m_closed = true;
    free();
}
void GUIWindow::setFlags(Uint32 t_flags){
    m_flags = t_flags;
}
bool GUIWindow::init(){
    //TODO: Let user add title...
    m_window = SDL_CreateWindow( "Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, m_flags);
    SDL_HideWindow(m_window);

    if (SDL_SetWindowHitTest(m_window, hitTest, this) == -1) {
        SDL_Log("Enabling hit-testing failed!\n");
        //SDL_Quit();
        return 1;
    }

    if( m_window != NULL ){
        m_mouseFocus = true;
        m_keyboardFocus = true;

        // Create renderer for window.
        m_renderer = SDL_CreateRenderer( m_window, -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
                    //SDL_WINDOW_OPENGL
        if (m_renderer == NULL){
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            SDL_DestroyWindow( m_window );
            m_window = NULL;

            return false;

        }
        else{
            sprites->setRenderer(m_renderer);
            //Initialize renderer color. //bgcolor
            WindowBackground::setRenderer(m_renderer);
            WindowBackground::setBackgroundColor({77, 77, 77, 83});
            //SDL_SetRenderDrawColor( m_renderer, 77, 77, 83, 0xFF );
            //SDL_RenderClear( m_renderer );
            m_shown = true;
            SDL_ShowWindow(m_window);
            printf("hello;\n");

            //Grab window identifier.
            m_windowId = SDL_GetWindowID( m_window );
            //SDL_Delay(2000);
            //Flag as opened

            // INIT OTHER.
            init_sprites();
            return true;
        }
    }
    else{
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
}
//test init
///GUISpriteContainer* GUIWindow::sprites(){
///    return m_sprites;
///}
GUISpriteHandler* GUIWindow::getSpriteContainer(){
    return sprites;
}

/*void GUIWindow::init_sprites(){
    GUISprite* sprite = new GUISprite();
    sprite->setRenderer(m_renderer);
    sprite->setTexture(loadTexture(m_renderer, "sss.png"));
    m_sprites->addSprite(sprite);
}*/
// Getters. NOte: Used to be in GUIwindow_getters.cpp

int GUIWindow::getWidth(){
    return m_width;
}

int GUIWindow::getHeight(){
    return m_height;
}

bool GUIWindow::hasMouseFocus(){
    return m_mouseFocus;
}

bool GUIWindow::hasKeyboardFocus(){
    return m_keyboardFocus;
}

bool GUIWindow::isMinimized(){
    return m_minimized;
}

bool GUIWindow::isShown(){
    return m_shown;
}

bool GUIWindow::isClosed(){
    return m_closed;
}

unsigned int GUIWindow::getWindowId(){
    return m_windowId;
}

void GUIWindow::focus(){
    //Restore window when called.
    if( !m_shown ){
        SDL_ShowWindow( m_window );
    }

    //Move window forward
    SDL_RaiseWindow( m_window );
}

void GUIWindow::free(){
    //TODO: Its okay to not use the If confi==dition for these...
    if(m_screenTexture != NULL) SDL_DestroyTexture( m_screenTexture );
    if(m_screenSurface != NULL) SDL_FreeSurface( m_screenSurface );
    if(m_renderer != NULL) SDL_DestroyRenderer( m_renderer );
    if(m_window != NULL) SDL_DestroyWindow( m_window );
    m_screenTexture = NULL;
    m_screenSurface = NULL;
    m_renderer = NULL;
    m_window = NULL;
    // Put cleaning code here.
}

void GUIWindow::update(){

}

void GUIWindow::render(){
    //m_sprites->render(m_screenTexture);
    //printf("Inside GUI window\n");
}

void GUIWindow::updateThread(){//return;
    printf("updateThread:: Started\n");

    while(!isClosed()){
        m_updateLock.lock(); //TODO: Order of  lock?

        update();

        m_updateLock.unlock();
    }

    printf("updateThread:: Stopped\n");
}

void GUIWindow::renderThread(){//return;
    printf("renderThread:: Started\n");
    while(!isClosed()){
        m_renderLock.lock(); //TODO: Order of  lock?

        render();

        m_renderLock.unlock();
        usleep(1);
    }
    printf("renderThread:: Stopped\n");
}

SDL_HitTestResult hitTest(SDL_Window *t_window, const SDL_Point *pt, void* data)
{
    GUIWindow* guiwindow = (GUIWindow*) data;

    for (unsigned int i = 0; i < guiwindow->m_hitTestDragRects.size(); i++)
    {
        if (SDL_PointInRect(pt, &(guiwindow->m_hitTestDragRects[i]))) // no resizing support currently.
            return SDL_HITTEST_DRAGGABLE;
    }

    return SDL_HITTEST_NORMAL; // Need to change this.
}
