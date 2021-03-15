#pragma once
#include <iostream>
#include "Display.h"

using namespace std;

class DebugDisplay : Display {
private:
    int fontSize;
    int debugOffset;

    vector<string> debugOutput;
    vector<DebugTexture*> opcodeTexture;

    TTF_Font * font;
    SDL_Color textColor;

    void loadOpcode();
    string opcodeToString(int opcode);
    void drawDebugLine(string output, int startY);
    void createTextures();

public:
    DebugDisplay(Chip8* chip8);
    void virtual draw();
    void virtual initialize();
    void virtual checkForDraw();
};