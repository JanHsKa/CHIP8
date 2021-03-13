#include <iostream>
#include "Display.h"
#include "Macros.h"
#include "SDL2/SDL_ttf.h"


Display::Display(): 
    debugColor({0,0,0,0}) {
    width = SCALE * COLUMNS;
    height = SCALE * ROWS;
    debugHeight = 480;
    debugWidth = 640;
}

void Display::initialize() {

    SDL_Init(true);
	window = SDL_CreateWindow("CHIP 8",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height,
                                          SDL_WINDOW_SHOWN);

    if(!window)
    {
        std::cout << "Failed to create window\n";
    }


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	 
	texture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            COLUMNS, ROWS); 
}

void Display::initDebugWindow() {
    if (TTF_Init() < 0) {
        cout<<"error: "<<TTF_GetError()<<endl;
    }
    
    debugWindow = SDL_CreateWindow("Debug",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          debugWidth, debugHeight,
                                          SDL_WINDOW_SHOWN);

    if(!debugWindow)
    {
        std::cout << "Failed to create window\n";
    }

    debugFont = TTF_OpenFont("Font/arial.ttf", 30);
	debugRenderer = SDL_CreateRenderer(debugWindow, -1, SDL_RENDERER_ACCELERATED);

	if (debugRenderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}
}

void Display::draw(Uint32* pixelMap) {
    cout<<"Drawing"<<endl;
    int error = 0;
    error = SDL_UpdateTexture(texture, NULL, pixelMap, COLUMNS * sizeof(Uint32));
    if (error > 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }
    error = SDL_RenderCopy(renderer, texture, NULL, NULL);
    cout<<"renderCopy: "<<error<<endl;
	SDL_RenderPresent(renderer);
}

void Display::drawDebug() {
    int success = 0;

    debugSurface = TTF_RenderText_Solid(debugFont, "das ist ein test text", debugColor);
    SDL_Rect rect;
     rect.x = 0;
     rect.y = 0;
     rect.w = debugSurface->w;
     rect.h = debugSurface->h;

    SDL_Rect startPos;
    startPos.x = 0;
    startPos.y = 0;
    startPos.h = debugSurface->h;
    startPos.w = debugSurface->w;


	debugTexture = SDL_CreateTextureFromSurface(debugRenderer,
            debugSurface); 
    SDL_SetRenderDrawColor(debugRenderer, 200, 200, 200, 200);
    success = SDL_QueryTexture(debugTexture, NULL, NULL, &rect.x, &rect.y);

    cout<<"query success: "<<success<<endl;

    SDL_RenderClear(debugRenderer);
    success = SDL_RenderCopy(debugRenderer, debugTexture, NULL, &startPos);
    cout<<"render success: "<<success<<endl;
    SDL_RenderPresent(debugRenderer);
    SDL_FreeSurface(debugSurface);
}


void Display::clearScreen() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Display::destroy() {
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_DestroyTexture(debugTexture);
	SDL_Quit();
}
