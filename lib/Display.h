#include <iostream>
#include "Chip8.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

using namespace std;

class Display {
private:
    int height;
    int width;
    int rows;
    int columns;
    int debugHeight;
    int debugWidth;

    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Window *debugWindow;
    SDL_Renderer *debugRenderer;
    SDL_Texture *debugTexture;

    TTF_Font * debugFont;
    SDL_Surface *debugSurface;
    SDL_Color debugColor;

public:
    Display();
    void initialize();
    void initDebugWindow();
    void clearScreen();
    void draw(Uint32* pixelMap);
    void drawDebug();
    void destroy();
};