#include <iostream>
#include "Display.h"
#include "SDL2/SDL.h"
#include "Macros.h"

Display::Display() {
    width = SCALE * COLUMNS;
    height = SCALE * ROWS;
    //initialize();
}

void Display::initialize() {
	SDL_Window *window = SDL_CreateWindow("CHIP 8",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height,
                                          SDL_WINDOW_SHOWN);

    if(!window)
    {
        std::cout << "Failed to create window\n";
    }


	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	 
	SDL_Texture* texture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            COLUMNS, ROWS); 
}

void Display::draw(uint32_t* pixelMap) {
    cout<<"Drawing"<<endl;
    SDL_UpdateTexture(texture, NULL, pixelMap, COLUMNS * sizeof(Uint32));
	SDL_RenderCopy(renderer, texture, NULL, NULL);
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
