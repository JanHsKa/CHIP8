#include <iostream>
#include <map>
#include "SDL2/SDL.h"
#include "Macros.h"
#include <bitset>


using namespace std;

class Keypad {
private:
    map<SDL_Keycode, uint8_t> keymap;
    unsigned short keypad[KEYCOUNT];
    bool quit;

    void changePressedKey(SDL_Event event, int value);

public:
    Keypad();
    void initialize();
    bool checkInput();
    bool getQuit();
    bool isKeypressed(int i);
    bool isAnyKeypressed();
    int getPressedKey();
};