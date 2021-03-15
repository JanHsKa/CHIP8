#include "DebugDisplay.h"
#include <sstream>



DebugDisplay::DebugDisplay(Chip8* chip8) : Display(chip8),
    textColor({0,0,0,0}) {
    fontSize = 30;
    debugOffset = 0;
    windowHeight = fontSize * 20;
    windowWidth = 640;
}

void  DebugDisplay::initialize() {
    if (TTF_Init() < 0) {
        cout<<"error: "<<TTF_GetError()<<endl;
    }
    
    window = SDL_CreateWindow("Debug",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          windowWidth, windowHeight,
                                          SDL_WINDOW_SHOWN);

    if(!window)
    {
        cout << "Failed to create window\n";
    }


    font = TTF_OpenFont("Font/arial.ttf", fontSize);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);

    loadOpcode();
    createTextures();
}

void  DebugDisplay::checkForDraw() {
    SDL_Event event;

    SDL_GetWindowFlags(window);
}

void DebugDisplay::loadOpcode() {
    debugOutput.clear();
    int size = cpu->getProgramSize();
    int opcode;
    if (size > DEBUG_LINES) {
        for (int i = 0; i < DEBUG_LINES; i++) {
            debugOutput.push_back(to_string(i) + "      " + opcodeToString(cpu->getOpcode(i)));
        }
    } 
}

string DebugDisplay::opcodeToString(int opcode) {
    stringstream st;
    st <<"0x"<<hex<<opcode;
    return st.str(); 
}

void DebugDisplay::drawDebugLine(string output, int startY) {
    int success = 0;
    SDL_Rect startPos;
    startPos.x = 0;
    startPos.y = 0;
    startPos.w = 0;
    startPos.h = fontSize;

    SDL_RenderClear(renderer);
    for (int i = 0; i < DEBUG_LINES; i++) {
        startPos.w = opcodeTexture.at(i)->getWidth();
        startPos.h = opcodeTexture.at(i)->getHeight();
        startPos.y = i * fontSize;
        success = SDL_RenderCopy(renderer, opcodeTexture.at(i)->getTexture(), NULL, &startPos);

        cout<<"success: "<<success<<SDL_GetError()<<endl;
    }

    cout<<"render success: "<<success<<endl;
    SDL_RenderPresent(renderer);
}

void DebugDisplay::createTextures() {
    for (int i = 0; i < DEBUG_LINES; i++) {
        DebugTexture *newTexture = new DebugTexture(font, renderer, textColor, debugOutput.at(i));
        opcodeTexture.push_back(newTexture);
    }
}

void DebugDisplay::draw() {
    drawDebugLine("test", 0);
}