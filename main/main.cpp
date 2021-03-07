#include <iostream>
#include "Emulator.h"
#include "SDL2/SDL.h"

using namespace std;

int main(int argc, char** argv) {
	for (int i = 0; i < argc; ++i) 
        cout << argv[i] << "\n"; 
	
	Emulator* emulator = new Emulator(argv[1],0);

	
	return emulator->emulateProgram();
}
