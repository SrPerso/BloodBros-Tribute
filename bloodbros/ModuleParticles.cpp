#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleScope.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	Scope.anim.PushBack({ 209, 278, 11, 7 });
	Scope.anim.PushBack({ 226, 278, 11, 9 });
	Scope.anim.loop = true;
	Scope.anim.speed = 0.3f;
	Scope.speed.y = -3;
	Scope.life = 2000;


	housesmoke.anim.PushBack({ 3, 263, 80, 32 });//1
	housesmoke.anim.PushBack({ 85, 263, 80, 32 });//2
	housesmoke.anim.PushBack({ 170, 263, 80, 32 });//3
	housesmoke.anim.PushBack({ 254, 263, 80, 32 });//4
	housesmoke.anim.PushBack({ 338, 263, 80, 32 });//5
	housesmoke.anim.PushBack({ 422, 263, 80, 32 });//6
	housesmoke.anim.PushBack({ 254, 263, 80, 32 });//4
	housesmoke.anim.PushBack({ 338, 263, 80, 32 });//5
	housesmoke.anim.PushBack({ 422, 263, 80, 32 });//6
	housesmoke.anim.PushBack({ 254, 263, 80, 32 });//4
	housesmoke.anim.PushBack({ 338, 263, 80, 32 });//5
	housesmoke.anim.PushBack({ 422, 263, 80, 32 });//6
	housesmoke.anim.PushBack({ 254, 263, 80, 32 });//4
	housesmoke.anim.PushBack({ 338, 263, 80, 32 });//5
	housesmoke.anim.PushBack({ 422, 263, 80, 32 });//6
	housesmoke.anim.PushBack({ 254, 263, 80, 32 });//4
	housesmoke.anim.PushBack({ 338, 263, 80, 32 });//5
	housesmoke.anim.PushBack({ 422, 263, 80, 32 });//6
	housesmoke.anim.PushBack({ 254, 263, 80, 32 });//4
	housesmoke.anim.PushBack({ 338, 263, 80, 32 });//5
	housesmoke.anim.PushBack({ 422, 263, 80, 32 });//6
	housesmoke.anim.PushBack({ 254, 263, 80, 32 });//4
	housesmoke.anim.PushBack({ 338, 263, 80, 32 });//5
	housesmoke.anim.PushBack({ 422, 263, 80, 32 });//6
	housesmoke.anim.PushBack({ 254, 263, 80, 32 });//4
	housesmoke.anim.PushBack({ 338, 263, 80, 32 });//5
	housesmoke.anim.PushBack({ 422, 263, 80, 32 });//6
	housesmoke.anim.PushBack({ 254, 263, 80, 32 });//4
	housesmoke.anim.PushBack({ 338, 263, 80, 32 });//5
	housesmoke.anim.PushBack({ 422, 263, 80, 32 });//6
	housesmoke.anim.PushBack({ 254, 263, 80, 32 });//4
	housesmoke.anim.PushBack({ 338, 263, 80, 32 });//5
	housesmoke.anim.PushBack({ 422, 263, 80, 32 });//6
	housesmoke.anim.PushBack({ 170, 263, 80, 32 });//3
	housesmoke.anim.PushBack({ 85, 263, 80, 32 });//2
	housesmoke.anim.PushBack({ 3, 263, 80, 32 });//1
	housesmoke.anim.speed = 0.2f;
	housesmoke.anim.loop = false;
	housesmoke.life = 3000;
	
	
	bigsmoke.anim.PushBack({ 2, 299, 92, 40 });//1
	bigsmoke.anim.PushBack({ 98, 299, 92, 40 });//2
	bigsmoke.anim.PushBack({ 194, 299, 92, 40 });//3
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 290, 299, 92, 40 });//4
	bigsmoke.anim.PushBack({ 386, 299, 92, 40 });//5
	bigsmoke.anim.PushBack({ 482, 299, 92, 40 });//6
	bigsmoke.anim.PushBack({ 194, 299, 92, 40 });//3
	bigsmoke.anim.PushBack({ 98, 299, 92, 40 });//2
	bigsmoke.anim.PushBack({ 2, 299, 92, 40 });//1
	bigsmoke.anim.speed = 0.2f;
	bigsmoke.anim.loop = false;
	bigsmoke.life = 5700;


	Cowboyshot.anim.PushBack({ 213, 9, 7, 7 });
	Cowboyshot.anim.PushBack({ 230, 9, 7, 7 });
	Cowboyshot.anim.loop = true;
	Cowboyshot.anim.speed = 0.1f;
	Cowboyshot.speed.x = 1;
	Cowboyshot.speed.y = 1;
	Cowboyshot.collides = true;
	Cowboyshot.life = 3000;

	gunflare.anim.PushBack({ 150, 4, 16, 17 });
	gunflare.anim.PushBack({ 171, 4, 16, 17 });
	gunflare.anim.PushBack({ 190, 4, 16, 17 });
	gunflare.anim.speed = 0.3f;

	

	Planebomb.anim.PushBack({286, 6, 16, 16});
	Planebomb.anim.PushBack({ 303, 6, 16, 16 });
	Planebomb.anim.PushBack({ 320, 6, 16, 16 });
	Planebomb.anim.PushBack({ 337, 6, 16, 16 });
	Planebomb.anim.PushBack({ 354, 6, 16, 16 });
	Planebomb.anim.speed = 0.15f;
	Planebomb.anim.loop = false;
	Planebomb.life = 3000;
	Planebomb.type = planebomb;

	Hitbomb.anim.PushBack({ 5, 29, 33, 58 });
	Hitbomb.anim.PushBack({ 39, 29, 33, 58 });
	Hitbomb.anim.PushBack({ 73, 29, 33, 58 });
	Hitbomb.anim.PushBack({ 107, 29, 33, 58 });
	Hitbomb.anim.PushBack({ 141, 29, 33, 58 });
	Hitbomb.anim.PushBack({ 175, 29, 33, 58 });
	Hitbomb.anim.PushBack({ 209, 29, 33, 58 });
	Hitbomb.anim.PushBack({ 243, 29, 33, 58 });
	Hitbomb.anim.speed = 0.25f;
	Hitbomb.anim.loop = false;
	Hitbomb.life = 400;

	orangebomb.anim.PushBack({ 493, 229, 15, 15 });
	orangebomb.anim.PushBack({ 476, 229, 15, 15 });
	orangebomb.anim.PushBack({ 459, 229, 15, 15 });
	orangebomb.anim.PushBack({ 374, 229, 15, 15 });
	orangebomb.anim.PushBack({ 391, 229, 15, 15 });
	orangebomb.anim.PushBack({ 408, 229, 15, 15 });
	orangebomb.anim.PushBack({ 425, 229, 15, 15 });
	orangebomb.anim.PushBack({ 442, 229, 15, 15 });
	orangebomb.anim.PushBack({ 459, 229, 15, 15 });
	orangebomb.anim.PushBack({ 476, 229, 15, 15 });
	orangebomb.anim.PushBack({ 493, 229, 15, 15 });
	orangebomb.anim.speed = 0.06f;
	orangebomb.type = ORANGE;
	orangebomb.anim.loop = false;
	orangebomb.life = 5000;

	tnt.anim.PushBack({ 374, 212, 15, 15 });
	tnt.anim.PushBack({ 391, 212, 15, 15 });
	tnt.anim.PushBack({ 408, 212, 15, 15 });
	tnt.anim.PushBack({ 425, 212, 15, 15 });
	tnt.anim.PushBack({ 442, 212, 15, 15 });
	tnt.anim.PushBack({ 459, 212, 15, 15 });
	tnt.anim.PushBack({ 476, 212, 15, 15 });
	tnt.anim.PushBack({ 493, 212, 15, 15 });
	tnt.anim.speed = 0.1f;
	tnt.anim.loop = false;
	tnt.type = TNT;

	points1000.anim.PushBack({ 283, 35, 20, 12 });
	points1000.anim.PushBack({ 305, 35, 20, 12 });
	points1000.anim.loop = true;
	points1000.anim.speed = 0.3f;
	points1000.type = POINTS;
	points1000.life = 5000;
	points1000.points = 1000;

	points5000.anim.PushBack({ 327, 34, 26, 14 });
	points5000.anim.PushBack({ 355, 34, 26, 14 });
	points5000.anim.loop = true;
	points5000.anim.speed = 0.3f;
	points5000.type = POINTS;
	points5000.points = 5000;
	points5000.life = 5000;

	points7000.anim.PushBack({ 383, 34, 26, 14 });
	points7000.anim.PushBack({ 411, 34, 26, 14 });
	points7000.anim.loop = true;
	points7000.anim.speed = 0.3f;
	points7000.type = POINTS;
	points7000.points = 7000;
	points7000.life = 5000;

	points10000.anim.PushBack({ 283, 51, 39, 16 });
	points10000.anim.PushBack({ 323, 51, 39, 16 });
	points10000.anim.loop = true;
	points10000.anim.speed = 0.3f;
	points10000.type = POINTS;
	points10000.points = 10000;
	points10000.life = 5000;

	points20000.anim.PushBack({ 364, 51, 40, 16 });
	points20000.anim.PushBack({ 406, 51, 40, 16 });
	points20000.anim.loop = true;
	points20000.anim.speed = 0.3f;
	points20000.type = POINTS;
	points20000.points = 20000;
	points20000.life = 5000;

	points50000.anim.PushBack({ 283, 70, 40, 16 });
	points50000.anim.PushBack({ 325, 70, 40, 16 });
	points50000.anim.loop = true;
	points50000.anim.speed = 0.3f;
	points50000.type = POINTS;
	points50000.points = 50000;
	points50000.life = 5000;

	points70000.anim.PushBack({ 368, 70, 43, 16 });
	points70000.anim.PushBack({ 413, 70, 43, 16 });
	points70000.anim.loop = true;
	points70000.anim.speed = 0.3f;
	points70000.type = POINTS;
	points70000.points = 70000;
	points70000.life = 5000;

	shotgun.anim.PushBack({ 407, 93, 32, 16 });
	shotgun.anim.PushBack({ 441, 93, 32, 16 });
	shotgun.anim.loop = true;
	shotgun.anim.speed = 0.3f;
	shotgun.life = 5000;
	shotgun.type = SHOTGUN;

}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Images/Particles.png");
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
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
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active[last_particle++] = p;
}
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
	p->originalpos.x = x;
	p->originalpos.y = y;
	if (p->type == TNT){
		p->speed = p->position.GetSpeed(App->scope->position);
	}
	if (collider_type != COLLIDER_NONE)
		p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
	active[last_particle++] = p;

}
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, float speedx, float speedy, COLLIDER_TYPE collider_type, Uint32 delay)
{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->originalpos.x = x;
			p->originalpos.y = y;
			p->speed.x = speedx;
			p->speed.y = speedy;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[last_particle++] = p;
	
}


void ModuleParticles::OnCollision(Collider* c1, Collider* c2){
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];
		if (active[i] != nullptr && active[i]->collider== c1 && active[i]->collider->type==COLLIDER_BOMB && c2->type==COLLIDER_WALL){
			active[i]->anim.Reset();
			App->particles->AddParticle(App->particles->Hitbomb, active[i]->position.x, active[i]->position.y-45, 0.0f, +0.0f, COLLIDER_ENEMY, 0);
			delete p;
			active[i] = nullptr;
			break;
		}
		else if (active[i] != nullptr && active[i]->collider == c1 && active[i]->collider->type == COLLIDER_POINT && c2->type == COLLIDER_PLAYER){
			App->player->score += active[i]->points;
			delete p;
			active[i] = nullptr;
			break;
		}
		else if (active[i] != nullptr && active[i]->collider == c1 && active[i]->collider->type == COLLIDER_POINT && c2->type == COLLIDER_WALL){
			active[i]->speed.y = 0;
			break;
		}
		else if (active[i] != nullptr && active[i]->collider == c1 && active[i]->collider->type == COLLIDER_POWERUP && c2->type == COLLIDER_PLAYER){
			App->scope->shotgun = true;
			delete p;
			active[i] = nullptr;
			break;
		}
		else if (active[i] != nullptr && active[i]->collider == c1 && active[i]->type==SHOTGUN && c2->type == COLLIDER_WALL){
			active[i]->speed.y = 0;
			break;
		}
		// Always destroy particles that collide
		else if (active[i] != nullptr && active[i]->collider == c1 && active[i]->type!=planebomb)
		{
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete p;
			active[i] = nullptr;
			break;
		}
		
	}
}
// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life), type(p.type), points(p.points)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

bool Particle::Update()
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

	if (type == ORANGE && position.y==25){
		speed.y = 1;
		speed.x = 0.5;
	}

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

