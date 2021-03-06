#pragma once

#include <iostream>
#include <map>
#include "DebugDisplay.h"

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
    CPU* cpu;
    map<SDL_Keycode, int> keymap; 
    bool debugKeys[DEBUG_KEY_COUNT];
    vector<DebugOpcode> programCode;

    int offset;
    int lastButtonPress;
    int maxDebugLines;
    bool continueDebug;
    int currentLine;
    bool active;

    void loadOpcode();
    void markClickedLine(int line);
    void updateWindowLines();
    void createDebugOutput();
    
    string opcodeToString(int opcode);
    string transformLine(int line);   

    void setCurrentLine();
    bool isAtBreakPoint();
    void jumpToCurrentLine();
    void printStoppedAtLine();
    void scroll(SDL_MouseWheelEvent wheel);

public:
    DebugManager(DebugDisplay* display, CPU* chip8);
    void initialize();
    void setPressedDebugKey(SDL_Event event, int value);
    void scrollText(SDL_MouseWheelEvent wheel);
    void doubleClick(SDL_MouseButtonEvent click);

    bool isDebugKeyPressed(DebugKey key);
    bool continueProgram();

    void setActive(bool debug);
};