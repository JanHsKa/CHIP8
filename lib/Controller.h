#include <iostream>
#include "chip8.h"

using namespace std;


class Controller {
private:
	chip8* emulator;
	uint8_t keymap[16];
	const char* filePath;
	uint8_t debugType;


public:
	Controller(const char* , uint8_t);
	bool loadFile();
	void emulateCycle();
};