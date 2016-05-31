#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemiesFront.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"

#include "GreenCowBoy.h"

#include "GreenRight.h"
#include "ModulePlayer.h"
#include "Jumper.h"
#include "GreenCowBoyMedium.h"
#include "IndianMedium.h"
#include "GreenCowBoyLeavingTheHouse.h"
#include "IndianLeavingTheHouse.h"
#include "Jumpershoot.h"


/*#include "Enemy_RedBird.h"
#include "Enemy_Cookie.h"
#include "Enemy_Mech.h"*/

#define SPAWN_MARGIN 50

ModuleEnemiesFront::ModuleEnemiesFront()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;

}

// Destructor
ModuleEnemiesFront::~ModuleEnemiesFront()
{
}

bool ModuleEnemiesFront::Start()
{

	sprites = App->textures->Load("Images/Enemies.png");
	hits = 0;


	return true;
}

update_status ModuleEnemiesFront::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES2::NO_TYPE2)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES2::NO_TYPE2;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->to_delete == true)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemiesFront::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemiesFront::PostUpdate()
{
	// check camera position to decide what to spawn
	/*for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
	if (enemies[i] != nullptr)
	{
	if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
	{
	LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
	delete enemies[i];
	enemies[i] = nullptr;
	}
	}
	}*/

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemiesFront::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);


	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemiesFront::AddEnemy(ENEMY_TYPES2 type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES2::NO_TYPE2)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemiesFront::SpawnEnemy(const EnemyInfo2& info)
{

	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i); {

		if (i != MAX_ENEMIES)
		{
			switch (info.type)
			{
			case ENEMY_TYPES2::JUMPER:
				enemies[i] = new Jumper(info.x, info.y);
				break;
			case ENEMY_TYPES2::JUMPERSHOOT:
				enemies[i] = new Jumpershoot(info.x, info.y);
				break;
			case ENEMY_TYPES2::GREENLEAVINGCOWBOY:
				enemies[i] = new GreenCowBoyLeavingTheHouse(info.x, info.y);
				break;
			case ENEMY_TYPES2::INDIANLEAVING:
				enemies[i] = new IndianLeavingTheHouse(info.x, info.y);
				break;


			}

		}

	}
}



void ModuleEnemiesFront::OnCollision(Collider* c1, Collider* c2)
{
	if (App->player->hit == true){
		App->player->hit = false;
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
			{
				hits++;
				enemies[i]->OnCollision(c1, c2);
				//delete enemies[i];
				//enemies[i] = nullptr;
				break;
			}
		}
	}
}