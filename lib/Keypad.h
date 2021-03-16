#pragma once
#include <iostream>
#include <map>
#include "SDL2/SDL.h"
#include "Macros.h"


using namespace std;

class Keypad {
private:
    map<SDL_Keycode, uint8_t> keymap;
    uint16_t keypad[KEYCOUNT];

public:
    Keypad();
    void changePressedKey(SDL_Event event, int value);
    void initialize();
    bool isKeypressed(uint8_t i);
    bool isAnyKeypressed();
    int getPressedKey();
};