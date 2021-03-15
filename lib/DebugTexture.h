#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

using namespace std;

class DebugTexture {
private:
    int height;
    int width;
    string debugText;

    SDL_Rect rectangle;
    SDL_Texture *debugTexture;

public:
    DebugTexture(TTF_Font* font, SDL_Renderer* renderer, SDL_Color color,string text);
    SDL_Texture* getTexture();
    string getText();
    int getHeight();
    int getWidth();
};

