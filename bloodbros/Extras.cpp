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

#include "SDL/include/SDL_timer.h"

ModuleExtra::ModuleExtra()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleExtra::~ModuleExtra()
{}

// Load assets
bool ModuleExtra::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("level12.png");



	pig.anim.PushBack({ 258, 149, 34, 22 });
	pig.anim.PushBack({ 293, 149, 34, 22 });
	pig.anim.loop = true;
	pig.anim.speed = 0.2f;
	pig.speed.x = -1;
	pig.life = 4000;

	

	



	return true;
}

// Unload assets
bool ModuleExtra::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
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

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
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
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
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
	p->collider =App->collision->AddCollider({ p->position.x, p->position.y+1, 30, 19 }, COLLIDER_EXTRA);
	active[last_particle++] = p;
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
fx(p.fx), born(p.born), life(p.life)
{}

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
	collider->rect.x += speed.x;
	collider->rect.y += speed.y;
	
	return ret;
}