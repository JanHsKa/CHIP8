#include <iostream>
#include "Chip8.h"
#include "SDL2/SDL.h"

using namespace std;

class Display {
private:
    int height;
    int width;
    int rows;
    int columns;

    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Window *window;

public:
    Display();
    void initialize();
    void clearScreen();
    void draw(Uint32* pixelMap);
    void destroy();
    void checkKeyboardInput();
};