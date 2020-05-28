#include "Mine.h"
//m_programsWindowObject::
#include <iostream>
#include <fstream>
//#include <jsoncpp/json/json.h>
#include "precompiled.h"
#include "Button.h"

#include "Tile.h"

GUIWindowProgram::GUIWindowProgram(){
    m_tileGroup = new TileGroup(this);
}
GUIWindowProgram::~GUIWindowProgram(){
}

//

void GUIWindowProgram::init_sprites(){
    /* Init all sprites here. */
    setBackgroundColor({206, 206, 206, 0xFF});

    Tile::offset_xy.x = 20;
    Tile::offset_xy.y = 130;

    Tile::defaultSurface = loadSurface("resources/data/tile/default.png");
    Tile::defaultOverSurface = loadSurface("resources/data/tile/default_hover.png");
    Tile::defaultpressedSurface = loadSurface("resources/data/tile/default_hover.png");

    SDL_Surface * alphaSurf = loadSurface("resources/data/tile/held_alpha.png");
    SDL_BlitScaled(alphaSurf, NULL, Tile::defaultpressedSurface, NULL);

    Tile::surfaceMap[0]["sprite"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    Tile::surfaceMap[0]["sprite_over"] = Tile::surfaceMap[0]["sprite"];
    Tile::surfaceMap[0]["sprite_pressed"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    SDL_BlitScaled(alphaSurf, NULL, Tile::surfaceMap[0]["sprite_pressed"], NULL);

    ///Rect rect = {0, 0, 32, 32};
    SDL_Surface* numSurf = NULL;
    for (int i = 1; i<=8; i++)
    {
        Tile::surfaceMap[i]["sprite"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
        Tile::surfaceMap[i]["sprite_over"] = Tile::surfaceMap[i]["sprite"];
        Tile::surfaceMap[i]["sprite_pressed"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
        numSurf = loadSurface("resources/data/themes/bgcolors/Tile/"+std::to_string(i)+"mines.png");
        SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[i]["sprite"], NULL);
        ///SDL_BlitSurface(numSurf, NULL, Tile::surfaceMap[i]["sprite_over"], NULL);
        SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[i]["sprite_pressed"], NULL);
        SDL_BlitScaled(alphaSurf, NULL, Tile::surfaceMap[i]["sprite_pressed"], NULL);
    }
    //Blast
    Tile::surfaceMap[13]["sprite"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    Tile::surfaceMap[13]["sprite_over"] = Tile::surfaceMap[13]["sprite"];
    Tile::surfaceMap[13]["sprite_pressed"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    numSurf = loadSurface("resources/data/themes/bgcolors/Tile/exploded.png");
    SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[13]["sprite"], NULL);
    ///SDL_BlitSurface(numSurf, NULL, Tile::surfaceMap[i]["sprite_over"], NULL);
    SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[13]["sprite_pressed"], NULL);
    SDL_BlitScaled(alphaSurf, NULL, Tile::surfaceMap[13]["sprite_pressed"], NULL);

    Tile::surfaceMap[14]["sprite"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    Tile::surfaceMap[14]["sprite_over"] = Tile::surfaceMap[14]["sprite"];
    Tile::surfaceMap[14]["sprite_pressed"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    numSurf = loadSurface("resources/data/themes/bgcolors/Tile/mine.png");
    SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[14]["sprite"], NULL);
    ///SDL_BlitSurface(numSurf, NULL, Tile::surfaceMap[i]["sprite_over"], NULL);
    SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[14]["sprite_pressed"], NULL);
    SDL_BlitScaled(alphaSurf, NULL, Tile::surfaceMap[14]["sprite_pressed"], NULL);

    ///Flag
    Tile::surfaceMap[10]["sprite"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    Tile::surfaceMap[10]["sprite_over"] = Tile::surfaceMap[10]["sprite"];
    Tile::surfaceMap[10]["sprite_pressed"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    numSurf = loadSurface("resources/data/themes/bgcolors/Tile/flag.png");
    SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[10]["sprite"], NULL);
    ///SDL_BlitSurface(numSurf, NULL, Tile::surfaceMap[i]["sprite_over"], NULL);
    SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[10]["sprite_pressed"], NULL);
    SDL_BlitScaled(alphaSurf, NULL, Tile::surfaceMap[10]["sprite_pressed"], NULL);

    //Maybe Flag
    Tile::surfaceMap[11]["sprite"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    Tile::surfaceMap[11]["sprite_over"] = Tile::surfaceMap[11]["sprite"];
    Tile::surfaceMap[11]["sprite_pressed"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    numSurf = loadSurface("resources/data/themes/bgcolors/Tile/maybe.png");
    SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[11]["sprite"], NULL);
    ///SDL_BlitSurface(numSurf, NULL, Tile::surfaceMap[i]["sprite_over"], NULL);
    SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[11]["sprite_pressed"], NULL);
    SDL_BlitScaled(alphaSurf, NULL, Tile::surfaceMap[11]["sprite_pressed"], NULL);

    //incorrect flag.
    Tile::surfaceMap[12]["sprite"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    Tile::surfaceMap[12]["sprite_over"] = Tile::surfaceMap[12]["sprite"];
    Tile::surfaceMap[12]["sprite_pressed"] = loadSurface("resources/data/themes/bgcolors/Tile/uncovered.png");
    numSurf = loadSurface("resources/data/themes/bgcolors/Tile/incorrect.png");
    SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[12]["sprite"], NULL);
    ///SDL_BlitSurface(numSurf, NULL, Tile::surfaceMap[i]["sprite_over"], NULL);
    SDL_BlitScaled(numSurf, NULL, Tile::surfaceMap[12]["sprite_pressed"], NULL);
    SDL_BlitScaled(alphaSurf, NULL, Tile::surfaceMap[12]["sprite_pressed"], NULL);

    std::pair<int, int> sizeRC;
    sizeRC.first = sizeRC.second = 8;
    m_tileGroup->generateTiles(10, sizeRC);
    sprites->add(m_tileGroup);
    ///sprites->add(new Tile(this));
}

void GUIWindowProgram::update(){//locks updateLock
    /* Do game updates here. */
}
void GUIWindowProgram::draw(){
    /* Do Surface drawing to surface here. */
}

void GUIWindowProgram::render(){//locks renderLock
    /* Perform all rendering activities here. */
    if( !isMinimized())
    {
//        Clear screen
        //clearRenderer();
        clearRenderer();

        sprites->render();

        //render();//TODO. check this.

        //Update screen
        SDL_RenderPresent( m_renderer);
    }
    ///printf("rendering thread \n");
}


