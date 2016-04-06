#ifndef _AUDIO_H
#define _AUDIO_H
#include "Globals.h"
#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"


class ModuleAudio :public Module
{
public:
	ModuleAudio();
	~ModuleAudio();
	// load support for the OGG and MOD sample/music formats
	int audioflag = MIX_INIT_OGG | MIX_INIT_MOD;
	// Initialize the audio library 

	bool Init();
	bool CleanUp();
	Mix_Music *music;
	Mix_Music *Load();

};

#endif