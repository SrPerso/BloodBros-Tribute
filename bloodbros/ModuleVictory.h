#ifndef __MODULEVICTORY_H__
#define __MODULEVICTORY_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleVictory : public Module
{
public:
	ModuleVictory();
	~ModuleVictory();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect victoryscreen;
};

#endif // __MODULEVICTORY_H__