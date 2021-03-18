#include "InputChecker.h"

InputChecker::InputChecker(DebugManager* debug, Keypad* keypad)  :
    debugManager(debug), 
    gameKeypad(keypad){

    quit = false;
}

void InputChecker::checkInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        switch(event.type)
        {
        case SDL_MOUSEBUTTONUP:
            debugManager->doubleClick(event.button);
            break;

        case SDL_MOUSEWHEEL:
            debugManager->scrollText(event.wheel);
            break;
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                quit = true;
            }
            break;

        case SDL_KEYDOWN:
            gameKeypad->changePressedKey(event, 1);
            debugManager->setPressedDebugKey(event, 1);
            break;

        case SDL_KEYUP:
            gameKeypad->changePressedKey(event, 0);
            debugManager->setPressedDebugKey(event, 0);
            break;
        }
    }
}

bool InputChecker::getQuit() {
    return quit;
}
