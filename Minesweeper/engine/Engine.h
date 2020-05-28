#ifndef INCLUDED_ENGINE
#define INCLUDED_ENGINE
#include <map>
#include <pthread.h>
#include <boost/thread.hpp>
///libboost-thread-dev
///#include <boost/date_time.hpp>
#include <vector>
#include "GUI.h"

class Engine {
    /*
        m_programsWindowObject[id] = &SDL_window
        e
        m_windowCount // removed
        m_maxThreadCount // removed
        m_threadCount  //removed
        m_threads <-- TODO: Use vector instead of arrays
    */
    std::map<int, GUIWindow*> m_windowsMap; //Used by eventHandler. Only windows that may accept events will be stored here.
    std::vector<GUIWindow*> m_windowsContainer;
    std::vector<std::thread*> m_threads;
    ///std::vector<pthread_t> m_threadIds;
    ///std::vector<boost::thread*> m_threads;
    SDL_Event e;

    void handleSpriteEvent(SDL_Event& e);

public:
    Engine();
    ~Engine();
    // Interface initialisation.
    bool init();

    // Program ...
    int addProgram(GUIWindow* t_programMain);
    void waitTillClosed();
    void startEventHandler();

    //getters.
    GUIWindow* getWindowById(unsigned t_id);


};

#endif // INCLUDED_ENGINE
