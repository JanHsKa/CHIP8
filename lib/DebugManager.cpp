#include "DebugManager.h"


DebugManager::DebugManager(DebugDisplay* display) :
    debugDisplay(display) {
    keymap.insert({SDLK_F6, Step_over});
	keymap.insert({SDLK_F8, Continue});
	keymap.insert({SDLK_F7, Debug_Output});
}

void DebugManager::setPressedDebugKey(SDL_Event event, int value) {
    SDL_Keycode key = event.key.keysym.sym;
	if (keymap.find(key) != keymap.end()) {
		debugKeys[keymap.at(key)] = value;
	}
}

void DebugManager::scrollText(SDL_MouseWheelEvent wheel) {
    debugDisplay->scrollText(wheel);
}

void DebugManager::doubleClick(SDL_MouseButtonEvent click) {
    debugDisplay->doubleClick(click);
}

bool DebugManager::isDebugKeyPressed(DebugKey key) {
    return debugKeys[key];
}