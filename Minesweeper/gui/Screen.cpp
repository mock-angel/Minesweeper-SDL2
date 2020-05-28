#include "Screen.h"

void GOScene::switchScene(int screenId)
{
    m_screenLock.lock();
    if (m_currentGroup != NULL)
    {
        m_currentGroup->disable();
        m_currentGroup->setVisible(false);
    }
    GUISpriteGroup* tempGroupPtr = getSceneSprites(screenId);
    if (tempGroup==NULL) return;
    
    m_currentGroup = tempGroupPtr;
    m_currentScreenId = screenId;
    m_screenLock.unlock();
}
void GOScene::add(int screenId, GUISprite* t_sprite)
{
    m_screenLock.lock();
    GUISpriteGroup* tempGroupPtr = getSceneSprites(screenId)
    if (tempGroup!=NULL) tempGroupPtr->add(t_sprite);
    m_screenLock.unlock();
}
void GOScene::draw(SDL_Surface* t_surface)
{
    m_screenLock.lock();
    if (m_currentGroup != NULL)
        m_currentGroup->draw(t_surface);
    m_screenLock.unlock();
}
void GOScene::render(SDL_Texture* t_texture)
{
    m_screenLock.lock();
    if (m_currentGroup != NULL)
        m_currentGroup->render(t_texture);
    m_screenLock.unlock();
}
GUISpriteGroup* GOScene::getSceneSprites(int screenId)
{
    if(m_spriteGroups.count(screenId) != 0)
        return m_spriteGroups[screenId];
    
    return NULL;
}
