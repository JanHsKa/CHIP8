#include <iostream>
#include "SDL2/SDL.h"

using namespace::std;

static Uint8 *audio_pos; 
static Uint32 audio_len;
static Uint8 *wav_buffer;

class Soundcontroller {
private:
    const static int AMPLITUDE = 28000;
    const static int SAMPLE_RATE = 44100;

    // SDL_AudioSpec* wantedSpec;
    // SDL_AudioSpec* currentSpec;

    

    SDL_AudioDeviceID audioDevice;

public:
    Soundcontroller();
    static void audioCallback(void *data, Uint8 *buffer, int bytes);
    void playSound();
    ~Soundcontroller();
};