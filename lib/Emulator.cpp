#include "Emulator.h"
#include "Macros.h"

using namespace std;

Emulator::Emulator(const char* file, uint8_t debug) : 
filePath(file) {
	debugType = debug;
	display = new Display();
	keyboard = new Keypad();
	cpu = new Chip8(keyboard);
	soundController = new Soundcontroller();

	cpu->copyGraphicBuffer(pixelMap);

	lastUpdate = 0;
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
			stop = keyboard->getQuit();
		}

		cpu->processCommand();
		checkForRefresh();	
		SDL_Delay(1);
	}
}

void Emulator::checkForRefresh() {
	if (lastUpdate + REFRESHRATE < SDL_GetTicks()) {
		if(cpu->updateTimers()) {
			//soundController->playSound();
		}
		checkForDraw();
		lastUpdate = SDL_GetTicks();
	}
}

void Emulator::checkForDraw() {
	if (cpu->getDrawFlag()) {
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
			stop = keyboard->getQuit();
		}

		cpu->processCommand();
		checkForRefresh();
		SDL_Delay(3);
		}

	display->destroy();
	return 0;
}
