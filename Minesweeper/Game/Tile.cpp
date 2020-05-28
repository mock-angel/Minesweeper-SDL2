#include "Tile.h"

SDL_Surface * Tile::defaultSurface = NULL;
SDL_Surface * Tile::defaultOverSurface = NULL;
SDL_Surface * Tile::defaultpressedSurface = NULL;
std::map<int, std::map<Str, SDL_Surface*>> Tile::surfaceMap;
PosXY Tile::offset_xy;

Tile::Tile(GUIWindow* t_window, int r, int c):ImageButton(t_window){
    ///Load surfaces.
    m_pos.r = r;
    m_pos.c = c;

    SetSurface("sprite", defaultSurface);
    SetSurface("sprite_over", defaultOverSurface);
    SetSurface("sprite_pressed", defaultpressedSurface);
    SetSurface("sprite_disabled", defaultSurface);
}
PosRC Tile::getPos()
{
    return m_pos;
}
void Tile::setValue(int value)
{
    m_value = value;
}
int Tile::getValue()
{
    return m_value;
}
void Tile::reveal()
{
    SetSurface("sprite", surfaceMap[m_value]["sprite"]);
    SetSurface("sprite_over", surfaceMap[m_value]["sprite_over"]);
    SetSurface("sprite_pressed", surfaceMap[m_value]["sprite_pressed"]);
    //SelectSurface("sprite");
    //SelectSurface("sprite_over");
    //SelectSurface("sprite_pressed");
}
void Tile::blast()
{
    if (m_value >= 13 and m_value != 20)
    {
        SetSurface("sprite", surfaceMap[14]["sprite"]);
        SetSurface("sprite_over", surfaceMap[14]["sprite_over"]);
        SetSurface("sprite_pressed", surfaceMap[14]["sprite_pressed"]);

    } else if (m_value == 20)
    {
        SetSurface("sprite", surfaceMap[13]["sprite"]);
        SetSurface("sprite_over", surfaceMap[13]["sprite_over"]);
        SetSurface("sprite_pressed", surfaceMap[13]["sprite_pressed"]);
    }
}

TileGroup::TileGroup(GUIWindow* t_window)
{
    m_cWindow = t_window;
    m_mineField = MineField();
}

void TileGroup::generateTiles(int t_mineCount, std::pair<int, int> t_sizeRC)
{
    m_mineField.clear();
    m_mineField.createMatrix(t_sizeRC.first, t_sizeRC.second);

    Tile* createdTile = NULL;
    for (int r = 0; r<t_sizeRC.first; r++)
        for (int c = 0; c<t_sizeRC.second; c++)
        {
            createdTile = new Tile(m_cWindow, r, c);

            //Connect the clicked signal.
            createdTile->clicked(std::bind(&TileGroup::cTouched, this, createdTile));

            //Set position.
            createdTile->m_rect->move(c*33 + Tile::offset_xy.x, r*33 + Tile::offset_xy.y);

            add(createdTile);
        }
    m_totalMineCount = t_mineCount;
}

void TileGroup::cTouched(Tile* t_tile)
{
    if (not m_constructed)
    {
        m_mineField.layMine(m_totalMineCount, t_tile->getPos());
        std::vector<GUISprite*> sprts = sprites();

        Tile* spr = NULL;
        for (unsigned int i = 0; i<sprts.size(); i++)
        {
            spr = (Tile*)sprts[i];
            spr->setValue( m_mineField.getValue(spr->getPos().r, spr->getPos().c));
        }
        m_constructed = true;

    }
    if(t_tile->getValue() >= 13)
    {   //game lost.
        printf("Game Lost \n");
        /// Lost Game operations.

        t_tile->m_value = 20; //20 means it can it needs a red mine.
        std::vector<GUISprite*> sprts = sprites();
        Tile* spr = NULL;
        for (unsigned int i = 0; i<sprts.size(); i++)
        {
            spr = (Tile*)sprts[i];
            spr->blast();
        }
    }
    else
    {
        Tile* tempTile = t_tile;
        PosRC pos;
        std::vector<Tile*> tileList;
        unsigned int i = 0;
        tileList.push_back(t_tile);
        do
        {
            tempTile = tileList[i++];
            tempTile->reveal();
            if(tempTile->getValue() == 0)
            {   pos = tempTile->getPos();

                tempTile = findTile(pos.r + 1, pos.c);
                if (tempTile!= NULL and std::find(tileList.begin(), tileList.end(), tempTile) == tileList.end()) tileList.push_back(tempTile);
                tempTile = findTile(pos.r - 1, pos.c);
                if (tempTile!= NULL and std::find(tileList.begin(), tileList.end(), tempTile) == tileList.end()) tileList.push_back(tempTile);
                tempTile = findTile(pos.r, pos.c + 1);
                if (tempTile!= NULL and std::find(tileList.begin(), tileList.end(), tempTile) == tileList.end()) tileList.push_back(tempTile);
                tempTile = findTile(pos.r, pos.c - 1);
                if (tempTile!= NULL and std::find(tileList.begin(), tileList.end(), tempTile) == tileList.end()) tileList.push_back(tempTile);
                tempTile = findTile(pos.r - 1, pos.c - 1);
                if (tempTile!= NULL and std::find(tileList.begin(), tileList.end(), tempTile) == tileList.end()) tileList.push_back(tempTile);
                tempTile = findTile(pos.r + 1, pos.c - 1);
                if (tempTile!= NULL and std::find(tileList.begin(), tileList.end(), tempTile) == tileList.end()) tileList.push_back(tempTile);
                tempTile = findTile(pos.r - 1, pos.c + 1);
                if (tempTile!= NULL and std::find(tileList.begin(), tileList.end(), tempTile) == tileList.end()) tileList.push_back(tempTile);
                tempTile = findTile(pos.r + 1, pos.c + 1);
                if (tempTile!= NULL and std::find(tileList.begin(), tileList.end(), tempTile) == tileList.end()) tileList.push_back(tempTile);
            }

        }while(i < tileList.size());
    }

    printf("Clicked  %d, %d ,, %d\n", t_tile->getPos().r, t_tile->getPos().c, t_tile->m_value);
}

Tile* TileGroup::findTile(int r, int c)
{
    PosRC pos;
    std::vector<GUISprite*> sprts = sprites();
    Tile* spr = NULL;
    for (unsigned int i = 0; i<sprts.size(); i++)
    {
        spr = (Tile*)sprts[i];
        pos = spr->getPos();
        if (pos.r == r and pos.c == c)
            return spr;
    }
    return NULL;
}
