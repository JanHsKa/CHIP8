#include <iostream>
#include "Display.h"
#include "Macros.h"
#include "SDL2/SDL_ttf.h"
#include <sstream>
#include <iterator>


Display::Display(Chip8 *chip8): 
    debugColor({0,0,0,0}),
    cpu(chip8) {
    width = SCALE * COLUMNS;
    height = SCALE * ROWS;
    fontSize = 30;
    debugHeight = fontSize * 20;
    debugWidth = 640;

	cpu->copyGraphicBuffer(pixelMap);

}

void Display::initialize() {

    SDL_Init(true);
	window = SDL_CreateWindow("CHIP 8",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height,
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

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	 
	texture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            COLUMNS, ROWS); 
}

void Display::initDebugWindow() {
    if (TTF_Init() < 0) {
        cout<<"error: "<<TTF_GetError()<<endl;
    }
    
    debugWindow = SDL_CreateWindow("Debug",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          debugWidth, debugHeight,
                                          SDL_WINDOW_SHOWN);

    if(!debugWindow)
    {
        cout << "Failed to create window\n";
    }


    debugFont = TTF_OpenFont("Font/arial.ttf", fontSize);
	debugRenderer = SDL_CreateRenderer(debugWindow, -1, SDL_RENDERER_ACCELERATED);
	if (debugRenderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

    SDL_SetRenderDrawColor(debugRenderer, 200, 200, 200, 200);

    loadOpcode();
    createTextures();
}

void Display::checkForDraw() {
	if (cpu->getDrawFlag()) {
		cpu->copyGraphicBuffer(pixelMap);
		draw();			
		cpu->setDrawFlag(false);
	}
}

void Display::draw() {
    cout<<"Drawing"<<endl;
    int error = 0;
    error = SDL_UpdateTexture(texture, NULL, pixelMap, COLUMNS * sizeof(Uint32));
    if (error > 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }
    error = SDL_RenderCopy(renderer, texture, NULL, NULL);
    cout<<"renderCopy: "<<error<<endl;
	SDL_RenderPresent(renderer);
}

void Display::createTextures() {
    for (int i = 0; i < DEBUG_LINES; i++) {
        DebugTexture *newTexture = new DebugTexture(debugFont, debugRenderer, debugColor, debugOutput.at(i));
        opcodeTexture.push_back(newTexture);

        // SDL_Surface* newSurface = TTF_RenderText_Solid(debugFont, debugOutput.at(i).c_str(), debugColor);
        // SDL_Rect textRectangle;
        // textRectangle.x = 0;
        // textRectangle.y = 0;
        // textRectangle.w = newSurface->w;
        // textRectangle.h = newSurface->h;

        // SDL_Texture* newTexture = SDL_CreateTextureFromSurface(debugRenderer,
        //         newSurface);
        // SDL_QueryTexture(newTexture, NULL, NULL, &textRectangle.h, &textRectangle.w);
        // normalTexture.push_back(newTexture);
        // SDL_FreeSurface(newSurface);
    }
}

void Display::drawDebug() {
    // string completeOutput;
    // for (int i = 0; i < DEBUG_LINES; i++) {
    //     completeOutput.append(debugOutput.at(i));
    // }
    //SDL_RenderClear(debugRenderer);

    // for (int i = 0; i < DEBUG_LINES; i++) {
    //     drawDebugLine(debugOutput[i], i * 30);
    // }
    drawDebugLine("test", 0);

}

void Display::drawDebugLine(string output, int startY) {
    int success = 0;
    SDL_Rect startPos;
    startPos.x = 0;
    startPos.y = 0;
    startPos.w = 100;
    startPos.h = fontSize;

    SDL_RenderClear(debugRenderer);
    for (int i = 0; i < DEBUG_LINES; i++) {
        startPos.w = opcodeTexture.at(i)->getWidth();
        startPos.h = opcodeTexture.at(i)->getHeight();
        startPos.y = i * fontSize;
        //string text = opcodeTexture.at(i)->getText();
        //success = SDL_RenderCopy(debugRenderer, normalTexture.at(i), NULL, &startPos);
        success = SDL_RenderCopy(debugRenderer, opcodeTexture.at(i)->getTexture(), NULL, &startPos);

        cout<<"success: "<<success<<SDL_GetError()<<endl;
    }

    cout<<"render success: "<<success<<endl;
    SDL_RenderPresent(debugRenderer);
}

void Display::loadOpcode() {
    debugOutput.clear();
    int size = cpu->getProgramSize();
    int opcode;
    if (size > DEBUG_LINES) {
        for (int i = 0; i < DEBUG_LINES; i++) {
            debugOutput.push_back(to_string(i) + "    " + opcodeToString(cpu->getOpcode(i)));
        }
    }
}

string Display::opcodeToString(int opcode) {
    stringstream st;
    st <<"0x"<<hex<<opcode;
    return st.str(); 
}


void Display::clearScreen() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Display::destroy() {
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_DestroyTexture(debugTexture);
	SDL_Quit();
}
