#include "Emulator.h"
#include "Macros.h"

using namespace std;

Emulator::Emulator(const char* file, uint8_t debug) : 
filePath(file) {
	debugType = debug;
	keyboard = new Keypad();
	cpu = new Chip8(keyboard);
	display = new Display(cpu);
	soundController = new Soundcontroller();


	initialize();
}

bool Emulator::loadFile()
{
	return cpu->load(filePath);
}

void Emulator::initialize() {
	lastUpdate = 0;
	loadedFile = false;
	display->initialize(); 
	//display->initDebugWindow();
	//display->drawDebug();
	loadedFile = loadFile();
}

int Emulator::emulateProgram() {
	if (loadedFile) {
		emulationCycle();

	} else {
		cerr<<"Failed to load program file";
	}

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
		display->checkForDraw();
		lastUpdate = SDL_GetTicks();
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
