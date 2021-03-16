#pragma once
#include <iostream>
#include "Chip8.h"
#include "SDL2/SDL.h"
#include "GameDisplay.h"
#include "DebugDisplay.h"
#include "Soundcontroller.h"
#include "InputChecker.h"
#include <map>

using namespace std;


class Emulator {
private:
	Chip8* cpu;
	GameDisplay* display; 
	DebugDisplay* debugDisplay;
	Keypad* keyboard;
	InputChecker* inputChecker;
	Soundcontroller* soundController;
	DebugManager* debugManager;

	const char* filePath;
	uint8_t debugType;

	unsigned int lastUpdate;
	bool loadedFile;

	bool loadFile();
	void initialize();
	void checkForDraw();
	void checkForRefresh();

public:
	Emulator(const char* , uint8_t);
	int emulateProgram();
	int emulateDebug();
	void emulationCycle();
};