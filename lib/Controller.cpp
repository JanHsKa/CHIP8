#include "Controller.h"
#include "SDL2/SDL.h"
#include "Macros.h"

using namespace std;

Controller::Controller(const char* file, uint8_t debug) : 
filePath(file) {
	debugType = debug;
	emulator = new Chip8();
	display = new Display();

	keymap.insert({SDLK_1, 0x1});
	keymap.insert({SDLK_2, 0x2});
	keymap.insert({SDLK_3, 0x3});
	keymap.insert({SDLK_4, 0xC});
	keymap.insert({SDLK_q, 0x4});
	keymap.insert({SDLK_w, 0x5});
	keymap.insert({SDLK_e, 0x6});
	keymap.insert({SDLK_r, 0xD});
	keymap.insert({SDLK_a, 0x7});
	keymap.insert({SDLK_s, 0x8});
	keymap.insert({SDLK_d, 0x9});
	keymap.insert({SDLK_f, 0xE});
	keymap.insert({SDLK_y, 0xA});
	keymap.insert({SDLK_x, 0x0});
	keymap.insert({SDLK_c, 0xB});
	keymap.insert({SDLK_v, 0xF});

}

bool Controller::loadFile()
{
	return emulator->load(filePath);
}

int Controller::emulateProgram()
{
	cout<<"starting emulate"<<endl;

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

	SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1024, 512,
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

	cout << "Loading file" <<endl;

	loadFile();

	cout << "Finished loading" <<endl;

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
					changePressedKey(e, 1);
					break;

				case SDL_KEYUP:
					changePressedKey(e, 0);
					break;
			}

		}

		uint32_t pixelMap[32 * 64];
		emulator->copyGraphicBuffer(pixelMap);

		if (emulator->getDrawFlag()) {
			emulator->setDrawFlag(false);
			//SDL_RenderClear(renderer);
			SDL_UpdateTexture(sdlTexture, NULL, pixelMap, 64 * sizeof(Uint32));
			SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
			SDL_RenderPresent(renderer);
		}

		SDL_Delay(5);
	}


	

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
	
}

int Controller::emulateProgramDisplay() {
cout << "Init Display" <<endl;

	display->initialize();
	display->clearScreen();

	cout << "Loading file" <<endl;

	loadFile();

	cout << "Finished loading" <<endl;

	bool stop = false;

	cout << "Starting loop" <<endl;

	while(!stop) {

		emulator->processCommand();
		SDL_Event e;

		while(SDL_PollEvent(&e) > 0)
			{
				switch(e.type)
				{
					case SDL_QUIT:
						stop = true;
						break;

					case SDL_KEYDOWN:
						changePressedKey(e, 1);
						break;

					case SDL_KEYUP:
						changePressedKey(e, 0);
						break;
				}

			}

			uint32_t pixelMap[ROWS * COLUMNS];
			emulator->copyGraphicBuffer(pixelMap);

			if (emulator->getDrawFlag()) {
				emulator->setDrawFlag(false);

				display->draw(pixelMap);
			}

			SDL_Delay(5);
		}

	display->destroy();
	return 0;
}


void Controller::changePressedKey(SDL_Event event, int value) {
	if (keymap.find(event.key.keysym.sym) != keymap.end()) {
		emulator->setKeyPadAt(keymap[event.key.keysym.sym], value);
	}
}

int Controller::emulateDebug() {
	cout << "Starting Debug Mode" <<endl;
	cout << "F6 : Step through program" <<endl;
	cout << "F7 : Print out current memory" <<endl;
	cout << "F8 : Run program normal" <<endl;
	
	return 0;
}
