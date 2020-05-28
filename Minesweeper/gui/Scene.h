#ifndef SCENE_INCLUDED
#define SCENE_INCLUDED

///#include "precompiled.h"
#include "GUISprite.h"

class Scene: public GUISpriteHandler
{
    Str n_name;
    unsigned int m_sceneId;

public:
    Scene(GUIWindow* win);
    Scene();
    void setWindow(GUIWindow* win);

    void setSceneId(unsigned int t_sceneId);
};

class SceneHandler{

    std::map<unsigned int, Scene*> m_scenes;
    std::mutex m_sceneHandlerLock;
    GUIWindow* window;
    unsigned int m_currentSceneId = 0;
    Scene* m_currentScene = NULL; //Needs to be updated to current scene.

public:
    ///SceneHandler();
    ~SceneHandler();
    SceneHandler(GUIWindow* win);
    ///void setWindow(GUIWindow* win);

    void createScene(unsigned int t_, Str t_sceneName);

    void switchScene(unsigned int t_);

    void add(GUISprite* spr);
    void handleEvent(SDL_Event& e);

    void update();
    void render(SDL_Texture* t_texture);
    void render();
};
#endif //SCENE_INCLUDED
