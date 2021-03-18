#include "Soundcontroller.h"
#include "Macros.h"

Soundcontroller::Soundcontroller() {

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        cerr<<"Failed to initialize: "<<endl;
        cerr<<SDL_GetError()<<endl<<endl;
    }

    int sampleNumber = 0;

    wantedSpec.freq = SAMPLE_RATE;
    wantedSpec.format = AUDIO_S16SYS;
    wantedSpec.channels = 1;
    wantedSpec.samples = 2048;
    wantedSpec.callback = audioCallback;
    wantedSpec.userdata = &sampleNumber; 

    audioDevice = SDL_OpenAudioDevice(NULL, 0, &wantedSpec, &currentSpec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
}

void Soundcontroller::audioCallback(void *user_data, Uint8 *raw_buffer, int bytes) {
    Sint16 *buffer = (Sint16*)raw_buffer;
    int length = bytes / 2;
    int &sampleNumber(*(int*)user_data);

    for(int i = 0; i < length; i++, sampleNumber++) {
        double time = (double)sampleNumber / (double)SAMPLE_RATE;
        buffer[i] = (Sint16)(AMPLITUDE * sin(2.0f * M_PI * 441.0f * time));
    }
}

void Soundcontroller::playSound() {
    SDL_PauseAudioDevice(audioDevice, 0);
    SDL_Delay(CLOCK_RATE);
    SDL_PauseAudioDevice(audioDevice, 1);
}

Soundcontroller::~Soundcontroller()
{
    SDL_CloseAudioDevice(audioDevice);
}