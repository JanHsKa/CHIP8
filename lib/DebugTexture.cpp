#include "DebugTexture.h"


DebugTexture::DebugTexture(TTF_Font* font, SDL_Renderer* renderer, SDL_Color color,string text) {
    debugText = text;
    SDL_Surface* newSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    rectangle.w = newSurface->w;
    rectangle.h = newSurface->h;
    rectangle.x = 0;
    rectangle.y = 0;

    height = newSurface->h;
    width = newSurface->w;

    debugTexture = SDL_CreateTextureFromSurface(renderer,
            newSurface);
    SDL_QueryTexture(debugTexture, NULL, NULL, &rectangle.w, &rectangle.h);
    SDL_FreeSurface(newSurface);
}

SDL_Texture* DebugTexture::getTexture() {
    return debugTexture;
}

string DebugTexture::getText() {
    return debugText;
}

int DebugTexture::getHeight() {
    return rectangle.h;
}

int DebugTexture::getWidth() {
    return rectangle.w;
}