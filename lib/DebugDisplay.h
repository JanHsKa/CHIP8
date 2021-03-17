#pragma once
#include <iostream>
#include "GameDisplay.h"
#include "Display.h"
#include <map>
#include <regex>

using namespace std;


class DebugDisplay : public Display {
private:
    int fontSize;
    bool quitWindow;
    bool redraw;

    vector<string> debugOutput;
    vector<DebugTexture*> opcodeTexture;

    regex opcodeMap;

    TTF_Font * font;
    SDL_Color textColor;

    void drawDebugLine();
    void createTextures();

    void updateAllLines();
    void printDebugStart();
    void initWindow();

    void draw();
public:
    DebugDisplay(Chip8* chip8);
    int getClickedRow(int line);
    void updateMarkedLine(string lineText,int row);
    void updateOutput(vector<string> output);
    void initialize();
    void checkForDraw();
};