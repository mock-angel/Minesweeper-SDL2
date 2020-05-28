#include "Button.h"
#include <functional>   // std::bind
#include <string>

ImageButton::ImageButton(){
    AddTexture("sprite", NULL);
    AddTexture("sprite_over", NULL);
    AddTexture("sprite_pressed", NULL); // pressed and over.
    AddTexture("sprite_disabled", NULL);

    std::function<void(void*)> fun = std::bind(&Button::emptyCallback, this, std::placeholders::_1);
    m_callbacks["onEnter"] = fun;
    m_callbacks["onOver"] = fun;
    m_callbacks["onPressed"] = fun;
    m_callbacks["onClicked"] = fun;
    m_callbacks["onReleased"] = fun;
    m_callbacks["onLeave"] = fun;

}
ImageButton::~ImageButton(){}
void ImageButton::update(){}
void ImageButton::emptyCallback(void* userdata){}

void ImageButton::AddTexture(const Str& str, SDL_Texture* t_texture)
{
    if (m_sprTextures.count(str) >= 1)
    {
        printf("Button::AddTexture: key allready exists.\n");
        return;
    }

    m_sprTextures[str] = t_texture;
}

void ImageButton::SetTexture(Str str, SDL_Texture* t_texture)
{
    if (m_sprTextures.count(str) == 0)
    {
        printf("Button::SetTexture: key non-existant.\n");
        return;
    }

    m_sprTextures[str] = t_texture;
    return;
}

/// TODO: Change return type.
void ImageButton::GetTexture(Str str)
{
    if (m_sprTextures.count(str) == 0)
    {
        printf("Button::GetTexture: key non-existant.\n");
        return;
    }
    reqTexture = m_sprTextures[str];
}

void ImageButton::onClicked()
{
    // Clicked callback.

    if (m_spriteSettingDisabled) return;


    m_callbacks["onClicked"](NULL);
}
void ImageButton::onReleased()
{   // Set to over.

    if (m_spriteSettingDisabled) return;

    GetTexture("sprite_over");
    if (reqTexture == NULL) return;
    setTexture(reqTexture);
    reqTexture = NULL;

    m_callbacks["onReleased"](NULL);
}
void ImageButton::onPressed(){

    if (m_spriteSettingDisabled) return;

    GetTexture("sprite_pressed");
    if (reqTexture == NULL) return;
    setTexture(reqTexture);
    reqTexture = NULL;

    m_callbacks["onPressed"](NULL);
}
void ImageButton::onRightClicked(){
    if (m_spriteSettingDisabled) return;


    m_callbacks["onRightClicked"](NULL);
}
void ImageButton::onHover(){

    if (m_spriteSettingDisabled) return;

    /// Texture allready set by button enter, or by released.

    m_callbacks["onOver"](NULL);
}
void ImageButton::onEnter(){

    if (m_spriteSettingDisabled) return;

    GetTexture("sprite_over");
    if (reqTexture == NULL) return;
    setTexture(reqTexture);
    reqTexture = NULL;

    m_callbacks["onEnter"](NULL);
}
void ImageButton::onLeave(){

    if (m_spriteSettingDisabled) return;

    GetTexture("sprite");
    if (reqTexture == NULL) return;
    setTexture(reqTexture);
    reqTexture = NULL;

    m_callbacks["onLeave"](NULL);
}









/*
void Button::handleEvent(SDL_Event& e){ //Event by collission.
    switch(e.type)
    {
    case (SDL_MOUSEMOTION):
        break;
    case (SDL_MOUSEBUTTONDOWN):     //mouse.down.

        break;
    case (SDL_MOUSEBUTTONUP):       //mouse.up
        break;
    }

};*/


