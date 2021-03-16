#pragma once
#include <iostream>
#include "GameDisplay.h"
#include "Display.h"
using namespace std;

struct DebugOpcode {
    string opcode;
    bool marked;
    int line;
};


class DebugDisplay : public Display {
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
    
    void markClickedLine(int y);
    string transformLine(int i);    
    void updateTextures();
    void printDebugStart();
    void initWindow();

public:
    DebugDisplay(Chip8* chip8);
    void draw();
    void initialize();
    void checkForDraw();
    void scrollText(SDL_MouseWheelEvent wheel);
    void doubleClick(SDL_MouseButtonEvent click);
};