#pragma once
#include <iostream>
#include "SDL2/SDL.h"
#include "DebugManager.h"
#include "Keypad.h"
#include "Macros.h"


using namespace std;

class InputChecker {
private:
    Keypad* gameKeypad;
    DebugManager* debugManager;
    bool quit;

public:
    InputChecker(DebugManager* debug, Keypad* keypad);
    void checkInput();
    bool getQuit();
};