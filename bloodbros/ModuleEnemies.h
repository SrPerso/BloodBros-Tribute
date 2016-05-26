#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
//#include "Enemy_RedBird.h"

#define MAX_ENEMIES 100


enum ENEMY_TYPES
{
	NO_TYPE,
	PURPLEPLANE,
	GREENCOWBOY,
	CHARRIOT,
	BLUECOWBOY,
	GREENRIGHTCOWBOY,
	JUMPER,
	GREENCOWBOYMEDIUM,
	INDIANMEDIUM
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y);
	uint hits = 0;

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
	SDL_Texture* sprites2;
};

#endif // __ModuleEnemies_H__