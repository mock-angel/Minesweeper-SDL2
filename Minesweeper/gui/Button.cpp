#include "Button.h"
#include <functional>   // std::bind
#include <string>
#include "Text.h"


void ButtonBehaviour::emptyCallback(void* userdata){}

ButtonBehaviour::ButtonBehaviour(GUIWindow* t_window): GUISprite(t_window){
    buffer_flag = false;
    // Used internally
    AddTexture("sprite", NULL);         //Acts as buffer sprites.
    AddTexture("sprite_over", NULL);
    AddTexture("sprite_pressed", NULL); // pressed and over.
    AddTexture("sprite_disabled", NULL);

    //We work on surfaces. Then after setting it it gets destroyed after use.
    AddSurface("sprite", NULL);
    AddSurface("sprite_over", NULL);
    AddSurface("sprite_pressed", NULL);
    AddSurface("sprite_disabled", NULL);

    std::function<void(void*)> fun = std::bind(&ButtonBehaviour::emptyCallback, this, std::placeholders::_1);
    m_callbacks["onEnter"] = fun;
    m_callbacks["onOver"] = fun;
    m_callbacks["onPressed"] = fun;
    m_callbacks["onClicked"] = fun;
    m_callbacks["onReleased"] = fun;
    m_callbacks["onLeave"] = fun;
    m_callbacks["onRightClicked"] = fun;

    renderState = SPRITE_DEFAULT;
}

void ButtonBehaviour::generateButtonSprite(){}

/// Used Explicitly by Button.   Add locks here too.
void ButtonBehaviour::AddTexture(const Str& str, SDL_Texture* t_texture)
{
    if (m_sprTextures.count(str) >= 1)
    {
        printf("Button::AddTexture: key allready exists.\n");
        return;
    }

    m_sprTextures[str] = t_texture;
}
void ButtonBehaviour::SetTexture(Str str, SDL_Texture* t_texture)
{   ///Render thread Only.
    if (m_sprTextures.count(str) == 0)
    {
        printf("Button::SetTexture: key non-existant.\n");
        return;
    }

    m_sprTextures[str] = t_texture;
    return;
}
SDL_Texture* ButtonBehaviour::GetTexture(Str str)
{   ///Render thread Only.
    if (m_sprTextures.count(str) == 0)
    {
        printf("Button::GetTexture: key non-existant.\n");
        return NULL;
    }
    reqTexture = m_sprTextures[str];
    return m_sprTextures[str];
}

/// Use these to tell Button to create a texture and display in render thread.
void ButtonBehaviour::AddSurface(const Str& str, SDL_Surface* t_surface)
{
    std::unique_lock<std::mutex> lock (m_surfaceLock);

    if (m_sprSurfaces.count(str) >= 1)
    {
        printf("Button::AddSurface: key allready exists.\n");
        return;
    }

    m_sprSurfaces[str] = t_surface;
    if (t_surface != NULL) buffer_flag = true;

}
void ButtonBehaviour::SetSurface(Str str, SDL_Surface* t_surface)
{   ///Any thread.
    std::lock_guard<std::mutex> lock (m_surfaceLock);
    if (m_sprSurfaces.count(str) == 0)
    {
        printf("Button::SetSurface: key non-existant.\n");
        return;
    }

    m_sprSurfaces[str] = t_surface;
    if (t_surface != NULL)  {
        ///while(buffer_flag)printf("waiting\n");//Wait till bufferflag is reset to false.
        buffer_flag = true;
    }
}
SDL_Surface* ButtonBehaviour::GetSurface(Str str)
{   ///Render thread Only.
    std::lock_guard<std::mutex> lock (m_surfaceLock);
    if (m_sprSurfaces.count(str) == 0)
    {
        printf("Button::GetSurface: key non-existant.\n");
        return NULL;
    }
    reqSurface = m_sprSurfaces[str];
    return m_sprSurfaces[str];
}

void ButtonBehaviour::SelectSurface(Str str)
{   ///Any thread Only.
    //std::unique_lock<std::mutex> lock (m_surfaceLock);
    m_surfaceLock.lock();
    if (m_sprSurfaces.count(str) == 0)
    {
        printf("Button::SelectSurface: key non-existant.\n");
        m_surfaceLock.unlock();
        return;
    }
    selectedSurface = m_sprSurfaces[str];
    m_surfaceLock.unlock();
}

void ButtonBehaviour::updateTextures()
{   ///Render thread Only.
    GetSurface("sprite");
    if (reqSurface != NULL)
    {
        SDL_Texture* createdTexture = SDL_CreateTextureFromSurface(m_cRenderer, reqSurface);
        if (createdTexture != NULL) SetTexture("sprite", createdTexture );
    }

    GetSurface("sprite_over");
    if (reqSurface != NULL)
    {
        SDL_Texture* createdTexture = SDL_CreateTextureFromSurface(m_cRenderer, reqSurface);
        if (createdTexture != NULL) SetTexture("sprite_over", createdTexture );
    }

    GetSurface("sprite_pressed");
    if (reqSurface != NULL)
    {
        SDL_Texture* createdTexture = SDL_CreateTextureFromSurface(m_cRenderer, reqSurface);
        if (createdTexture != NULL) SetTexture("sprite_pressed", createdTexture );
    }

    GetSurface("sprite_disabled");
    if (reqSurface != NULL)
    {
        SDL_Texture* createdTexture = SDL_CreateTextureFromSurface(m_cRenderer, reqSurface);
        if (createdTexture != NULL) SetTexture("sprite_disabled", createdTexture );
    }
    reqSurface = NULL;

    switch(renderState)
    {
    case (SPRITE_DEFAULT):
        GetTexture("sprite");
        if (reqTexture != NULL) m_spriteTexture = reqTexture;
        SDL_QueryTexture(m_spriteTexture, NULL, NULL, &m_rect->w, &m_rect->h); ///Check this line.
        break;

    case (SPRITE_OVER):
        GetTexture("sprite_over");
        if (reqTexture != NULL) m_spriteTexture = reqTexture;
        break;

    case (SPRITE_PRESSED):
        GetTexture("sprite_pressed");
        if (reqTexture != NULL) m_spriteTexture = reqTexture;
        break;

    case (SPRITE_DISABLED):
        GetTexture("sprite_disabled");
        if (reqTexture != NULL) m_spriteTexture = reqTexture;
        break;
    }

    reqTexture = NULL;

    if(buffer_flag)
        printf("OMG BUFFER FLAG ACTIVE");
}

void ButtonBehaviour::clicked(std::function<void(void*)> t_callback)
{
    m_callbacks["onClicked"] = t_callback;


}


/// CALLBACKS
void ButtonBehaviour::onClicked()    ///Event thread Only.
{
    // Clicked callback.
    printf("onClicked\n");
    if (m_spriteSettingDisabled) return;

    m_callbacks["onClicked"](NULL);
}
void ButtonBehaviour::onReleased()   ///Event thread Only.
{   // Set to over.
    printf("onReleased\n");
    if (m_spriteSettingDisabled) return;

    m_surfaceLock.lock();
    renderState = SPRITE_OVER;
    buffer_flag = true;
    m_surfaceLock.unlock();

    m_callbacks["onReleased"](NULL);
}
void ButtonBehaviour::onPressed()    ///Event thread Only.
{
    printf("onPressed\n");
    if (m_spriteSettingDisabled) return;

    m_surfaceLock.lock();
    renderState = SPRITE_PRESSED;
    buffer_flag = true;
    m_surfaceLock.unlock();

    m_callbacks["onPressed"](NULL);
}
void ButtonBehaviour::onRightClicked()   ///Event thread Only.
{
    printf("onRightClicked\n");
    if (m_spriteSettingDisabled) return;

    m_callbacks["onRightClicked"](NULL);
}
void ButtonBehaviour::onHover()  ///Event thread Only.
{
    printf("onHover\n");
    if (m_spriteSettingDisabled) return;

    /// Texture allready set by button enter, or by released.

    m_callbacks["onOver"](NULL);
}
void ButtonBehaviour::onEnter(){ ///Event thread Only.
    printf("onEnter\n");
    if (m_spriteSettingDisabled) return;

    m_surfaceLock.lock();
    renderState = SPRITE_OVER;
    buffer_flag = true;
    m_surfaceLock.unlock();

    m_callbacks["onEnter"](NULL);
}

void ButtonBehaviour::onLeave()  ///Event thread Only.
{
    printf("onLeave\n");
    if (m_spriteSettingDisabled) return;

    m_surfaceLock.lock();
    renderState = SPRITE_DEFAULT;
    buffer_flag = true;
    m_surfaceLock.unlock();

    m_callbacks["onLeave"](NULL);
}

void ButtonBehaviour::render()
{   ///Render thread Only.

    if (m_dirty) {
        m_dirty = false;
        generateButtonSprite();
    }

    if (buffer_flag) {
        //m_surfaceLock.lock();
        buffer_flag = false;
        //m_surfaceLock.unlock();
        updateTextures();
    }

    if (SDL_RenderCopy(m_cRenderer, m_spriteTexture, NULL, m_rect)<0)
        printf("%s\n", SDL_GetError());
}

/**         Button         **/
Button::Button(GUIWindow* t_window): ButtonBehaviour(t_window)
{
    setText(" ");
}

Button::~Button(){}

void Button::setText(Str t_text)
{
    m_text = t_text;

    m_dirty = true;
}

char* Button::text(){
    return const_cast<char*>(m_text.c_str());
}

void Button::generateButtonSprite()
{
    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif
    renderState = SPRITE_DEFAULT;

    SDL_Surface* createdSurf = SDL_CreateRGBSurface(0, 100, 40, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(createdSurf, NULL, SDL_MapRGB(createdSurf->format, 72, 72, 72));
    // After set text...
    ///SDL_Surface* text = loadText("Hello");
    ///SDL_BlitSurface(text, NULL, createdSurf, NULL);

    ///t.draw(createdSurf);

    TextWall tt;
    tt.addLine("Hell");
    tt.addLine("Hell's kitchen");
    tt.draw(createdSurf);
    SetSurface("sprite", createdSurf);

    createdSurf = SDL_CreateRGBSurface(0, 100, 40, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(createdSurf, NULL, SDL_MapRGB(createdSurf->format, 80, 80, 80));
    if (createdSurf == NULL) printf("%s\n", SDL_GetError());
    SetSurface("sprite_over", createdSurf);
}


/**         ImageButton         **/
ImageButton::ImageButton(GUIWindow* t_window): ButtonBehaviour(t_window){}
ImageButton::~ImageButton(){}

