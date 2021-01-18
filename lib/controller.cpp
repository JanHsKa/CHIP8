#include "Controller.h"
#include "SDL2/SDL.h"

Controller::Controller(const char* file, uint8_t debug) : filePath(file), 
	keymap{SDLK_1, SDLK_2, SDLK_3, SDLK_4, 
		SDLK_q, SDLK_w, SDLK_e, SDLK_r, 
		SDLK_a, SDLK_s, SDLK_d, SDLK_f, 
		SDLK_y, SDLK_x, SDLK_c, SDLK_v}  {
	debugType = debug;
	emulator = new chip8();
}

bool Controller::loadFile()
{
	return emulator->load(filePath);
}