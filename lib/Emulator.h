#pragma once
#include <iostream>
#include "Chip8.h"
#include "SDL2/SDL.h"
#include "Display.h"
#include "DebugDisplay.h"
#include <map>
#include "Soundcontroller.h"

using namespace std;


class Emulator {
private:
	Chip8* cpu;
	Display* display; 
	Keypad* keyboard;
	Soundcontroller* soundController;
	DebugDisplay* debugDisplay;

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