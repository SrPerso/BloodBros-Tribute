#include "Application.h"
#include "GreenRight.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "ModuleParticles.h"
#include <time.h>
#include <stdlib.h>


GreenRightCowboy::GreenRightCowboy(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 251, 24, 16, 20 });
	fly.PushBack({ 268, 24, 16, 20 });
	fly.PushBack({ 285, 24, 16, 20 });
	fly.PushBack({ 302, 24, 16, 20 });
	fly.PushBack({ 319, 24, 16, 20 });
	fly.PushBack({ 336, 24, 16, 20 });//moviendose a la derecha
	fly.speed = 0.2f;

	idle.PushBack({ 353, 3, 16, 20 });//idle


	fly2.PushBack({ 336, 3, 16, 20 });
	fly2.PushBack({ 319, 3, 16, 20 });
	fly2.PushBack({ 302, 3, 16, 20 });
	fly2.PushBack({ 285, 3, 16, 20 });
	fly2.PushBack({ 268, 3, 16, 20 });
	fly2.PushBack({ 251, 3, 16, 20 });//moviendose izquierda
	fly2.speed = 0.2f;

	dead.PushBack({ 387, 3, 16, 20 });
	dead.PushBack({ 404, 3, 16, 20 });
	dead.PushBack({ 421, 3, 16, 20 });
	dead.PushBack({ 438, 3, 16, 20 });
	dead.speed = 0.12f;
	dead.loop = false;


	collider = App->collision->AddCollider({ 0, 0, 16, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	path.PushBack({ -0.8f, 0.0f }, 30, &fly2);
	path.PushBack({ 0.0f, 0.0f }, 20, &idle);
	path.PushBack({ 0.8f, 0.0f }, 30, &fly);
	path.PushBack({ -0.8f, 0.0f }, 30, &fly2);
	path.PushBack({ 0.0f, 0.0f }, 20, &idle);
	path.PushBack({ -0.8f, 0.0f }, 30, &fly2);
	path.PushBack({ 0.0f, 0.0f }, 20, &idle);
	path.PushBack({ 0.8f, 0.0f }, 30, &fly);
	path.PushBack({ 0.0f, 0.0f }, 20, &idle);
	path.PushBack({ 0.8f, 0.0f }, 30, &fly);
	srand(time(NULL));
}

void GreenRightCowboy::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	if (path.GetFrame() == 200 && isdead == false){
		App->particles->AddParticle(App->particles->gunflare, position.x, position.y);
		//if (App->particles->gunflare.anim.Finished()){
		App->particles->AddParticle(App->particles->Cowboyshot, position.x, position.y,  -(rand()%3), rand()%3+1, COLLIDER_ENEMY, 0);
		//}
	}
	if (isdead == true && dead.Finished() == true) {
		to_delete = true;
	}

}
void GreenRightCowboy::OnCollision(Collider* c1, Collider* c2)
{
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 25, &dead);
	path.loop = false;

	isdead = true;
}