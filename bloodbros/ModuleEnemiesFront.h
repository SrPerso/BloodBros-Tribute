#ifndef __ModuleEnemiesFront_H__
#define __ModuleEnemiesFront_H__

#include "Module.h"
//#include "Enemy_RedBird.h"

#define MAX_ENEMIES 100


enum ENEMY_TYPES2
{
	NO_TYPE2,
	JUMPER,
	JUMPERSHOOT,
	GREENLEAVINGCOWBOY,
	INDIANLEAVING
};

class Enemy;

struct EnemyInfo2
{
	ENEMY_TYPES2 type = ENEMY_TYPES2::NO_TYPE2;
	int x, y;
};

class ModuleEnemiesFront : public Module
{
public:

	ModuleEnemiesFront();
	~ModuleEnemiesFront();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES2 type, int x, int y);
	uint hits = 0;

private:

	void SpawnEnemy(const EnemyInfo2& info);

private:

	EnemyInfo2 queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
	SDL_Texture* sprites2;
};

#endif // __ModuleEnemiesFront_H__