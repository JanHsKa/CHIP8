#include <iostream>
#include "Display.h"
#include "Macros.h"
#include "SDL2/SDL_ttf.h"
#include <sstream>
#include <iterator>


Display::Display(Chip8 *chip8):
    cpu(chip8) {
    windowWidth = SCALE * COLUMNS;
    windowHeight = SCALE * ROWS;

	cpu->copyGraphicBuffer(pixelMap);
}

void Display::initialize() {

    SDL_Init(true);
	window = SDL_CreateWindow("CHIP 8",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          windowWidth, windowHeight,
                                          SDL_WINDOW_SHOWN);

    if(!window)
    {
        cout << "Failed to create window\n";
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

void Display::checkForDraw() {
	if (cpu->getDrawFlag()) {
		cpu->copyGraphicBuffer(pixelMap);
		draw();			
		cpu->setDrawFlag(false);
	}
}
 

void Display::draw() {
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

void Display::clearScreen() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Display::destroy() {
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
