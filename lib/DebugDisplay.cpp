#include "DebugDisplay.h"
#include <sstream>
#include <iomanip>



DebugDisplay::DebugDisplay(Chip8* chip8) : Display(chip8),
    textColor({0,0,0,0}) {
    fontSize = 30;
    windowHeight = fontSize * DEBUG_LINES;
    windowWidth = 640;
    quitWindow = false;
    redraw = true;

    opcodeMap = "asdf";
}

void  DebugDisplay::initialize() {
    printDebugStart();
    initWindow();
    createTextures();
}

void DebugDisplay::initWindow() {
    if (TTF_Init() < 0) {
        cout<<"error: "<<TTF_GetError()<<endl;
    }
    
    font = TTF_OpenFont("Font/arial.ttf", fontSize);

    window = SDL_CreateWindow("Debug",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_UNDEFINED,
        windowWidth, windowHeight,
        SDL_WINDOW_SHOWN);

    if(!window)
    {
        cout << "Failed to create window\n";
    }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
}

void DebugDisplay::printDebugStart() {
    cout << "Starting Debug Mode" <<endl;
	cout << "F6 : Step through program" <<endl;
	cout << "F7 : Print out current memory" <<endl;
	cout << "F8 : Run program normal" <<endl;
}

int DebugDisplay::getClickedRow(int line) {
    return line / fontSize;
}


void DebugDisplay::updateMarkedLine(string lineText,int row) {
    debugOutput.at(row) = lineText;
    opcodeTexture.at(row)->setText(lineText);
    opcodeTexture.at(row)->renderText();
    redraw = true;
}

void DebugDisplay::drawDebugLine() {
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

void DebugDisplay::updateAllLines() {
    for (int i = 0; i < DEBUG_LINES; i++) {
        opcodeTexture.at(i)->setText(debugOutput.at(i));
        opcodeTexture.at(i)->renderText();
    }
    redraw = true;
}

void DebugDisplay::checkForDraw() {
    if(redraw) {
        draw();
    }
}

void DebugDisplay::draw() {
    drawDebugLine();
    redraw = false;
}

void DebugDisplay::updateOutput(vector<string> output) {
    debugOutput = output;
}
