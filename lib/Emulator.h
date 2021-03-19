#pragma once
#include <iostream>
#include "CPU.h"
#include "SDL2/SDL.h"
#include "GameDisplay.h"
#include "DebugDisplay.h"
#include "Soundcontroller.h"
#include "InputChecker.h"
#include <map>

using namespace std;


class Emulator {
private:
	CPU* cpu;
	GameDisplay* gameDisplay; 
	DebugDisplay* debugDisplay;
	Keypad* keyboard;
	InputChecker* inputChecker;
	//Soundcontroller* soundController;
	DebugManager* debugManager;

	const char* filePath;
	const char* debugParam;

	bool debugMode;

	unsigned int lastUpdate;
	bool loadedFile;

	bool loadFile();
	void initialize();
	void initDebug();
	void checkIfDebug();

	void checkForDraw();
	void checkForRefresh();
	void refreshDisplay();
	void updateTimer();
	bool timeToUpdate();

	void close();

public:
	Emulator(const char* , const char*);
	int emulateProgram();
	int emulateDebug();
	void emulationCycle();
};