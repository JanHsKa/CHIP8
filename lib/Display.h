#pragma once
#include <iostream>
#include "Chip8.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "DebugTexture.h"
#include <vector>

using namespace std;

class Display {
private:
    int rows;
    int columns;

	Uint32 pixelMap[ROWS * COLUMNS];

protected:
    int windowHeight;
    int windowWidth;
    Chip8 *cpu;

    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Window *window;

    void virtual draw();

public:
    Display(Chip8 *chip8);
    void virtual initialize();
    void virtual checkForDraw();
    void clearScreen();
    void destroy();
};