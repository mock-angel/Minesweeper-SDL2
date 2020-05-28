#include <iostream>
#include <thread>         // std::thread
#include<SDL2/SDL.h>
//#include <SDL/SDL_opengl.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <gtk/gtk.h>
//`pkg-config --cflags --libs gtk+-3.0`
using namespace std;
#include "engine/Engine.h"
#include "GUI.h"
#include "Game/Mine.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
/*void openGtkWindow(){
    GtkWidget *aboutWindow = gtk_about_dialog_new();
    //Write things in the About window
    g_signal_connect(G_OBJECT(aboutWindow),"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    gtk_widget_show(aboutWindow);
    gtk_main();
}*/
//SDL_PIXELFORMAT_RGBA8888
int main()
{
    cout << "Hello world!" <<SDL_INIT_VIDEO<< endl;
    /*SDL_WindowFlags-SDL_WINDOW_FULLSCREEN_DESKTOP
    SDL_WINDOW_OPENGL
    SDL_WINDOW_BORDERLESS
    SDL_WINDOW_RESIZABLE
    SDL_WINDOW_ALWAYS_ON_TOP
    SDL_SetWindowInputFocus()
    */
    //Uint32 flag = SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP;

    GUIWindowProgram* g = new GUIWindowProgram();
    //g->setFlags(flag);
    GUIWindowProgram* h = new GUIWindowProgram();
    Engine* engine = new Engine() ;
    //engine->addProgram(g);
    //engine->addProgram(new GUIWindowProgram());
    engine->addProgram(h);//openGtkWindow();
    printf("Starting destructor\n");
    engine->startEventHandler();
    //engine->waitTillClosed();
    //engine->waitTillClosed();

    //SDL_Delay(1000);
    delete engine;
}
