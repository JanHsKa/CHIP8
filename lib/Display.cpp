#include <iostream>
#include "Display.h"
#include "SDL2/SDL.h"
#include "Macros.h"

Display::Display() {
    width = SCALE * COLUMNS;
    height = SCALE * ROWS;
}

void Display::initialize() {

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

void Display::draw(Uint32* pixelMap) {
    cout<<"Drawing"<<endl;
    int error = 0;
    error = SDL_UpdateTexture(texture, NULL, pixelMap, COLUMNS * sizeof(Uint32));
    printf("SDL_Init failed: %s\n", SDL_GetError());
    error = SDL_RenderCopy(renderer, texture, NULL, NULL);
    cout<<"renderCopy: "<<error<<endl;
	SDL_RenderPresent(renderer);
}

void Display::clearScreen() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Display::destroy() {
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
