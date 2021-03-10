#include "Keypad.h"


Keypad::Keypad() {

    quit = false;

    keymap.insert({SDLK_1, 0x1});
	keymap.insert({SDLK_2, 0x2});
	keymap.insert({SDLK_3, 0x3});
	keymap.insert({SDLK_4, 0xC});
	keymap.insert({SDLK_q, 0x4});
	keymap.insert({SDLK_w, 0x5});
	keymap.insert({SDLK_e, 0x6});
	keymap.insert({SDLK_r, 0xD});
	keymap.insert({SDLK_a, 0x7});
	keymap.insert({SDLK_s, 0x8});
	keymap.insert({SDLK_d, 0x9});
	keymap.insert({SDLK_f, 0xE});
	keymap.insert({SDLK_y, 0xA});
	keymap.insert({SDLK_x, 0x0});
	keymap.insert({SDLK_c, 0xB});
	keymap.insert({SDLK_v, 0xF});
}

bool Keypad::checkInput() {
    bool keypressed = false;

    SDL_Event e;

    while(SDL_PollEvent(&e) != 0)
    {
        switch(e.type)
        {
            case SDL_QUIT:
                quit = true;
                keypressed = true;
                break;

            case SDL_KEYDOWN:
                changePressedKey(e, 1);
                keypressed = true;
                break;

            case SDL_KEYUP:
                changePressedKey(e, 0);
                keypressed = true;
                break;
        }
    }
    return keypressed;
}

void Keypad::changePressedKey(SDL_Event event, int value) {
    SDL_Keycode key = event.key.keysym.sym;
	if (keymap.find(key) != keymap.end()) {
		keypad[keymap.at(key)] = value;
	}
}

bool Keypad::isKeypressed(int i) {
    return keypad[i];
}

bool Keypad::isAnyKeypressed() {
    return keypad.any();
}


int Keypad::getPressedKey() {
    for (int i = 0; i < KEYCOUNT; i++) {
		if (keypad[i]) {
            return i;
        }
	}

    return -1;
}

bool Keypad::getQuit() {
    return quit;
}
