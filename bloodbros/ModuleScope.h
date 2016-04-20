#ifndef __ModuleScope_H__
#define __ModuleScope_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "Extras.h"

struct SDL_Texture;

class ModuleScope : public Module
{
public:
	ModuleScope();
	~ModuleScope();

	bool Start();
	update_status Update();
	bool CleanUp();


public:

	SDL_Texture* graphics = nullptr;
	fPoint position;
	Animation* current_animation = nullptr;
	Collider* shot;
	Animation scope;
	Animation shoots;
	ModuleExtra* extra;

};

#endif