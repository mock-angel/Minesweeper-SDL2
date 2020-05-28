#ifndef INCLUDED_BUTTON_
#define INCLUDED_BUTTON_

#include <boost/optional.hpp>
#include <boost/bind.hpp>

//class BackgroundManagement{ // Use this for rendering of background.



//};
#include "GUI.h"
#include "precompiled.h"

/// Img button <-- convert to this name.
class ImageButton:public GUISprite{

    std::map<Str, SDL_Texture*> m_sprTextures;

    std::map<std::string, std::function<void(void*)>> m_callbacks;

    bool m_spriteSettingDisabled = false;

    //calbaclk.
    void emptyCallback(void*);

    SDL_Texture* reqTexture = NULL;

public:
    Button();
    ~Button();

    void AddTexture(const Str&, SDL_Texture*);
    void SetTexture(Str, SDL_Texture*);
    void GetTexture(Str);

    void handleEvent(SDL_Event& e){};
    void update();
    //void render(){}

    /// TODO: Implement to work with callbacks and inheritance.
    void onClicked();
    void onReleased();
    void onPressed();
    void onRightClicked();
    void onHover();
    void onEnter();
    void onLeave();
};
#endif // INCLUDED_BUTTON
