#pragma once

#include <iostream>
#include <map>
#include "DebugDisplay.h"

using namespace std;

enum DebugKey {
    Step_over,
    Continue,
    Debug_Output
};  

class DebugManager {
private:
    DebugDisplay* debugDisplay;
    map<SDL_Keycode, int> keymap; 
    bool debugKeys[DEBUG_KEY_COUNT];

public:
    DebugManager(DebugDisplay* display);
    void setPressedDebugKey(SDL_Event event, int value);
    void scrollText(SDL_MouseWheelEvent wheel);
    void doubleClick(SDL_MouseButtonEvent click);

    bool isDebugKeyPressed(DebugKey key);

};