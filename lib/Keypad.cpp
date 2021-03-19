#include "Keypad.h"


Keypad::Keypad() {
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

    initialize();
}

void Keypad::initialize() {
    for (int i = 0; i < KEYCOUNT; i++) {
            keypad[i] = 0;
        }
}

void Keypad::changePressedKey(SDL_Event event, int value) {
    SDL_Keycode key = event.key.keysym.sym;
	if (keymap.find(key) != keymap.end()) {
		keypad[keymap.at(key)] = value;
	}
}

void Keypad::resetKey(uint8_t i) {
	keypad[i] = 0;
}

bool Keypad::isKeypressed(uint8_t i) {
    return keypad[i];
}

bool Keypad::isAnyKeypressed() {
    for (int i = 0; i < KEYCOUNT; i++) {
        if (keypad[i]) {
            return true;
        }
    }
    return false;
}


int Keypad::getPressedKey() {
    for (int i = 0; i < KEYCOUNT; i++) {
		if (keypad[i]) {
            return i;
        }
	}

    return -1;
}
