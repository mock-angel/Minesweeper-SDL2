#ifndef INCLUDED_BUTTON_
#define INCLUDED_BUTTON_

#include <boost/optional.hpp>
#include <boost/bind.hpp>
#include <atomic>
//class BackgroundManagement{ // Use this for rendering of background.
//#include <shared_mutex>



//};
#include "GUI.h"
#include "precompiled.h"
class GUIWindow;

enum RenderStateEnum{
    SPRITE_DEFAULT,
    SPRITE_OVER,
    SPRITE_PRESSED,
    SPRITE_DISABLED
};

class ButtonBehaviour: public GUISprite{
    std::map<Str, SDL_Texture*> m_sprTextures;
    std::map<Str, SDL_Surface*> m_sprSurfaces;

    bool m_spriteSettingDisabled = false;///Need a disable/enable function for this.

    SDL_Texture* reqTexture = NULL;
    SDL_Surface* reqSurface = NULL;

    SDL_Surface* selectedSurface = NULL;

    //callback.
    void emptyCallback(void*);
    std::map<std::string, std::function<void(void*)>> m_callbacks;

    virtual void generateButtonSprite();

    void AddTexture(const Str&, SDL_Texture*);
    void SetTexture(Str, SDL_Texture*);
    SDL_Texture* GetTexture(Str);

    SDL_Surface* GetSurface(Str);///Render thread only.

protected:
    std::mutex m_surfaceLock; // TODO: Change to sprite lock?

    std::atomic<bool> buffer_flag;
    bool m_dirty = true;

    void updateTextures();

public:
    ButtonBehaviour(GUIWindow*);

    void AddSurface(const Str&, SDL_Surface*);  ///
    void SetSurface(Str, SDL_Surface*); ///thread friendly.
    void SelectSurface(Str str);        ///For user only.

    virtual void handleEvent(SDL_Event& e){};

    /// TODO: Implement to work with callbacks and inheritance.
    void clicked(std::function<void(void*)> t_callback);

    void onClicked();
    void onReleased();
    void onPressed();
    void onRightClicked();
    void onHover();
    void onEnter();
    void onLeave();

    std::atomic<RenderStateEnum> renderState;

    void render();
};

class Button:public ButtonBehaviour{
    Str m_text;

    void generateButtonSprite();    ///virtual.

public:
    Button(GUIWindow*);
    ~Button();

    /// Main usable functions.
    void setText(Str t_text);
    char* text();
};

/**         ImageButton         **/
class ImageButton:public ButtonBehaviour{
    //void generateButtonSprite();    ///virtual.

public:
    ImageButton(GUIWindow*);
    ~ImageButton();

    //void handleEvent(SDL_Event& e){};
};
#endif // INCLUDED_BUTTON
