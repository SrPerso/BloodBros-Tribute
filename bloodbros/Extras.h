#ifndef __EXTRAS_H__
#define __EXTRAS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_EXTRAS 20

enum extratype{PIG, ZEPE};
struct SDL_Texture;

struct Extra
{

	Animation anim;
	Animation hit;
	uint fx = 0;
	fPoint position;
	fPoint speed;
	extratype type;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	Collider* collider=nullptr;

	Extra();
	Extra(const Extra& p);
	~Extra();
	bool Update();
	const Collider* get_collider()const;
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
	Extra* active[MAX_EXTRAS];
	uint last_particle = 0;

public:


	Extra pig;
	Extra zepe;

};

#endif // __MODULEPARTICLES_H__