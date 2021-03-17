#include "Emulator.h"
#include "Macros.h"

using namespace std;

Emulator::Emulator(const char* file, uint8_t debug) : 
filePath(file) {
	debugType = debug;
	keyboard = new Keypad();
	cpu = new Chip8(keyboard);
	display = new GameDisplay(cpu);
	soundController = new Soundcontroller();
	debugDisplay = new DebugDisplay(cpu);
	debugManager = new DebugManager(debugDisplay, cpu);
	inputChecker = new InputChecker(debugManager, keyboard);

	initialize();
}

bool Emulator::loadFile()
{
	return cpu->load(filePath);
}

void Emulator::initialize() {
	lastUpdate = 0;
	loadedFile = false;
	loadedFile = loadFile();
	display->initialize(); 
	debugManager->initialize();
	debugDisplay->initialize();
	debugDisplay->checkForDraw();
}

int Emulator::emulateProgram() {
	if (loadedFile) {
		emulationCycle();

	} else {
		cerr<<"Failed to load program file"<<endl;
	}

	display->destroy();

	return 0;
}

void Emulator::emulationCycle() {
	bool stop = false;
	lastUpdate = SDL_GetTicks(); 

	while(!stop) {
		inputChecker->checkInput();
		stop = inputChecker->getQuit();
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
		debugDisplay->checkForDraw();
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
		inputChecker->checkInput();
		stop = inputChecker->getQuit();

		cpu->processCommand();
		checkForRefresh();
		SDL_Delay(3);
		}

	display->destroy();
	debugDisplay->destroy();
	return 0;
}
