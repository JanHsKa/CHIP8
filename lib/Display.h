#pragma once
#include <iostream>
#include "CPU.h"

using namespace std;


class Display {
private:
    int rows;
    int columns;

protected:
    CPU *cpu;

    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Window *window;

    int windowHeight;
    int windowWidth;
public:
    Display(CPU* chip8) : cpu(chip8){};
    virtual void initialize() = 0;
    virtual void checkForDraw() = 0;
    virtual void setWindowShown(bool show) {
        if (show) {
            SDL_ShowWindow(window);
        } else {
            SDL_HideWindow(window);
    }
    };
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