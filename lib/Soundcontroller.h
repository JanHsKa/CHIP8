#include <iostream>
#include "SDL2/SDL.h"

using namespace::std;

class Soundcontroller {
private:
    const static int AMPLITUDE = 28000;
    const static int SAMPLE_RATE = 44100;

    SDL_AudioSpec wantedSpec;
    SDL_AudioSpec currentSpec;

    SDL_AudioDeviceID audioDevice;

public:
    static void audioCallback(void *data, Uint8 *buffer, int bytes);
    Soundcontroller();
    void playSound();
    ~Soundcontroller();
};