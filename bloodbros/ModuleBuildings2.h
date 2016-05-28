#ifndef __MODULEBUILDING2_H__
#define __MODULEBUILDING2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

enum buildingtype2{ YELLOW2, PURPLE2, WINDMILL2, WHEEL2, TREES2, ROCK2 };

struct SDL_Texture;

struct Building2
{
	SDL_Rect build;
	Animation movement;
	Animation destroy;
	uint fx = 0;
	fPoint position;
	bool fx_played = false;
	Collider* collider = nullptr;
	buildingtype2 mytype;
	uint hits = 0;
	Building2();
	Building2(const Building2& p);
	~Building2();
	bool Update();
	const Collider* get_collider()const;
};


class ModuleBuilding2 : public Module
{
public:
	ModuleBuilding2();
	~ModuleBuilding2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void AddBuilding2(const Building2& particle, int x, int y);


private:

	SDL_Texture* graphics = nullptr;
	Building2* active[MAX_BUILDINGS];
	uint last_building = 0;

public:


	Building2 yellow;
	Building2 purple;
	Building2 yellow2;
	Building2 purple2;
	Building2 mill;
	Building2 trees;
	Building2 rock;

	bool purplealive = true;
	bool yellowalive = true;
	bool windmillalive = true;

};

#endif // __MODULEBUILDING2_H__