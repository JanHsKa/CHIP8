#include <iostream>
#include "SDL2/SDL.h"

using namespace::std;

class Soundcontroller {
private:
    const static int AMPLITUDE = 28000;
    const static int SAMPLE_RATE = 44100;

    SDL_AudioSpec want;
    SDL_AudioSpec have;

    SDL_AudioDeviceID m_device;

public:
    static void audioCallback(void *user_data, Uint8 *raw_buffer, int bytes);
    Soundcontroller();
    ~Soundcontroller();
    void playSound();
};