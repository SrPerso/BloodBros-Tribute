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
	CROUCH,
	DEAD,
	WIN,
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
	Animation blackpig;
	Animation shot;
	Collider* player;
	Animation jump_left;
	Animation jump_right;
	Animation scope;
	Animation dead;
	Animation shotidle;
	Animation shotleft;
	Animation shotleftop;
	Animation shotopleft;
	Animation shotop;
	Animation shotright;
	Animation shotrighttop;
	Animation shotopright;
	Animation dance;

	Animation crouch;
	Animation crouchshotidle;
	Animation crouchshotleft;
	Animation crouchshotlefttop;
	Animation crouchshottopleft;
	Animation crouchshotop;
	Animation crouchshotright;
	Animation crouchshotrighttop;
	Animation crouchshotopright;

	uint hp;
	bool hit = true;
	bool god = false;
	//fonts

	int font_score = 2;
	char score_text[10];
	uint score = 0;
	

};

#endif