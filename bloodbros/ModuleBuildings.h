#ifndef __MODULEBUILDING_H__
#define __MODULEBUILDING_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_EXTRAS 20

struct SDL_Texture;

struct Building
{
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	Collider* collider = nullptr;

	Building();
	Building(const Building& p);
	~Building();
	bool Update();
	const Collider* get_collider()const;
};


class ModuleBuilding: public Module
{
public:
	ModuleBuilding();
	~ModuleBuilding();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void AddBuilding(const Building& particle, int x, int y, Uint32 delay = 0);


private:

	SDL_Texture* graphics = nullptr;
	Building* active[MAX_EXTRAS];
	uint last_particle = 0;

public:


	Building yellow;
	Building purple;

};

#endif // __MODULEBUILDING_H__