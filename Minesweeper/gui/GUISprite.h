#ifndef INCLUDED_SPRITE
#define INCLUDED_SPRITE

#include <vector>
#include <map>
#include <mutex>
#include <SDL2/SDL.h>

#include "precompiled.h"
#include "GUIEvent.h"
///#include "Scene.h"
class GUIWindow;

class GUISprite : public GUIEventObject{
    bool m_visible = true;
    bool m_disabled = false;
    ColorRGB m_bgColor;
protected:
    SDL_Texture* m_spriteTexture = NULL;
    SDL_Surface* m_spriteSurface = NULL; // dunmmy.

    SDL_Renderer* m_cRenderer = NULL;
public:
    Rect* m_rect = new Rect;

    GUISprite(GUIWindow * t_window);

    ~GUISprite(){};
    void setRenderer(SDL_Renderer* t_pRenderer);
    SDL_Renderer* getRenderer(){return m_cRenderer;};
    void setTexture(SDL_Texture* t_texture);
    virtual void handleEvent(SDL_Event& e){};
    virtual void update(){};
    virtual void draw(SDL_Surface* t_surface);
    virtual void render(SDL_Texture* t_texture);
    virtual void render();

    void setVisible(bool t_visible);    ///Sets if needs to be rendered
    void disable();
    void enable();
    bool isDisabled();                  ///Doesnt accept events if disabled.
};

class GUISpriteGroup{

    std::vector<GUISprite*> m_container;
    SDL_Renderer* m_cRenderer = NULL;
public:

    std::mutex m_containerLock;
    void setRenderer(SDL_Renderer* t_pRenderer){m_cRenderer = t_pRenderer;};

    std::vector<GUISprite*> sprites();

    int size();
    GUISprite* &operator[] (int i);

    void add(GUISprite* t_sprite);
    void add(GUISpriteGroup* t_spriteGroup);
    void update();

    void draw(SDL_Surface* t_surface);
    void render(SDL_Texture* t_texture);
    void render();
};

class GUISpriteHandler: public GUISpriteGroup{
    ///std::vector<GUISprite*> m_container;
    std::vector<GUISprite*> m_diabledSprites;   /// Won't recieve updates/ nor GuiEvents.
    std::vector<GUISprite*> m_enabledSprites;   /// The sprites that are enabled, can recieve GuiEvents and update calls.
    std::vector<GUISprite*> m_invisibleSprites; /// The sprites that arent recieving render calls from window.
    std::vector<GUISprite*> m_visibleSprites;   /// The sprites that recieve render calls.
    GUIWindow* window = NULL;

public:
    GUISpriteHandler(GUIWindow* win);
    ///void handleEvent(SDL_Event& e);
    virtual void handleEvent(SDL_Event& e);
    void setWindow(GUIWindow* win);
    GUIWindow* getWindow();
};
#endif // INCLUDED_SPRITE
