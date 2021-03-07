#include <iostream>
#include "Chip8.h"
#include "SDL2/SDL.h"
#include "Display.h"
#include <map>

using namespace std;


class Emulator {
private:
	Chip8* emulator;
	Display *display; 
	map<SDL_Keycode, uint8_t> keymap;
	const char* filePath;
	uint8_t debugType;

	void changePressedKey(SDL_Event, int);



public:
	Emulator(const char* , uint8_t);
	bool loadFile();
	void initialize();
	int emulateProgram();
	int emulateDebug();
	void emulationCycle();
};