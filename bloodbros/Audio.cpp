#include"Audio.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )
#include "Globals.h"





ModuleAudio::ModuleAudio(){ };
ModuleAudio::~ModuleAudio(){ };

bool ModuleAudio::Init()
{
	LOG("Init Audio library");
	bool ret = true;

	// load support for the PNG image format
	int audioflags = MIX_INIT_OGG;
	
	int initted = Mix_Init(audioflags);

	if ((initted) != audioflags)
	{
		LOG("Could not initialize Audio lib. MIX_Init: %s", Mix_GetError());
		ret = false;
	}
	Load();

	return ret;
}

Mix_Music* ModuleAudio::Load(){
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	music = Mix_LoadMUS("honda.ogg");
	Mix_PlayMusic(music, -1);
	return music;
}



bool ModuleAudio::CleanUp(){
	LOG("Freeing textures and Audio library");
	Mix_CloseAudio();
	Mix_FreeMusic(music);
	music = NULL;
	

	return true;
}


