#pragma once
#include <iostream>
#include "Chip8.h"
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
    GameDisplay(Chip8 *chip8);
    void initialize();
    void checkForDraw();
};