#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

struct SDL_Texture;

enum type{
	NORMAL,
	ROLL, 
	DEAD,
};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	

public:

	SDL_Texture* graphics = nullptr;
	fPoint position;
	Animation* current_animation = nullptr;
	type status;
	Animation idle;
	Animation left;
	Animation right;
	Animation pig;
	Animation shot;
	Collider* player;
	Animation jump_left;
	Animation jump_right;
	Animation scope;
	Animation dead;

};

#endif