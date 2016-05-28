#include "Application.h"
#include "PurplePlane.h"
#include "ModuleCollision.h"
#include "Path.h"
#include "Enemy.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "Audio.h"

PurplePlane::PurplePlane(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 118, 361, 113, 47 });
	fly.PushBack({ 118, 310, 113, 47 });
	fly.PushBack({ 118, 259, 113, 47 });
	fly.PushBack({ 118, 208, 113, 47 });
	fly.speed = 0.03f;
	fly.loop = false;
	fly2.PushBack({ 118, 157, 113, 47 });
	fly2.PushBack({ 118, 106, 113, 47 });
	fly2.PushBack({ 118, 55, 113, 47 });
	fly2.PushBack({ 118, 3, 113, 47 });
	fly2.speed = 0.1f;
	fly2.loop = false;
	
	

	collider = App->collision->AddCollider({x , y, 113, 47 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	path.PushBack({ 0.0f, 0.2f }, 100, &fly);	
	path.PushBack({ 0.0f, -0.8f }, 120, &fly2);
	path.loop = false;
	
	
}

void PurplePlane::Move()
{
	if (path.GetFrame() == 180){
		to_delete = true;
	}
	if (path.GetFrame() == 110 ){
		App->particles->AddParticle(App->particles->gunflare, position.x, position.y);
		//if (App->particles->gunflare.anim.Finished()){
		App->audio->Loadfx("Music/planebomb.ogg");
		App->particles->AddParticle(App->particles->Planebomb, position.x+50, position.y+46, 0.0f, +1.3f, COLLIDER_BOMB, 0);
		App->particles->AddParticle(App->particles->Planebomb, position.x + 12, position.y + 46, -0.15f, +1.3f, COLLIDER_BOMB, 0);
		App->particles->AddParticle(App->particles->Planebomb, position.x + 88, position.y + 46, 0.15f, +1.3f, COLLIDER_BOMB, 0);

		//}
	}
	position = original_pos + path.GetCurrentSpeed(&animation);


	
}
void PurplePlane::OnCollision(Collider* c1, Collider* c2)
{
	App->particles->AddParticle(App->particles->points5000, position.x, position.y, 0.0f, +1.3f, COLLIDER_POINT, 0);
	to_delete = true;
}