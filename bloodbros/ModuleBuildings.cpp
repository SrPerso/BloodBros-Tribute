#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModulePlayer.h"
#include"Animation.h"
#include "Extras.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
#include "Audio.h"
#include "ModuleBuildings.h"

#include "SDL/include/SDL_timer.h"

ModuleBuilding::ModuleBuilding()
{
	for (uint i = 0; i < MAX_BUILDINGS; ++i)
		active[i] = nullptr;
}

ModuleBuilding::~ModuleBuilding()
{
	if (yellow.collider != nullptr){
		App->collision->EraseCollider(yellow.collider);
	}
}

// Load assets
bool ModuleBuilding::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Images/buildings.png");


	yellow.build.x = 1;
	yellow.build.y = 2;
	yellow.build.w = 94;
	yellow.build.h = 95;
	yellow.mytype = YELLOW;

	yellow2.build.x = 104;
	yellow2.build.y = 2;
	yellow2.build.w = 94;
	yellow2.build.h = 95;

	yellow.destroy.PushBack({ 105, 2, 94, 96 });
	yellow.destroy.PushBack({ 104, 2, 94, 82 });
	yellow.destroy.PushBack({ 105, 2, 94, 70 });
	yellow.destroy.PushBack({ 104, 2, 94, 56 });
	yellow.destroy.PushBack({ 105, 2, 94, 44 });
	yellow.destroy.PushBack({ 104, 2, 94, 30 });
	yellow.destroy.PushBack({ 105, 2, 94, 18 });
	yellow.destroy.PushBack({ 104, 2, 94, 4 });
	yellow.destroy.loop = false;
	yellow.destroy.speed = 0.05f;

	purple.build.x = 1;
	purple.build.y = 217;
	purple.build.w = 80;
	purple.build.h = 54;
	purple.mytype = PURPLE;

	purple2.build.x = 104;
	purple2.build.y = 217;
	purple2.build.w = 80;
	purple2.build.h = 54;

	purple.destroy.PushBack({ 104, 217, 80, 54 });
	purple.destroy.PushBack({ 104, 217, 80, 49 });
	purple.destroy.PushBack({ 104, 217, 80, 44 });
	purple.destroy.PushBack({ 104, 217, 80, 39 });
	purple.destroy.PushBack({ 104, 217, 80, 34 });
	purple.destroy.PushBack({ 104, 217, 80, 29 });
	purple.destroy.PushBack({ 104, 217, 80, 24 });
	purple.destroy.PushBack({ 104, 217, 80, 19 });
	purple.destroy.PushBack({ 104, 217, 80, 14 });
	purple.destroy.PushBack({ 104, 217, 80, 9 });
	purple.destroy.PushBack({ 104, 217, 80, 4 });
	purple.destroy.loop = false;
	purple.destroy.speed = 0.12f;
	
	/*wheel.build.x = 0;
	wheel.build.y = 107;
	wheel.build.w = 46;
	wheel.build.h = 49;*/

	mill.build.x = 1;
	mill.build.y = 156;
	mill.build.w = 43;
	mill.build.h = 49;

	mill.movement.PushBack({ 1, 106, 43, 49 });
	mill.movement.PushBack({ 53, 106, 43, 49 });
	mill.movement.PushBack({ 105, 106, 43, 49 });
	mill.movement.PushBack({ 157, 106, 43, 49 });
	mill.movement.loop = true;
	mill.movement.speed = 0.12f;


	mill.destroy.PushBack({ 157, 156, 43, 49 });
	mill.destroy.PushBack({ 157, 156, 43, 44 });
	mill.destroy.PushBack({ 157, 156, 43, 39 });
	mill.destroy.PushBack({ 157, 156, 43, 34 });
	mill.destroy.PushBack({ 157, 156, 43, 29 });
	mill.destroy.PushBack({ 157, 156, 43, 24 });
	mill.destroy.PushBack({ 157, 156, 43, 19 });
	mill.destroy.PushBack({ 157, 156, 43, 14 });
	mill.destroy.PushBack({ 157, 156, 43, 9 });
	mill.destroy.PushBack({ 157, 156, 43, 4 });
	mill.destroy.loop = false;
	mill.destroy.speed = 0.12f;
	mill.mytype = WINDMILL;


	trees.build.x = 1;
	trees.build.y = 280;
	trees.build.w = 49;
	trees.build.h = 49;

	trees.movement.PushBack({ 1, 280, 49, 49 });
	trees.movement.PushBack({ 50, 280, 49, 49 });
	trees.movement.PushBack({ 1, 280, 49, 49 });
	trees.movement.PushBack({ 50, 280, 49, 49 });
	trees.movement.loop = true;
	trees.movement.speed = 0.2f;
	trees.mytype = TREES;

	return true;
}

// Unload assets
bool ModuleBuilding::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_BUILDINGS; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}
	last_building = 0;
	return true;
}

// Update: draw background
update_status ModuleBuilding::Update()
{
	
	for (uint i = 0; i < MAX_BUILDINGS; ++i)
	{
		Building* p = active[i];

		if (p == nullptr)
			continue;
		if (p->Update() == false)
		{
			p->collider->to_delete = true;
			delete p;
			active[i] = nullptr;

		}
		else if ((p->hits <= 1 && p->mytype != WINDMILL || (p->mytype == WINDMILL && p->hits <= 2)) || (p->mytype == TREES && p->hits==0))
		{
			if (p->mytype == WINDMILL){
				App->render->Blit(graphics, p->position.x, p->position.y - 48, &p->movement.GetCurrentFrame());
			}
			App->render->Blit(graphics, p->position.x, p->position.y, &p->build, 0);
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
		else if (p->mytype == TREES && p->hits >= 1){
			App->render->Blit(graphics, p->position.x, p->position.y, &p->movement.GetCurrentFrame());
			if (p->movement.Finished() == true){
				LOG("NOW 0");
				p->hits = 0;
				p->movement.Reset();
				p->movement.loops = 0;
			}
		}
		else if (p->hits > 1 && p->mytype != WINDMILL && p->mytype!=TREES){

			App->render->Blit(graphics, p->position.x, p->position.y += 0.6f, &p->destroy.GetCurrentFrame());

			/*p->collider->to_delete = true;
			delete p;*/
			if (p->destroy.Finished()){
				if (p->mytype == PURPLE){ purplealive = false; }
				if (p->mytype == YELLOW){ yellowalive = false; }
				delete p;
				active[i] = nullptr;
			}
		}
		else if (p->hits > 2 && p->mytype == WINDMILL){
			App->render->Blit(graphics, p->position.x, (p->position.y += 0.4f) - 48, &p->movement.GetCurrentFrame());
			App->render->Blit(graphics, p->position.x, p->position.y += 0.4f, &p->destroy.GetCurrentFrame());
			if (p->destroy.Finished()){
				if (p->mytype == WINDMILL){ windmillalive = false; }
				delete p;
				active[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleBuilding::AddBuilding(const Building& particle, int x, int y)
{
	Building* p = new Building(particle);
	p->position.x = x;
	p->position.y = y;
	if (p->mytype == PURPLE){ purplealive = true; }
	if (p->mytype == YELLOW){ yellowalive = true; }
	if (p->mytype == WINDMILL){ windmillalive = true; }
	if (p->mytype == WHEEL){
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, particle.build.w, particle.build.h }, COLLIDER_NONE, this);
	}
	else{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, particle.build.w, particle.build.h }, COLLIDER_EXTRA, this);
	}
	active[last_building++] = p;
}

const Collider* Building::get_collider() const
{
	return collider;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Building::Building()
{
	position.SetToZero();
}

Building::Building(const Building& p) :
build(p.build), position(p.position),
fx(p.fx), mytype(p.mytype), destroy(p.destroy), movement(p.movement)
{}

Building::~Building(){
	if (collider != nullptr){
		App->collision->EraseCollider(collider);
	}
}

bool Building::Update()
{
	bool ret = true;

	return ret;
}
void ModuleBuilding::OnCollision(Collider* c1, Collider* c2)
{
	if (App->player->hit == true){
		App->player->hit = false;
		for (uint i = 0; i < MAX_BUILDINGS; ++i){
			if (active[i] != nullptr && active[i]->get_collider() == c1 && active[i]->mytype == TREES){
				active[i]->hits += 1;
				break;
			}
			if (active[i] != nullptr && active[i]->get_collider() == c1 && active[i]->mytype == YELLOW){
				if (active[i]->hits == 0){
					active[i]->build.x = yellow2.build.x;
					active[i]->build.y = yellow2.build.y;
					active[i]->build.w = yellow2.build.w;
					active[i]->build.h = yellow2.build.h;
					active[i]->hits++;
					break;
				}
				else if (active[i]->hits == 1){
					active[i]->build.x = 0;
					active[i]->build.y = 0;
					active[i]->build.w = 0;
					active[i]->build.h = 0;
					active[i]->hits++;
					App->particles->AddParticle(App->particles->bigsmoke, active[i]->position.x, active[i]->position.y + 85);
					App->extra->AddExtra(App->extra->guitar, active[i]->position.x + 24, active[i]->position.y + 50);
					/*delete[] active[i]->collider;
					active[i]->collider = nullptr;//PROBLEM*/
				}
			}
			if (active[i] != nullptr && active[i]->get_collider() == c1 && active[i]->mytype == PURPLE){
				if (active[i]->hits == 0){
					active[i]->build.x = purple2.build.x;
					active[i]->build.y = purple2.build.y;
					active[i]->build.w = purple2.build.w;
					active[i]->build.h = purple2.build.h;
					active[i]->hits++;
					break;
				}
				else if (active[i]->hits == 1){
					active[i]->build.x = 0;
					active[i]->build.y = 0;
					active[i]->build.w = 0;
					active[i]->build.h = 0;
					active[i]->hits++;
					App->particles->AddParticle(App->particles->housesmoke, active[i]->position.x, active[i]->position.y + 44);
					App->extra->AddExtra(App->extra->shower, active[i]->position.x + 15, active[i]->position.y + 14);
				}
			}
			if (active[i] != nullptr && active[i]->get_collider() == c1 && active[i]->mytype == WINDMILL){
				if (active[i]->hits == 0){
					active[i]->build.x = 53;
					active[i]->build.y = 156;
					active[i]->build.w = 43;
					active[i]->build.h = 49;
					active[i]->hits++;
					break;
				}
				else if (active[i]->hits == 1){
					active[i]->build.x = 105;
					active[i]->build.y = 156;
					active[i]->build.w = 43;
					active[i]->build.h = 49;
					active[i]->hits++;
					break;
				}
				else if (active[i]->hits == 2){
					active[i]->build.x = 157;
					active[i]->build.y = 156;
					active[i]->build.w = 43;
					active[i]->build.h = 49;
					active[i]->hits++;
					App->particles->AddParticle(App->particles->housesmoke, active[i]->position.x - 5, active[i]->position.y + 44);
				}
			}
		}
	}
}