#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemiesMid.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"

#include "ModulePlayer.h"

#include "GreenCowBoyMedium.h"
#include "IndianMedium.h"
#include "Jumper2.h"
#include "jumper2left.h"
#include "FarIndian.h"
#include "FarIndian2.h"
#include "FarGreenCowboy.h"
#include "FarGreenCowboy2.h"

#define SPAWN_MARGIN 50

ModuleEnemiesMid::ModuleEnemiesMid()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;

}

// Destructor
ModuleEnemiesMid::~ModuleEnemiesMid()
{
}

bool ModuleEnemiesMid::Start()
{

	sprites = App->textures->Load("Images/Enemies.png");



	return true;
}

update_status ModuleEnemiesMid::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES3::NO_TYPE3)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES3::NO_TYPE3;
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
update_status ModuleEnemiesMid::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemiesMid::PostUpdate()
{


	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemiesMid::CleanUp()
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

bool ModuleEnemiesMid::AddEnemy(ENEMY_TYPES3 type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES3::NO_TYPE3)
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

void ModuleEnemiesMid::SpawnEnemy(const EnemyInfo3& info)
{

	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i); {

		if (i != MAX_ENEMIES)
		{
			switch (info.type)
			{

			case ENEMY_TYPES3::GREENCOWBOYMEDIUM:
				enemies[i] = new GreenCowboyMedium(info.x, info.y);
				break;
			case ENEMY_TYPES3::INDIANMEDIUM:
				enemies[i] = new IndianMedium(info.x, info.y);
				break;
			case ENEMY_TYPES3::GREENCOWBOYJUMPERRIGTH:
				enemies[i] = new Jumper2(info.x, info.y);
				break;
			case ENEMY_TYPES3::GREENCOWBOYJUMPERLEFT:
				enemies[i] = new Jumper2left(info.x, info.y);
				break;
			case ENEMY_TYPES3::FARINDIAN:
				enemies[i] = new FarIndian(info.x, info.y);
				break;
			case ENEMY_TYPES3::FARINDIAN2:
				enemies[i] = new FarIndian2(info.x, info.y);
				break;
			case ENEMY_TYPES3::FARGREEN:
				enemies[i] = new FarGreenCowBoy(info.x, info.y);
				break;
			case ENEMY_TYPES3::FARGREEN2:
				enemies[i] = new FarGreenCowBoy2(info.x, info.y);
				break;
				
		}

		}

	}
}



void ModuleEnemiesMid::OnCollision(Collider* c1, Collider* c2)
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