#include "DebugDisplay.h"
#include <sstream>
#include <iomanip>



DebugDisplay::DebugDisplay(Chip8* chip8) : Display(chip8),
    textColor({0,0,0,0}) {
    fontSize = 30;
    debugOffset = 0;
    windowHeight = fontSize * DEBUG_LINES;
    windowWidth = 640;
    lastButtonPress = 0;
    quitWindow = false;
    redraw = true;
    maxDebugLines = 0;
}

void  DebugDisplay::initialize() {
    printDebugStart();
    maxDebugLines = cpu->getProgramSize();
    initWindow();
    loadOpcode();
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

void  DebugDisplay::checkForDraw() {
   // if (SDL_GetWindowFlags(window) & SDL_WINDOW_MOUSE_FOCUS || SDL_GetWindowFlags(window) & SDL_WINDOW_INPUT_FOCUS) {
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0)
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quitWindow = true;
                    break;

                case SDL_MOUSEBUTTONUP:
                    doubleClick(event.button);
                    break;

                case SDL_MOUSEWHEEL:
                    scrollText(event.wheel);
                    break;
            }
        }
    
    //}
}

void DebugDisplay::scrollText(SDL_MouseWheelEvent wheel) {
    int y = wheel.y;
    
    if (y > debugOffset) {
        debugOffset = 0;
    } else if ((debugOffset - y) > maxDebugLines) {
        debugOffset = maxDebugLines - DEBUG_LINES;
    } else {
        debugOffset -= y;
    }
    
    updateTextures();
    redraw = true;
}

void DebugDisplay::doubleClick(SDL_MouseButtonEvent click) {
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

void DebugDisplay::markClickedLine(int y) {
    int row = y / fontSize;
    if (programCode.at(row + debugOffset).marked) {
        programCode.at(row+debugOffset).marked = false;
    } else {
        programCode.at(row+debugOffset).marked = true;
    }
    opcodeTexture.at(row)->setText(transformLine(row + debugOffset));
    opcodeTexture.at(row)->renderText();
    redraw = true;
}

void DebugDisplay::loadOpcode() {
    debugOutput.clear();
    programCode.clear();
    int opcode;
    if (maxDebugLines > DEBUG_LINES) {
        for (int i = 0; i < maxDebugLines; i++) {
            programCode.push_back({opcodeToString(cpu->getOpcode(i)), false, i});
            //debugOutput.push_back(to_string(i) + "      " + opcodeToString(cpu->getOpcode(i)));
        }
    } 
}

string DebugDisplay::opcodeToString(int opcode) {
    stringstream st;
    st <<"0x" <<hex<<setw(4)<<setfill('0')<<opcode;
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
    for (int i = debugOffset; i < DEBUG_LINES + debugOffset; i++) {
        DebugTexture *newTexture = new DebugTexture(font, renderer, textColor, transformLine(i));
        opcodeTexture.push_back(newTexture);
    }
}

void DebugDisplay::updateTextures() {
    cout<<opcodeTexture.size()<<endl;
    cout<<programCode.size()<<endl;

    for (int i = 0; i < DEBUG_LINES; i++) {
        opcodeTexture.at(i)->setText(transformLine(i + debugOffset));
        opcodeTexture.at(i)->renderText();
    }
}


string DebugDisplay::transformLine(int i) {
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

void DebugDisplay::draw() {
    if (redraw) {
        drawDebugLine("test", 0);
    }
    redraw = false;
}