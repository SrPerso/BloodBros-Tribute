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
	zepe.nothit.x = 235;
	zepe.nothit.y = 20;
	zepe.nothit.w = 97;
	zepe.nothit.h = 49;
	zepe.hit.x = 340;
	zepe.hit.y = 17;
	zepe.hit.w = 96;
	zepe.hit.h = 48;
	zepe.speed.x = -1;
	zepe.life = 4000;
	zepe.type = ZEPE;

	



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
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
			if (active[i]->type == ZEPE){
				App->render->Blit(graphics, p->position.x, p->position.y, &p->anim.GetCurrentFrame());
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
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 97, 49}, COLLIDER_EXTRA, this);
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

	if (position.x == 100 && type == ZEPE){
		speed.x = 0;
		speed.y = -1;
	}
	if (collider != nullptr){
		collider->rect.x += speed.x;
		collider->rect.y += speed.y;
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
			App->render->Blit(graphics, active[i]->position.x, active[i]->position.y, &active[i]->hit);
		}
	}
}