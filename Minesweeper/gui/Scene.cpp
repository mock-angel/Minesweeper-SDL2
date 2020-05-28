#include "Scene.h"
void Scene::setSceneId(unsigned int t_sceneId)
{
    m_sceneId = t_sceneId;
}
Scene::Scene(GUIWindow* win)  : GUISpriteHandler(win)
{
}
Scene::Scene() :  GUISpriteHandler(NULL)
{
}


SceneHandler::SceneHandler(GUIWindow* win): window(win)
{
    createScene(0, "Default");
    switchScene(0);
}/*
SceneHandler::SceneHandler()
{
    createScene(0, "Default");
}
void SceneHandler::setWindow(GUIWindow* win)
{
    window = win;
}*/
SceneHandler::~SceneHandler()
{
    for (std::map<unsigned int, Scene*>::iterator it=m_scenes.begin(); it!=m_scenes.end(); ++it)
    {
        delete it->second;
        it->second = NULL;
    }
}
void SceneHandler::createScene(unsigned int t_, Str t_sceneName){
    m_sceneHandlerLock.lock();
    // TODO: Check if t_ is allready there.
    m_scenes[t_] = new Scene(window);
    m_sceneHandlerLock.unlock();
}
void SceneHandler::switchScene(unsigned int t_){// TODO: Check if t_ is not there.
    m_sceneHandlerLock.lock();
    m_currentSceneId = t_;
    if (m_scenes[t_]!=NULL) m_currentScene = m_scenes[t_];
    m_sceneHandlerLock.unlock();
}

void SceneHandler::update(){
    ///m_sceneHandlerLock.lock();
    if (m_currentScene!=NULL) m_currentScene->update();
    ///m_sceneHandlerLock.unlock();
}
void SceneHandler::render(SDL_Texture* t_texture){
    ///m_sceneHandlerLock.lock();
    if (m_currentScene!=NULL) m_currentScene->render(t_texture);
    ///m_sceneHandlerLock.unlock();
}
void SceneHandler::render(){
    ///m_sceneHandlerLock.lock();
    if (m_currentScene!=NULL) m_currentScene->render();
    ///m_sceneHandlerLock.unlock();
}
void SceneHandler::add(GUISprite* spr)
{   //Not multithread friendly.
    //Udage: Use only during init of app.
    if (spr!=NULL) m_currentScene->add(spr);
    else printf("SceneHandler::add(GUISprite* spr): Tried to pass NULL GlmObject\n");
}
void SceneHandler::handleEvent(SDL_Event& e)
{
    if (m_currentScene!=NULL) m_currentScene->handleEvent(e);
}

