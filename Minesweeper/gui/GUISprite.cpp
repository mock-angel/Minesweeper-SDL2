#include "GUISprite.h"
#include <algorithm> // for std::count

#include "GUIWindow.h"

GUISprite::GUISprite(GUIWindow* t_window): m_spriteTexture(NULL), m_spriteSurface(NULL)//;m_rect = new Rect(); m_rect->dissolve();
{
    m_cRenderer = t_window->getRenderer();
}

void GUISprite::setTexture(SDL_Texture* t_texture){
    m_spriteTexture = t_texture;
    SDL_QueryTexture(t_texture, NULL, NULL, &m_rect->w, &m_rect->h);
}
void GUISprite::setRenderer(SDL_Renderer* t_pRenderer){
    m_cRenderer = t_pRenderer;
}

void GUISprite::setVisible(bool t_visible)
{
    m_visible = t_visible;
}
void GUISprite::disable()
{
    m_disabled = true;
}
void GUISprite::enable()
{
    m_disabled = true;
}
bool GUISprite::isDisabled()
{
    return m_disabled;
}

/**
    Sprite's basic draw function for screen, can be optionally derived.
    Is virtual.
*/
void GUISprite::draw(SDL_Surface* t_surface){
    SDL_BlitSurface(m_spriteSurface, NULL, t_surface, m_rect);
}
void GUISprite::render(SDL_Texture* t_texture){
    SDL_SetRenderTarget( m_cRenderer, t_texture );
    SDL_RenderCopy(m_cRenderer, m_spriteTexture, NULL, m_rect);
    SDL_SetRenderTarget( m_cRenderer, NULL );
}
void GUISprite::render(){
    if (!m_visible) return;
    if (SDL_RenderCopy(m_cRenderer, m_spriteTexture, NULL, m_rect)<0)
        printf("%s\n", SDL_GetError());
}



GUISprite* &GUISpriteGroup::operator[] (int i){
    return m_container[i];
}

void GUISpriteGroup::add(GUISprite* t_sprite){
    m_containerLock.lock();
    if(!(m_cRenderer == NULL)) t_sprite->setRenderer(m_cRenderer);

    if(!(std::count(m_container.begin(), m_container.end(), t_sprite)))
        m_container.push_back(t_sprite);
    m_containerLock.unlock();
}
void GUISpriteGroup::add(GUISpriteGroup* t_spriteGroup){
    m_containerLock.lock();
    if(!(m_cRenderer == NULL))
        t_spriteGroup->setRenderer(m_cRenderer);

    GUISprite* sprite = NULL;

    std::vector<GUISprite*> sprites = t_spriteGroup->sprites();

    for (unsigned int i = 0; i<sprites.size(); i++)
    {
        sprite = sprites[i];
        if(!(std::count(m_container.begin(), m_container.end(), sprite)))
            m_container.push_back(sprite);
    }
    m_containerLock.unlock();
}

void GUISpriteGroup::update(){
    for(std::vector<GUISprite*>::iterator it = m_container.begin();it!=m_container.end();++it)
        (*it)->update();
}
int GUISpriteGroup::size(){
    return m_container.size();
}
std::vector<GUISprite*> GUISpriteGroup::sprites(){
    return m_container;
}

/**
    All render and draw functions.
    render for texture
    draw for surface.
    TODO: Optional update
*/
void GUISpriteGroup::draw(SDL_Surface* t_surface){

    for(std::vector<GUISprite*>::iterator it = m_container.begin();it!=m_container.end();++it)
        (*it)->draw(t_surface);
}
void GUISpriteGroup::render(SDL_Texture* t_texture){

    for(std::vector<GUISprite*>::iterator it = m_container.begin();it!=m_container.end();++it)
        (*it)->render(t_texture);
}
void GUISpriteGroup::render(){

    for(std::vector<GUISprite*>::iterator it = m_container.begin();it!=m_container.end();++it)
        (*it)->render();
}







GUISpriteHandler::GUISpriteHandler(GUIWindow* win)
{
    window = win;
}

void GUISpriteHandler::handleEvent(SDL_Event& e)
{
    ///This makes sure that the event is processed by the window only if it belongs to it.
    if (e.window.windowID != window->getWindowId()) return;
    //return;
    GUISprite* temp = NULL;
    GUISpriteGroup* spr = NULL;

    m_containerLock.lock();
    switch(e.type){
    case SDL_MOUSEMOTION:
        spr = window->sprites;
        for (int s = 0;s < spr->size();s++ )
        {
            temp = (*spr)[s];
            if (temp->m_mouseOver) // if entered before
                if ( window->m_mouse.isCollided(temp->m_rect) )
                    temp->onHover();
                else
                {
                    temp->m_mouseOver = false;
                    temp->onLeave();
                }
            else{
                if ( window->m_mouse.isCollided(temp->m_rect) )
                {
                    temp->m_mouseOver = true;
                    temp->onEnter();
                }
            }
        };
        break;
    case SDL_MOUSEBUTTONDOWN:

        spr = window->sprites;

        if (e.button.button == SDL_BUTTON_LEFT)

            for (int s = 0;s < spr->size();s++ )
            {
                temp = (*spr)[s];
                if ( window->m_mouse.isCollided(temp->m_rect) ){
                    temp->m_pressed = true;
                    temp->onPressed();
                }
                //temp->onClicked();
            }

        if (e.button.button == SDL_BUTTON_RIGHT)
            for (int s = 0;s < spr->size();s++ )
            {
                temp = (*spr)[s];
                if ( window->m_mouse.isCollided(temp->m_rect) ){
                    temp->m_pressed = true;
                    temp->onRightClicked();
                }
            }
        break;
    case SDL_MOUSEBUTTONUP:
        spr = window->sprites;

        if (e.button.button == SDL_BUTTON_LEFT) //Change to switch-case statements?
        {
            for (int s = 0;s < spr->size();s++ )
            {   temp = (*spr)[s];

                if ( temp->m_pressed )
                    if ( window->m_mouse.isCollided(temp->m_rect) )
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
    m_containerLock.unlock();
}
void GUISpriteHandler::setWindow(GUIWindow* win)
{
    window = win;
}
GUIWindow* GUISpriteHandler::getWindow()
{
    return window;
}
