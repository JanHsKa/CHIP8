#include <iostream>
#include "Controller.h"
#include "SDL2/SDL.h"

using namespace std;

int main(int argc, char** argv) {
	for (int i = 0; i < argc; ++i) 
        cout << argv[i] << "\n"; 
	
	//Controller* controller = new Controller(argv[1],0);

	
	//return controller->emulate();

	return 0;
}
