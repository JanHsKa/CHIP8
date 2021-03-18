#include "DebugTexture.h"


DebugTexture::DebugTexture(TTF_Font* font, SDL_Renderer* renderer, SDL_Color color,string text) :
    debugRenderer(renderer),
    debugFont(font){
    debugText = text;
    debugColor = color;
    renderText();
}

void DebugTexture::renderText() {
    cout<<"render "<<debugText.c_str()<<endl;
    SDL_Surface* newSurface = TTF_RenderText_Solid(debugFont, debugText.c_str(), debugColor);
    cout<<"render surface ende "<<endl;

    rectangle.w = newSurface->w;
    rectangle.h = newSurface->h;
    rectangle.x = 0;
    rectangle.y = 0;

    height = newSurface->h;
    width = newSurface->w;

    debugTexture = SDL_CreateTextureFromSurface(debugRenderer,
            newSurface);
    SDL_QueryTexture(debugTexture, NULL, NULL, &rectangle.w, &rectangle.h);
    SDL_FreeSurface(newSurface);
    cout<<"render ende"<<endl;

}

SDL_Texture* DebugTexture::getTexture() {
    return debugTexture;
}

void DebugTexture::setText(string text) {
    debugText = text;
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