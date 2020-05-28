#include <thread>
#include <pthread.h>
#include "Engine.h"

#include "precompiled.h"

#include "GUI.h"
typedef void * (*THREADFUNCPTR)(void *);

Engine::Engine(){
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();
}

Engine::~Engine(){
    // Wait till all threads are closed.
    waitTillClosed();

    // Safely delete all threads in array.
    /*for(unsigned i = 0; i < m_threadIds.size(); i++){
        ///delete m_threadIds[i];      //delete
        ///m_threadIds[i] = NULL;
    }
    m_threadIds.clear();
    */
    /*for(unsigned i = 0; i < m_threads.size(); i++){
        delete m_threads[i];      //delete
        m_threads[i] = NULL;
    }
    m_threads.clear();
    */
    // Now delete all windows.
    printf("Starting destructor\n");
    for(unsigned i = 0; i < m_windowsContainer.size(); i++){
        delete m_windowsContainer[i];      //delete
        m_windowsContainer[i] = NULL;
    }
    m_windowsContainer.clear();
}

int  Engine::addProgram(GUIWindow* t_programMain){
    // Test init of the program.
    if ( t_programMain->init() )
    {   int id = t_programMain->getWindowId();

        // Create update thread and render thread.
        //pthread_t threadId0, threadId1;
        //pthread_create(&threadId0, NULL, (THREADFUNCPTR) &GUIWindow::updateThread, t_programMain);
        //pthread_create(&threadId1, NULL, (THREADFUNCPTR) &GUIWindow::renderThread, t_programMain);
        m_threads.push_back(new std::thread(&GUIWindow::updateThread, t_programMain));
        m_threads.push_back(new std::thread(&GUIWindow::renderThread, t_programMain));

        ///m_threads.push_back(new boost::thread(boost::bind(&GUIWindow::updateThread, t_programMain)));
        ///m_threads.push_back(new boost::thread(boost::bind(&GUIWindow::renderThread, t_programMain)));
        printf("Engine::All threads for window %d %s",t_programMain->getWindowId(),"created\n");
        //m_threadIds.push_back(threadId0);
        //m_threadIds.push_back(threadId1);
        // Important to store in map after window->init() to hide from eventHandler
        // which otherwise could cause problems.
        m_windowsContainer.push_back(t_programMain);
        m_windowsMap[id] = t_programMain;

        return id;
    }
    else return 0;
}

/**
    public member.
    Joins all existing threads and is called while the Engine is being deconstructed.

    TODO: Test if any other object is being deconstructed before hand.
    Maybe this shouldnt be called in only destructor?

*/
void Engine::waitTillClosed(){
    printf("Starting thread joiner\n");
    for (unsigned i = 0; i < m_threads.size(); i++) {m_threads[i]->join();}
    printf("Starting destructor\n");
    //for (unsigned i = 0; i < m_threadIds.size(); i++) {pthread_join(m_threadIds[i], NULL);}
    ///for (unsigned i = 0; i < m_threads.size(); i++) {m_threads[i]->join();}
}



void Engine::handleSpriteEvent(SDL_Event& e){//return;
    return;
    ///dont do this anymore.
    GUIWindow* w = m_windowsMap[e.window.windowID];
    w->sprites->m_containerLock.lock();
    GUISprite* temp;

    GUISpriteGroup* spr = NULL;

    switch(e.type){
    case SDL_MOUSEMOTION:

        spr = w->sprites;
        for (int s = 0;s < spr->size();s++ )
        {
            temp = (*spr)[s];
            if (temp->m_mouseOver) // if entered before
                if ( w->m_mouse.isCollided(temp->m_rect) ) temp->onHover();
                else
                {
                    temp->m_mouseOver = false;
                    temp->onLeave();
                }
            else
            {
                if ( w->m_mouse.isCollided(temp->m_rect) )
                {
                    temp->m_mouseOver = true;
                    temp->onEnter();
                }
            }
        };
        break;
    case SDL_MOUSEBUTTONDOWN:

        spr = w->sprites;
        if (e.button.button == SDL_BUTTON_LEFT)

            for (int s = 0;s < spr->size();s++ )
            {
                temp = (*spr)[s];
                if ( w->m_mouse.isCollided(temp->m_rect) ){
                    temp->m_pressed = true;
                    temp->onPressed();
                }
                //temp->onClicked();
            }

        if (e.button.button == SDL_BUTTON_RIGHT)
            for (int s = 0;s < spr->size();s++ )
            {
                temp = (*spr)[s];
                if ( w->m_mouse.isCollided(temp->m_rect) ){
                    temp->m_pressed = true;
                    temp->onRightClicked();
                }
            }
        /*if (e.button.clicks == 2)
            if (e.button.button == SDL_BUTTON_LEFT)

                for (int s = 0;s < spr->size();s++ )
                {
                    temp = (*spr)[s];
                    temp->onDblClicked();
                }
        */

        break;
    case SDL_MOUSEBUTTONUP:
        spr = w->sprites;

        if (e.button.button == SDL_BUTTON_LEFT) //Change to switch-case statements?
        {
            for (int s = 0;s < spr->size();s++ )
            {   temp = (*spr)[s];

                if ( temp->m_pressed )
                    if ( w->m_mouse.isCollided(temp->m_rect) )
                    {   temp->m_pressed = false;
                        temp->onClicked(); // TODO: refer order from python.
                        temp->onReleased();
                    }
                //temp->onClicked();
            }

        }
        break;
    case SDL_KEYDOWN:
        printf("Physical %s key acting as %s key\n",
          SDL_GetScancodeName(e.key.keysym.scancode),
          SDL_GetKeyName(e.key.keysym.sym));
        /*spr = w->sprites();
        for (int s = 0;s < spr->size();s++ )
        {

        }*/
        break;
    case SDL_KEYUP:
        /*spr = w->sprites();
        switch (event.key.keysym.sym)
        {
            case SDLK_LEFT:  x--; break;
            case SDLK_RIGHT: x++; break;
            case SDLK_UP:    y--; break;
            case SDLK_DOWN:  y++; break;
        }*/
        break;

    }
    w->sprites->m_containerLock.unlock();
}
//void handleKeyPress()
/**
    waits for an event after confirming that atleast one window is alive.


*/
void Engine::startEventHandler(){
        std::map<int, GUIWindow*>::iterator it;// Coonstruct it only once to avoid input lag.

        GUIWindow* win = NULL;
        //Check if all windows are closed first before waiting for an event.
        while( !m_windowsMap.empty() && SDL_WaitEvent( &e ) )
        {   if(m_windowsMap.count(e.window.windowID))//Check if the window belonging to event exists.
            {   win = m_windowsMap[e.window.windowID];
                switch (e.type){ // Handle for
                case SDL_MOUSEMOTION:
                    win->m_mouse.x = e.motion.x;
                    win->m_mouse.y = e.motion.y;
                    printf("%d , %d\n", e.motion.x, e.motion.y);
                    break;
                default:
                    break;
                };

                ///handleSpriteEvent(e); Depreciated...

                win->handleEvent(e);
                win->sprites->handleEvent(e);
            }
            else{// Error
                printf("Event does not belong to any existing window\n");
            }
            //Check if any window is closed, and hence delete them from the map.
            ///If it deletes one window, it skips the next window's check.
            for (it=m_windowsMap.begin(); it!=m_windowsMap.end(); ++it)
            {
                if( it->second->isClosed() )
                    m_windowsMap.erase(it->first);
            }
        }
}
