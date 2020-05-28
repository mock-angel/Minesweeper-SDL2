
#include "SDL2/SDL.h"
//#include<SDL2/SDL_image.h>
#include <iostream>

#include "GUIWindow.h"

void GUIWindow::handleEvent( SDL_Event& e )
{
    //TODO: remove unnecessary window ID check.

    //If an event was detected for this window
    if( e.type == SDL_WINDOWEVENT)// && e.window.windowID == m_windowId)
    //TODO: Avoid unnecessarity searching and calling for events from window.
    {
        //Caption update flag.
        //bool updateCaption = false;

        switch( e.window.event )
        {
        //Window appeared.
        case SDL_WINDOWEVENT_SHOWN:
            m_shown = true;
            printf("W: Show\n");
            break;

        //Window disappeared.
        case SDL_WINDOWEVENT_HIDDEN:
            m_shown = false;
            printf("W: Hide\n");
            break;

        //Get new dimensions and repaint.
        case SDL_WINDOWEVENT_SIZE_CHANGED:

            m_renderLock.lock(); // First lock the render thread.
            m_updateLock.lock(); // Second lock the update thread.
            std::lock (m_textureLock, m_surfaceLock);
            m_width = e.window.data1;
            m_height = e.window.data2;

            //SDL_RenderPresent( m_renderer );
            //TODO: Rewrite above line for surface render...

            m_renderLock.unlock();
            m_updateLock.unlock();

            m_textureLock.unlock();
            m_surfaceLock.unlock();

            break;
        //Repaint on expose.
        case SDL_WINDOWEVENT_EXPOSED:
            m_renderLock.lock();
            std::lock (m_textureLock, m_surfaceLock);
            SDL_RenderPresent(m_renderer);

            printf("W: Exposed\n");
            m_textureLock.unlock();
            m_surfaceLock.unlock();
            m_renderLock.unlock();
            break;

        //Mouse enter.
        case SDL_WINDOWEVENT_ENTER:
            m_mouseFocus = true;

            printf("M: Enter\n");
            break;

        //Mouse exit.
        case SDL_WINDOWEVENT_LEAVE:
            m_mouseFocus = false;

            printf("M: Leave\n");
            break;

        //Keyboard focus gained.
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            m_keyboardFocus = true;

            printf("K: focus Gained\n");
            break;

        //Keyboard focus lost.
        case SDL_WINDOWEVENT_FOCUS_LOST:
            m_keyboardFocus = false;

            printf("W: focus Lost\n");
            break;

        //Window minimized.
        case SDL_WINDOWEVENT_MINIMIZED:
            m_minimized = true;

            printf("W: MINIMIZED\n");
            break;

        //Window maxized.
        case SDL_WINDOWEVENT_MAXIMIZED:
            m_minimized = false;
            printf("W: MAXIMIZED\n");
            break;

        //Window restored.
        case SDL_WINDOWEVENT_RESTORED:
            m_minimized = false;

            printf("W: RESTORED\n");
            break;

        //Hide on close.
        case SDL_WINDOWEVENT_CLOSE:
            SDL_HideWindow( m_window );
            m_renderLock.lock(); // First lock the render thread.
            m_updateLock.lock(); // Second lock the update thread.

            std::lock (m_textureLock, m_surfaceLock); // Next lock draw surfaces.

            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);

            m_window = NULL;
            m_renderer = NULL;
            m_closed = true;
            m_textureLock.unlock();
            m_surfaceLock.unlock();

            m_renderLock.unlock();
            m_updateLock.unlock();

            break;
        }
    }
}
