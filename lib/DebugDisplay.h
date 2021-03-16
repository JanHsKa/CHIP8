#pragma once
#include <iostream>
#include "Display.h"

using namespace std;

struct DebugOpcode {
    string opcode;
    bool marked;
    int line;
};


class DebugDisplay : Display {
private:
    int fontSize;
    int debugOffset;
    bool quitWindow;
    int lastButtonPress;
    bool redraw;
    int maxDebugLines;

    vector<DebugOpcode> programCode;
    vector<string> debugOutput;
    vector<DebugTexture*> opcodeTexture;

    TTF_Font * font;
    SDL_Color textColor;

    void loadOpcode();
    string opcodeToString(int opcode);
    void drawDebugLine(string output, int startY);
    void createTextures();
    void scrollText(SDL_MouseWheelEvent wheel);
    void doubleClick(SDL_MouseButtonEvent click);
    void markClickedLine(int y);
    string transformLine(int i);
    void updateTextures();

public:
    DebugDisplay(Chip8* chip8);
    void virtual draw();
    void virtual initialize();
    void virtual checkForDraw();
};