#pragma once
#include <iostream>
#include "CPU.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "DebugTexture.h"
#include "Display.h"
#include <vector>

using namespace std;

class GameDisplay : public Display {
private:

	Uint32 pixelMap[ROWS * COLUMNS];

    void draw();
public:
    GameDisplay(CPU *chip8);
    void initialize();
    void checkForDraw();
};