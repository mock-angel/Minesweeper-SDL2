#ifndef INCLUDED_TILE
#define INCLUDED_TILE

#include "Button.h"
#include "MineField.h"
#include "GolMath.h"
class Tile: public ImageButton
{
    PosRC m_pos;

public:
    int m_value;

    static SDL_Surface * defaultSurface;
    static SDL_Surface * defaultOverSurface;
    static SDL_Surface * defaultpressedSurface;
    static PosXY offset_xy;
    static std::map<int, std::map<Str, SDL_Surface*>> surfaceMap;

    void setValue(int value);
    int getValue();

    Tile(GUIWindow* t_window, int r, int c);
    PosRC getPos();
    void blast();
    void reveal();
};

class TileGroup: public virtual GUISpriteGroup
{
    bool m_constructed = false;

    ///std::vector<Tile*> m_container;

    int m_totalMineCount = 0;
    std::pair<int, int> m_sizeRC;

    MineField m_mineField;

    GUIWindow* m_cWindow;

public:
    TileGroup(GUIWindow* t_window);
    void generateTiles(int t_mineCount, std::pair<int, int> t_sizeRC);
    void destroyTiles();

    void pause();
    void resume();

    void cTouched(Tile* t_tile);
    Tile* findTile(int r, int c);

};

#endif // INCLUDED_TILE
