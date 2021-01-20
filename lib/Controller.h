#include <iostream>
#include "Chip8.h"
#include "SDL2/SDL.h"
#include <map>

using namespace std;


class Controller {
private:
	Chip8* emulator;
	map<SDL_Keycode, uint8_t> keymap;
	const char* filePath;
	uint8_t debugType;

	void addPressedKey(SDL_Event, int);


public:
	Controller(const char* , uint8_t);
	bool loadFile();
	int emulate();
	int emulateProgram();
	int emulateDebug();
};