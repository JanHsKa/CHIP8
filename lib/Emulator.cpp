#include "Emulator.h"
#include "SDL2/SDL.h"
#include "Macros.h"

using namespace std;

Emulator::Emulator(const char* file, uint8_t debug) : 
filePath(file) {
	debugType = debug;
	display = new Display();
	cpu = new Chip8();

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

bool Emulator::loadFile()
{
	return cpu->load(filePath);
}

void Emulator::initialize() {
	display->initialize();
	loadFile();
}

int Emulator::emulateProgram() {
	initialize();
	emulationCycle();

	display->destroy();

	return 0;
}

void Emulator::emulationCycle() {
	bool stop = false;
	unsigned int lastUpdate = SDL_GetTicks(); 
	int cyclecount = 0;

	while(!stop) {
		cout<<std::dec;
		cout<<"lastupdate: "<<lastUpdate<<endl;
		cout<<"lastupdate + : "<<lastUpdate + REFRESHRATE<<endl<<endl;
		cout<<"get Ticks: "<<SDL_GetTicks()<<endl;
		cout<<"difference "<<SDL_GetTicks() - lastUpdate<<endl<<endl;


		cyclecount += 1;
		cout<<"gamecycle round  "<<cyclecount<<endl;
		SDL_Event e;

		while(SDL_PollEvent(&e) != 0)
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
		cpu->processCommand();

		if (lastUpdate + REFRESHRATE < SDL_GetTicks()) {
			cout<<"drawcycle round"<<endl;

			Uint32 pixelMap[ROWS * COLUMNS];
			cpu->copyGraphicBuffer(pixelMap);
			cpu->updateTimers();

			if (cpu->getDrawFlag()) {
				cpu->setDrawFlag(false);
				display->draw(pixelMap);			
			}

			lastUpdate = SDL_GetTicks();
			cyclecount = 0;
		}
	SDL_Delay(1);
	}

}


void Emulator::changePressedKey(SDL_Event event, int value) {
	if (keymap.find(event.key.keysym.sym) != keymap.end()) {
		cpu->setKeyPadAt(keymap[event.key.keysym.sym], value);
	}
}

int Emulator::emulateDebug() {
	cout << "Starting Debug Mode" <<endl;
	cout << "F6 : Step through program" <<endl;
	cout << "F7 : Print out current memory" <<endl;
	cout << "F8 : Run program normal" <<endl;
	

	display->initialize();

	loadFile();

	bool stop = false; 

	while(!stop) {

		SDL_Event e;

		while(SDL_PollEvent(&e) != 0) {
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
		cpu->processCommand();

		Uint32 pixelMap[ROWS * COLUMNS];
		cpu->copyGraphicBuffer(pixelMap);

		if (cpu->getDrawFlag()) {
			cpu->setDrawFlag(false);
			display->draw(pixelMap);			
		}

		SDL_Delay(10);
		}

	display->destroy();
	return 0;
	return 0;
}
