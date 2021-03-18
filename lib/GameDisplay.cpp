#include <iostream>
#include "GameDisplay.h"
#include "Macros.h"
#include "SDL2/SDL_ttf.h"
#include <sstream>
#include <iterator>


GameDisplay::GameDisplay(CPU *chip8): Display(chip8) {
    windowWidth = SCALE * COLUMNS;
    windowHeight = SCALE * ROWS;

	for (int i = 0; i < COLUMNS * ROWS; i++) {
        pixelMap[i] = 0;
    }
}

void GameDisplay::initialize() {
    SDL_Init(true);
	window = SDL_CreateWindow("CHIP 8",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        SDL_WINDOW_SHOWN);

    if(!window)
    {
        cerr<<"Failed to create window"<<SDL_GetError()<<endl;
    }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
        cerr<<"Could not create a renderer:"<<SDL_GetError()<<endl;
	}

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	 
	texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        COLUMNS, ROWS); 
}

void GameDisplay::checkForDraw() {
	if (cpu->getDrawFlag()) {
		cpu->copyGraphicBuffer(pixelMap);
		draw();			
		cpu->setDrawFlag(false);
	}
}

void GameDisplay::draw() {
    SDL_UpdateTexture(texture, NULL, pixelMap, COLUMNS * sizeof(Uint32));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}



