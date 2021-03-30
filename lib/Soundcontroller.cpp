#include "Soundcontroller.h"
#include "Macros.h"

Soundcontroller::Soundcontroller() {

    // if (SDL_Init(SDL_INIT_AUDIO) != 0) {
    //     cerr<<"Failed to initialize: "<<endl;
    //     cerr<<SDL_GetError()<<endl<<endl;
    // }

    // wantedSpec = new SDL_AudioSpec();
    // currentSpec = new SDL_AudioSpec();

    // int sampleNumber = 0;

    // wantedSpec->freq = SAMPLE_RATE;
    // wantedSpec->format = AUDIO_S16SYS;
    // wantedSpec->channels = 1;
    // wantedSpec->samples = 2048;
    // wantedSpec->callback = audioCallback;
    // wantedSpec->userdata = &sampleNumber; 

    // audioDevice = SDL_OpenAudioDevice(NULL, 0, wantedSpec, currentSpec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);

    static Uint32 wav_length; // length of our sample
	//static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music

	if( SDL_LoadWAV("Sound/126423__makofox__shoot-laser.wav", &wav_spec, &wav_buffer, &wav_length) == NULL ){
	  cerr<<"Failed to load WAV"<<endl;
	}

	wav_spec.callback = audioCallback;
	wav_spec.userdata = NULL;

	audio_pos = wav_buffer; 
	audio_len = wav_length; 

    audioDevice = SDL_OpenAudio(&wav_spec, NULL);

}

void Soundcontroller::audioCallback(void *userdata, Uint8 *stream, int len) {
	
	if (audio_len ==0)
		return;
	
	len = ( len > audio_len ? audio_len : len );
	//SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another
	
	audio_pos += len;
	audio_len -= len;
}

// void Soundcontroller::audioCallback(void *user_data, Uint8 *raw_buffer, int bytes) {
//     Sint16 *buffer = (Sint16*)raw_buffer;
//     int length = bytes / 2;
//     int &sampleNumber(*(int*)user_data);

//     for(int i = 0; i < length; i++, sampleNumber++) {
//         double time = (double)sampleNumber / (double)SAMPLE_RATE;
//         buffer[i] = (Sint16)(AMPLITUDE * sin(2.0f * M_PI * 441.0f * time));
//     }
// }

void Soundcontroller::playSound() {
    SDL_PauseAudioDevice(audioDevice, 0);
    SDL_Delay(16);
    SDL_PauseAudioDevice(audioDevice, 1);
}

Soundcontroller::~Soundcontroller()
{
    SDL_CloseAudioDevice(audioDevice);
    SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);
}