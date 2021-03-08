#include <iostream>
#include <map>
#include "SDL2/SDL.h"
#include "Macros.h"


using namespace std;

class Keyboard {
private:
    map<SDL_Keycode, uint8_t> keymap;
    uint8_t keypad[KEYCOUNT];
    bool quit;

    void changePressedKey(SDL_Event event, int value);

public:
    Keyboard();
    bool checkInput();
    bool getQuit();
    uint8_t* getKeypad();
};