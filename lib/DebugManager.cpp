#include "DebugManager.h"
#include <iomanip>


DebugManager::DebugManager(DebugDisplay* display, Chip8* chip8) :
    debugDisplay(display),
    cpu(chip8) {
    keymap.insert({SDLK_F6, Step_over});
	keymap.insert({SDLK_F8, Continue});
	keymap.insert({SDLK_F7, Debug_Output});
    lastButtonPress = 0;
    offset = 150;
    maxDebugLines = 0;

}

void DebugManager::initialize() {
    loadOpcode();
    createDebugOutput();
}


void DebugManager::setPressedDebugKey(SDL_Event event, int value) {
    SDL_Keycode key = event.key.keysym.sym;
	if (keymap.find(key) != keymap.end()) {
		debugKeys[keymap.at(key)] = value;
	}
}

bool DebugManager::isDebugKeyPressed(DebugKey key) {
    return debugKeys[key];
}


string DebugManager::opcodeToString(int opcode) {
    stringstream st;
    st <<"0x" <<hex<<setw(4)<<setfill('0')<<opcode;
    return st.str(); 
}

void DebugManager::loadOpcode() {
    maxDebugLines = cpu->getProgramSize();
    programCode.clear();
    int opcode;
    if (maxDebugLines > DEBUG_LINES) {
        for (int i = 0; i < maxDebugLines; i++) {
            programCode.push_back({opcodeToString(cpu->getOpcode(i)), false, i});
        }
    } 
    maxDebugLines = programCode.size();
}

void DebugManager::doubleClick(SDL_MouseButtonEvent click) {
    int ticks = SDL_GetTicks();
    if (click.button = SDL_BUTTON_LEFT) {
        if (SDL_GetTicks() - lastButtonPress < 2000) {
            markClickedLine(click.y);
            lastButtonPress = 0;
        } else {
            lastButtonPress = SDL_GetTicks();
        }
    }
}

void DebugManager::markClickedLine(int line) {
    int row = debugDisplay->getClickedRow(line);
    if (programCode.at(row + offset).marked) {
        programCode.at(row + offset).marked = false;
    } else {
        programCode.at(row + offset).marked = true;
    }
    
    debugDisplay->updateMarkedLine(transformLine(row + offset), row);
}

void DebugManager::scrollText(SDL_MouseWheelEvent wheel) {
    int scrollRange = wheel.y;
    cout<<"offset - scrollrange"<<dec<<offset-scrollRange<<endl;
    if (scrollRange > offset) {
        offset = 0;
    } else if ((offset + DEBUG_LINES - scrollRange) > maxDebugLines) {
        offset = maxDebugLines - DEBUG_LINES;
    } else {
        offset -= scrollRange;
    }
    
    updateWindowLines();
}

void DebugManager::updateWindowLines() {
    for (int i = 0; i < DEBUG_LINES; i++) {
        debugDisplay->updateMarkedLine(transformLine(i + offset), i);
    }
}


string DebugManager::transformLine(int i) {
    stringstream st;
    st <<i<<"  ";
    if (programCode.at(i).marked) {
        st<<">";
    } else {
        st<<"  ";
    }
    st<<programCode.at(i).opcode;
    return st.str();
}

void DebugManager::createDebugOutput() {
    vector<string> newOutput;

    for (int i = offset; i < offset + DEBUG_LINES; i++) {
        newOutput.push_back(transformLine(i));
    }

    debugDisplay->updateOutput(newOutput);
}
