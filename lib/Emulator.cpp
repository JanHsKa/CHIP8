#include "Emulator.h"
#include "Macros.h"

using namespace std;

Emulator::Emulator(const char* file, const char* debugInput) : 
	filePath(file),
	debugParam(debugInput) {
	//debugType = debug;
	keyboard = new Keypad();
	cpu = new Chip8(keyboard);
	gameDisplay = new GameDisplay(cpu);
	//soundController = new Soundcontroller();
	debugDisplay = new DebugDisplay(cpu);
	debugManager = new DebugManager(debugDisplay, cpu);
	inputChecker = new InputChecker(debugManager, keyboard);
	lastUpdate = 0;
	loadedFile = false;
	debugMode = false;
	initialize();
}

void Emulator::checkIfDebug() {
	if (debugParam != NULL) {
		string convert = debugParam;
		if (convert == "debug") {
			debugMode = true;
		}
	}
}

bool Emulator::loadFile()
{
	return cpu->load(filePath);
}

void Emulator::initialize() {
	checkIfDebug();
	cout<<"debugchecked   "<<debugMode<<endl;
	loadedFile = loadFile();
	cout << "start init" <<endl;
	
		gameDisplay->initialize(); 
	cout << "start init" <<endl;

	debugManager->initialize();
	cout << "start init" <<endl;

	debugDisplay->initialize();
	cout << "finished init" <<endl;

	if (debugMode) {
    	debugDisplay->setWindowShown(true);
	}
	//debugDisplay->checkForDraw();
}

int Emulator::emulateProgram() {
	if (loadedFile) {
		emulationCycle();

	} else {
		cerr<<"Failed to load program file"<<endl;
	}

	gameDisplay->destroy();

	return 0;
}

void Emulator::emulationCycle() {
	cout << "start programm" <<endl;

	bool stop = false;
	lastUpdate = SDL_GetTicks(); 

	while(!stop) {
		inputChecker->checkInput();
		stop = inputChecker->getQuit();
		if (!debugMode || debugManager->continueProgram()) {
			cpu->processCommand();
			updateTimer();
		}

		// cpu->processCommand();
		// updateTimer();
		refreshDisplay();	
		SDL_Delay(1);
	}

	close();
}

void Emulator::refreshDisplay() {
	if (timeToUpdate()) {
		gameDisplay->checkForDraw();
		if (debugMode) {
			debugDisplay->checkForDraw();
		}
		lastUpdate = SDL_GetTicks();
	}
}

void Emulator::updateTimer() {
	if (timeToUpdate()) {
		cpu->updateTimers();
	}
}

bool Emulator::timeToUpdate() {
	return lastUpdate + REFRESHRATE < SDL_GetTicks();
}

int Emulator::emulateDebug() {
	cout << "Starting Debug Mode" <<endl;
	cout << "F6 : Step through program" <<endl;
	cout << "F7 : Print out current memory" <<endl;
	cout << "F8 : Run program normal" <<endl;

	return 0;
}

void Emulator::close() {
	debugDisplay->destroy();
	gameDisplay->destroy();
}