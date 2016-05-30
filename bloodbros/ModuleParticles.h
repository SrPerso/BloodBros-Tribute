#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleScope.h"

#define MAX_ACTIVE_PARTICLES 1000

struct SDL_Texture;
enum COLLIDER_TYPE;
enum PARTICLE_TYPE{bomb,planebomb, ORANGE, TNT, POINTS, SHOTGUN, TNTAMMO,ROCKPIECES,BIGEXPLOSION};

struct Particle
{
	Animation anim;
	Collider* collider=nullptr;
	bool collides = false;
	uint fx = 0;
	fPoint position;
	fPoint originalpos;
	fPoint speed;
	PARTICLE_TYPE type;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	uint points = 0;
	Particle();
	~Particle();
	Particle(const Particle& p);
	bool Update();
	ModuleScope* scope;
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
	Particle bigsmoke;
	Particle Cowboyshot;
	Particle gunflare;
	Particle Planebomb;
	Particle Hitbomb;
	Particle orangebomb;
	Particle tnt;
	Particle tntammo;
	Particle points1000;
	Particle points2000;
	Particle points5000;
	Particle points7000;
	Particle points10000;
	Particle points20000;
	Particle points50000;
	Particle points70000;
	Particle shotgun;
	Particle rockpieces;
	Particle bigexplosion;
};

#endif // __MODULEPARTICLES_H__