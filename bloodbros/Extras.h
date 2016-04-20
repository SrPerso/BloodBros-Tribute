#ifndef __EXTRAS_H__
#define __EXTRAS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;

struct Extra
{
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	Collider* collider=nullptr;

	Extra();
	Extra(const Extra& p);
	bool Update();
};

class ModuleExtra : public Module
{
public:
	ModuleExtra();
	~ModuleExtra();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void AddExtra(const Extra& particle, int x, int y, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Extra* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:


	Extra pig;

};

#endif // __MODULEPARTICLES_H__