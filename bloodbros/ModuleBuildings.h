#ifndef __MODULEBUILDING_H__
#define __MODULEBUILDING_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"


#define MAX_BUILDINGS 50

enum buildingtype{ YELLOW, PURPLE, WINDMILL, WHEEL};

struct SDL_Texture;

struct Building
{
	SDL_Rect build;
	Animation movement;
	Animation destroy;
	uint fx = 0;
	fPoint position;
	bool fx_played = false;
	Collider* collider = nullptr;
	buildingtype mytype;
	uint hits = 0;
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
	void AddBuilding(const Building& particle, int x, int y);


private:

	SDL_Texture* graphics = nullptr;
	Building* active[MAX_BUILDINGS];
	uint last_building = 0;

public:


	Building yellow;
	Building purple;
	Building yellow2;
	Building purple2;
	Building mill;

};

#endif // __MODULEBUILDING_H__