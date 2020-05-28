
#ifndef INCLUDE_GUIWindowProgram
#define INCLUDE_GUIWindowProgram

#include <map>
#include "GUI.h"
#include "Tile.h"


enum ScreenEnum{
    GAME_SCREEN,
    SELECTION_SCREEN,
    CUSTOM_SCREEN
};
class GUIWindowProgram : public GUIWindow {
public:
    GUIWindowProgram();
    ~GUIWindowProgram();

private:
    void update();
    void render();
    void draw();

    void init_sprites();

    TileGroup* m_tileGroup;

    /* User data memebers/functions */
    std::map<Str, SDL_Texture*> textures;

};
#endif
