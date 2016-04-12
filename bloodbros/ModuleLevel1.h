#ifndef __MODULELEVEL1_H__
#define __MODULELEVEL_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"

struct SDL_Texture;

class ModuleLevel1 : public Module
{
public:
	ModuleLevel1();
	~ModuleLevel1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect background;
	SDL_Rect house1, house2;
	

	SDL_Texture* graphics = nullptr;
	
};

#endif // __MODULELEVEL1_H__