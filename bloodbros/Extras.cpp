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
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleExtra::ModuleExtra()
{
	for (uint i = 0; i < MAX_EXTRAS; ++i)
		active[i] = nullptr;
}

ModuleExtra::~ModuleExtra()
{
}

// Load assets
bool ModuleExtra::Start()
{
	LOG("Loading extras");
	graphics = App->textures->Load("Images/Extra1.png");



	pig.anim.PushBack({ 0, 9, 32, 23 });
	pig.anim.PushBack({ 35, 9, 32, 23 });
	pig.anim.loop = true;
	pig.anim.speed = 0.2f;
	pig.speed.x = -1;
	pig.type = PIG;
	pig.life = 4000;

	zepe.anim.PushBack({ 235, 20, 97, 49 });
	zepe.anim.loop = true;
	zepe.hit.PushBack({ 340, 20, 97, 49 });
	zepe.hit.loop = true;
	zepe.speed.x = -0.5;
	zepe.life = 10000;
	zepe.type = ZEPE;

	//WOMAN ANIM
	shower.type = WOMEN;
	shower.anim.PushBack({ 3, 226, 31, 29 });//1
	shower.anim.PushBack({ 35, 226, 31, 29 });//2
	shower.anim.PushBack({ 67, 226, 31, 29 });//3
	shower.anim.PushBack({ 99, 226, 31, 29 });//4
	shower.anim.PushBack({ 3, 226, 31, 29 });//1
	shower.anim.PushBack({ 35, 226, 31, 29 });//2
	shower.anim.PushBack({ 67, 226, 31, 29 });//3
	shower.anim.PushBack({ 99, 226, 31, 29 });//4
	shower.anim.PushBack({ 3, 226, 31, 29 });//1
	shower.anim.PushBack({ 35, 226, 31, 29 });//2
	shower.anim.PushBack({ 67, 226, 31, 29 });//3
	shower.anim.PushBack({ 99, 226, 31, 29 });//4
	shower.anim.PushBack({ 131, 226, 31, 29 });//5
	shower.anim.PushBack({ 163, 226, 31, 29 });//6
	shower.anim.PushBack({ 195, 226, 31, 29 });//7
	shower.anim.PushBack({ 227, 226, 31, 29 });//8
	shower.anim.PushBack({ 259, 226, 31, 29 });//9
	shower.anim.PushBack({ 195, 226, 31, 29 });//7
	shower.anim.PushBack({ 227, 226, 31, 29 });//8
	shower.anim.PushBack({ 259, 226, 31, 29 });//9
	shower.anim.loop = false;
	shower.anim.speed = 0.08f;
	shower.life = 4000;
	shower.type = WOMEN;

	//GUITAR ANIM
	guitar.anim.PushBack({ 298, 224, 32, 32 });//1
	guitar.anim.PushBack({ 331, 224, 32, 32 });//2
	guitar.anim.PushBack({ 298, 224, 32, 32 });//1
	guitar.anim.PushBack({ 331, 224, 32, 32 });//2
	guitar.anim.PushBack({ 298, 224, 32, 32 });//1
	guitar.anim.PushBack({ 331, 224, 32, 32 });//2
	guitar.anim.PushBack({ 298, 224, 32, 32 });//1
	guitar.anim.PushBack({ 331, 224, 32, 32 });//2
	guitar.anim.PushBack({ 298, 224, 32, 32 });//1
	guitar.anim.PushBack({ 331, 224, 32, 32 });//2
	guitar.anim.PushBack({ 364, 224, 32, 32 });//3
	guitar.anim.PushBack({ 331, 224, 32, 32 });//2
	guitar.anim.PushBack({ 364, 224, 32, 32 });//3
	guitar.anim.PushBack({ 331, 224, 32, 32 });//2
	guitar.anim.PushBack({ 364, 224, 32, 32 });//3
	guitar.anim.PushBack({ 397, 224, 32, 32 });//4
	guitar.anim.loop = false;
	guitar.anim.speed = 0.08f;
	guitar.life = 4000;
	guitar.type = GUITAR;


	return true;
}

// Unload assets
bool ModuleExtra::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	
	for (uint i = 0; i < MAX_EXTRAS; ++i)
	{
		if (active[i] != nullptr)
		{
		
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleExtra::Update()
{

	for (uint i = 0; i < MAX_EXTRAS; ++i)
	{
		Extra* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			p->collider->to_delete = true;
			delete p;
			active[i] = nullptr;
		
		}
		else if (SDL_GetTicks() >= p->born)
		{
			if (p->type == PIG)
				App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			else if (p->type == ZEPE)
				App->render->Blit(graphics, p->position.x, p->position.y, &p->anim.GetCurrentFrame());
			else if (p->type == GUITAR){
				App->render->Blit(graphics, p->position.x, p->position.y, &p->anim.GetCurrentFrame());
			}
			else if (p->type == WOMEN){
				App->render->Blit(graphics, p->position.x, p->position.y, &p->anim.GetCurrentFrame());
			}
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleExtra::AddExtra(const Extra& particle, int x, int y, Uint32 delay)
{
	Extra* p = new Extra(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
	if (p->type == PIG){
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y + 1, 30, 19 }, COLLIDER_EXTRA, this);
	}
	if (p->type == ZEPE){
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 97, 40}, COLLIDER_EXTRA, this);
	}
	if (p->type == GUITAR){
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 31, 25 }, COLLIDER_NONE, this);
	}
	if (p->type == WOMEN){
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 31, 25 }, COLLIDER_NONE, this);
	}
	active[last_particle++] = p;
}

const Collider* Extra::get_collider() const
{
	return collider;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Extra::Extra()
{
	position.SetToZero();
	speed.SetToZero();
}

Extra::Extra(const Extra& p) :
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life), type(p.type)
{}

Extra::~Extra(){
	if (collider != nullptr){
		App->collision->EraseCollider(collider);
	}
}

bool Extra::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
	if (anim.Finished())
		
		ret = false;


	position.x += speed.x;
	position.y += speed.y;


	if (collider != nullptr){
		collider->rect.x = position.x;
		collider->rect.y = position.y;
	}

	if (position.x == 90 && type == ZEPE){
		speed.x = 0;
		speed.y = -0.5;
	}
	
	return ret;
}
void ModuleExtra::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_EXTRAS; ++i){
		if (active[i] != nullptr && active[i]->get_collider() == c1 && active[i]->type==PIG){
				App->audio->Loadfx("Music/pig.ogg");
				active[i]->speed.x--;
				break;
		}
		if (active[i] != nullptr && active[i]->get_collider() == c1 && active[i]->type == ZEPE){
			App->render->Blit(graphics, active[i]->position.x, active[i]->position.y, &active[i]->hit.frames[0]);
			
		}
		
	}
}