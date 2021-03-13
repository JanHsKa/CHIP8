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

    Chip8 *cpu;
	Uint32 pixelMap[ROWS * COLUMNS];

    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Window *debugWindow;
    SDL_Renderer *debugRenderer;
    SDL_Texture *debugTexture;

    TTF_Font * debugFont;
    SDL_Surface *debugSurface;
    SDL_Color debugColor;

    void draw();
public:
    Display(Chip8 *chip8);
    void initialize();
    void initDebugWindow();
    void checkForDraw();
    void clearScreen();
    void drawDebug();
    void destroy();
};