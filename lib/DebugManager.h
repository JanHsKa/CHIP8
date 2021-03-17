#pragma once

#include <iostream>
#include <map>
#include "DebugDisplay.h"
#include <vector>

using namespace std;

enum DebugKey {
    Step_over,
    Continue,
    Debug_Output
};  

struct DebugOpcode {
    string opcode;
    bool marked;
    int line;
};

class DebugManager {
private:
    DebugDisplay* debugDisplay;
    Chip8* cpu;
    map<SDL_Keycode, int> keymap; 
    bool debugKeys[DEBUG_KEY_COUNT];
    vector<DebugOpcode> programCode;

    int offset;
    int lastButtonPress;
    int maxDebugLines;

    void loadOpcode();
    string opcodeToString(int opcode);
    void markClickedLine(int line);
    string transformLine(int line);   
    void updateWindowLines();
    void createDebugOutput();

public:
    DebugManager(DebugDisplay* display, Chip8* chip8);
    void initialize();
    void setPressedDebugKey(SDL_Event event, int value);
    void scrollText(SDL_MouseWheelEvent wheel);
    void doubleClick(SDL_MouseButtonEvent click);

    bool isDebugKeyPressed(DebugKey key);
    bool continueProgram();
};