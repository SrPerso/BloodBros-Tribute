#ifndef __ModuleEnemiesMid_H__
#define __ModuleEnemiesMid_H__

#include "Module.h"

#define MAX_ENEMIES 100


enum ENEMY_TYPES3
{
	NO_TYPE3,
	GREENCOWBOYMEDIUM,
	INDIANMEDIUM,
	GREENCOWBOYJUMPERRIGTH,
	GREENCOWBOYJUMPERLEFT

};

class Enemy;

struct EnemyInfo3
{
	ENEMY_TYPES3 type = ENEMY_TYPES3::NO_TYPE3;
	int x, y;
};

class ModuleEnemiesMid : public Module
{
public:

	ModuleEnemiesMid();
	~ModuleEnemiesMid();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES3 type, int x, int y);
	uint hits = 0;

private:

	void SpawnEnemy(const EnemyInfo3& info);

private:

	EnemyInfo3 queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
	SDL_Texture* sprites2;
};

#endif // __ModuleEnemiesFront_H__