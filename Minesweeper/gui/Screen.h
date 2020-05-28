#ifndef GOSCREEN_INCLUDED
#define GOSCREEN_INCLUDED
class GOScene // GOScreen
{
    std::mutex m_screenLock;
    std::map<int, GUISpriteGroup*> m_spriteGroups;
    GUISpriteGroup* m_currentGroup = NULL;
    int m_currentScreenId;
    
public:
    void switchScene(int screenId);
    void add(int screenId, GUISprite* t_sprite);
    void draw(SDL_Surface* t_surface);
    void render(SDL_Texture* t_texture);
}
#endif // GOSCREEN_INCLUDED
