#ifndef INCLUDED_GUIEVENT
#define INCLUDED_GUIEVENT

#include "Mouse.h"

enum GUIEventsEnum{
    ENTER,
    LEAVE,
    //CLICKED,
    PRESSED,
    RELEASED,
};
class GUIEvent{
    Mouse mouse;

};

class GUIEventObject{ //Must be in the object that wants to convert to GUI Event?
    //void handleEvent(){}
public:
    bool m_mouseOver = false;
    bool m_pressed = false;
    virtual void onClicked(){printf("left Clicked Sprite\n");};
    virtual void onReleased(){printf("Released Sprite\n");};
    virtual void onPressed(){printf("onPressed Sprite\n");};
    //virtual void onDblClicked(){printf("left onDblClicked Sprite\n");}; // Not implemented;
    virtual void onRightClicked(){printf("Right clicked Sprite\n");};
    virtual void onHover(){printf("Hover Sprite\n");};
    virtual void onEnter(){printf("Entered Sprite\n");};
    virtual void onLeave(){printf("Left Sprite\n");};


};
#endif // INCLUDED_GUIEVENT
