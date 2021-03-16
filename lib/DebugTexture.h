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
    TTF_Font* debugFont;
    SDL_Color debugColor;
    SDL_Renderer* debugRenderer;

public:
    DebugTexture(TTF_Font* font, SDL_Renderer* renderer, SDL_Color color,string text);
    void renderText();
    SDL_Texture* getTexture();
    string getText();
    void setText(string text);
    int getHeight();
    int getWidth();
};

