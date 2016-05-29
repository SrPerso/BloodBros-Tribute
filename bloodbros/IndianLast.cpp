#include "Application.h"
#include "IndianLast.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "ModuleParticles.h"
#include <time.h>
#include <stdlib.h>


IndianLast::IndianLast(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 534, 313, 16, 32 });//1
	fly.PushBack({ 551, 313, 16, 32 });//2
	fly.PushBack({ 568, 313, 16, 32 });//3
	fly.PushBack({ 585, 313, 16, 32 });//4
	fly.PushBack({ 602, 313, 16, 32 });//5
	fly.PushBack({ 619, 313, 16, 32 });//5
	//moviendose a la derecha
	fly.speed = 0.2f;

	idle.PushBack({ 636, 280, 16, 32 });//idle


	fly2.PushBack({ 534, 280, 16, 32 });//1
	fly2.PushBack({ 551, 280, 16, 32 });//2
	fly2.PushBack({ 568, 280, 16, 32 });//3
	fly2.PushBack({ 585, 280, 16, 32 });//4
	fly2.PushBack({ 602, 280, 16, 32 });//5
	fly2.PushBack({ 619, 280, 16, 32 });//5//moviendose izquierda
	fly2.speed = 0.2f;

	dead.PushBack({ 653, 280, 16, 32 });//1
	dead.PushBack({ 670, 280, 16, 32 });//2
	dead.PushBack({ 687, 280, 16, 32 });//3
	dead.PushBack({ 704, 280, 16, 32 });//4
	dead.speed = 0.12f;
	dead.loop = false;


	collider = App->collision->AddCollider({ 0, 0, 16, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	path.PushBack({ 0.8f, 0.0f }, 30, &fly);
	path.PushBack({ 0.0f, 0.0f }, 20, &idle);
	path.PushBack({ 0.8f, 0.0f }, 30, &fly);
	path.PushBack({ 0.8f, 0.0f }, 30, &fly);
	path.PushBack({ 0.0f, 0.0f }, 20, &idle);
	path.PushBack({ 0.8f, 0.0f }, 30, &fly);
	path.PushBack({ 0.0f, 0.0f }, 20, &idle);
	path.PushBack({ 0.8f, 0.0f }, 30, &fly);
	path.PushBack({ 0.0f, 0.0f }, 20, &idle);
	path.PushBack({ 0.8f, 0.0f }, 30, &fly);
	srand(time(NULL));
}

void IndianLast::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	if (path.GetFrame() == 200 && isdead == false){
		App->particles->AddParticle(App->particles->gunflare, position.x, position.y);
		//if (App->particles->gunflare.anim.Finished()){
		App->particles->AddParticle(App->particles->Cowboyshot, position.x, position.y, -(rand() % 3), rand() % 3 + 1, COLLIDER_ENEMY, 0);
		//}
	}
	if (isdead == true && dead.Finished() == true) {
		to_delete = true;
	}

}
void IndianLast::OnCollision(Collider* c1, Collider* c2)
{
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 25, &dead);
	path.loop = false;

	isdead = true;
}