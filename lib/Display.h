#pragma once
#include <iostream>
#include "Chip8.h"

using namespace std;


class Display {
private:
    int rows;
    int columns;

protected:
    Chip8 *cpu;

    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Window *window;

    int windowHeight;
    int windowWidth;
public:
    Display(Chip8* chip8) : cpu(chip8){};
    virtual void initialize() = 0;
    virtual void checkForDraw() = 0;

    void clearScreen() {
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    };

    void destroy() {
        SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
	    SDL_Quit();
    };
};