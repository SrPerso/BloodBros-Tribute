#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
enum COLLIDER_TYPE;
enum PARTICLE_TYPE{bomb,planebomb,};

struct Particle
{
	Animation anim;
	Collider* collider=nullptr;
	bool collides = false;
	uint fx = 0;
	iPoint position;
	fPoint speed;
	PARTICLE_TYPE type;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	~Particle();
	Particle(const Particle& p);
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, Uint32 delay = 0);
	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay);
	void AddParticle(const Particle& particle, int x, int y, float speedx, float speedy, COLLIDER_TYPE collider_type, Uint32 delay);
	void OnCollision(Collider* c1, Collider* c2);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:

	Particle Scope;
	Particle housesmoke;
	Particle Cowboyshot;
	Particle gunflare;
	Particle Planebomb;
	Particle Hitbomb;
};

#endif // __MODULEPARTICLES_H__