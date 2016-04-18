#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	

public:

	SDL_Texture* graphics = nullptr;
	iPoint position;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation left;
	Animation right;
	Animation pig;
	Collider* player;



};

#endif