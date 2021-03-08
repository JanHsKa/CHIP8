#include "Emulator.h"
#include "SDL2/SDL.h"
#include "Macros.h"

using namespace std;

Emulator::Emulator(const char* file, uint8_t debug) : 
filePath(file) {
	debugType = debug;
	display = new Display();
	cpu = new Chip8();
	keyboard = new Keyboard();
	soundController = new Soundcontroller();

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
	lastUpdate = SDL_GetTicks(); 

	while(!stop) {
		if (keyboard->checkInput()) {
			cpu->updateKeyPad(keyboard->getKeypad());
			stop = keyboard->getQuit();
		}

		cpu->processCommand();
		checkForRefresh();	
		SDL_Delay(3);
	}
}

void Emulator::checkForRefresh() {
	if (lastUpdate + REFRESHRATE < SDL_GetTicks()) {
		if(cpu->updateTimers()) {
			soundController->playSound();
		}
		checkForDraw();
		lastUpdate = SDL_GetTicks();
	}
}

void Emulator::checkForDraw() {
	if (cpu->getDrawFlag()) {
		Uint32 pixelMap[ROWS * COLUMNS];
		cpu->copyGraphicBuffer(pixelMap);
		display->draw(pixelMap);			
		cpu->setDrawFlag(false);
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
	lastUpdate = SDL_GetTicks(); 

	while(!stop) {

		if (keyboard->checkInput()) {
			cpu->updateKeyPad(keyboard->getKeypad());
			stop = keyboard->getQuit();
		}

		cpu->processCommand();
		checkForRefresh();
		SDL_Delay(3);
		}

	display->destroy();
	return 0;
}
