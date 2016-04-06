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

	bool Init();
	bool CleanUp();
	Mix_Music *music;
	Mix_Music *Load();

};

#endif