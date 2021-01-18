#include "Controller.h"
#include "SDL2/SDL.h"

Controller::Controller(const char* file, uint8_t debug) : filePath(file), 
	keymap{SDLK_1, SDLK_2, SDLK_3, SDLK_4, 
		SDLK_q, SDLK_w, SDLK_e, SDLK_r, 
		SDLK_a, SDLK_s, SDLK_d, SDLK_f, 
		SDLK_y, SDLK_x, SDLK_c, SDLK_v}  {
	debugType = debug;
	emulator = new chip8();
}

bool Controller::loadFile()
{
	return emulator->load(filePath);
}

int Controller::emulateCycle()
{
	cout<<"starting emulate"<<endl;

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

	SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          64 * 4, 32 * 6,
                                          0);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }


	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
		return -1;
	}

	 
	SDL_Texture* sdlTexture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            64, 32); 

	loadFile();

	cout << "finished loading" <<endl;
	
	bool keep_window_open = true;
	while(keep_window_open)
	{
		emulator->processCommand();
		SDL_Event e;
		while(SDL_PollEvent(&e) > 0)
		{
			switch(e.type)
			{
				case SDL_QUIT:
					keep_window_open = false;
					break;

				case SDL_KEYDOWN:
					addPressedKey(e, 1);
					break;

				case SDL_KEYUP:
					addPressedKey(e, 0);
					break;
			}

		}

		uint32_t pixelMap[32 * 64];
		emulator->copyGraphicBuffer(pixelMap);

		if (emulator->getDrawFlag()) {
			emulator->setDrawFlag(false);

			SDL_UpdateTexture(sdlTexture, NULL, pixelMap, 64 * sizeof(Uint32));
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
				SDL_RenderPresent(renderer);
		}

		SDL_Delay(1000/60);
	}


	

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}


void Controller::addPressedKey(SDL_Event event, int value) {
	for (int i = 0; i < 16; i++) {
		if (event.key.keysym.sym == keymap[i]) {
			emulator->setKeyPad(i, value);
		}
	}
}

