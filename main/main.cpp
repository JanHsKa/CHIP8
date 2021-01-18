#include <iostream>
#include "Controller.h"
#include "SDL2/SDL.h"

using namespace std;

int main(int argc, char** argv) {
	cout << "Hello CMake." << endl;
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

	SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          680, 480,
                                          0);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if(!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }

    SDL_UpdateWindowSurface(window);

	bool keep_window_open = true;
while(keep_window_open)
{
    SDL_Event e;
    while(SDL_PollEvent(&e) > 0)
    {
        switch(e.type)
        {
            case SDL_QUIT:
                keep_window_open = false;
                break;
        }

        SDL_UpdateWindowSurface(window);
    }
}
	
	Controller* controller = new Controller(argv[1],0);
	return 0;
}
