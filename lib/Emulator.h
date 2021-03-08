#include <iostream>
#include "Chip8.h"
#include "SDL2/SDL.h"
#include "Display.h"
#include <map>
#include "Keyboard.h"
#include "Soundcontroller.h"

using namespace std;


class Emulator {
private:
	Chip8* cpu;
	Display* display; 
	Keyboard* keyboard;
	Soundcontroller* soundController;

	map<SDL_Keycode, uint8_t> keymap;
	const char* filePath;
	uint8_t debugType;

	unsigned int lastUpdate;

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