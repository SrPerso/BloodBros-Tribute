#include "Application.h"
#include "FarIndian2.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "ModuleParticles.h"


FarIndian2::FarIndian2(int x, int y) : Enemy(x, y)
{

	fly.PushBack({ 534, 73, 16, 16 });//1
	fly.PushBack({ 551, 73, 16, 16 });//2
	fly.PushBack({ 568, 73, 16, 16 });//3
	fly.PushBack({ 585, 73, 16, 16 });//4
	fly.PushBack({ 602, 73, 16, 16 });//5
	fly.PushBack({ 619, 73, 16, 16 });//5//moviendose izquierda
	fly.speed = 0.1f;


	idle.PushBack({ 636, 73, 16, 16 });//iddle


	fly2.PushBack({ 534, 90, 16, 16 });//1
	fly2.PushBack({ 551, 90, 16, 16 });//2
	fly2.PushBack({ 568, 90, 16, 16 });//3
	fly2.PushBack({ 585, 90, 16, 16 });//4
	fly2.PushBack({ 602, 90, 16, 16 });//5
	fly2.PushBack({ 619, 90, 16, 16 });//5/moviendose a la derecha
	fly2.speed = 0.1f;


	dead.PushBack({ 670, 73, 16, 16 });//1
	dead.PushBack({ 687, 73, 16, 16 });//2
	dead.PushBack({ 704, 73, 16, 16 });//3
	dead.PushBack({ 721, 73, 16, 16 });//4
	dead.speed = 0.12f;
	dead.loop = false;


	collider = App->collision->AddCollider({ 0, 0, 16, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->mid);

	original_pos.x = x;
	original_pos.y = y;
	path.PushBack({ 0.6f, 0.0f }, 110, &fly2);
	path.PushBack({ 0.0f, 0.0f }, 30, &idle);
	path.PushBack({ 0.6f, 0.0f }, 40, &fly2);
	path.PushBack({ 0.0f, 0.0f }, 30, &idle);
	path.PushBack({ 0.6f, 0.0f }, 40, &fly2);
	path.PushBack({ 0.0f, 0.0f }, 30, &idle);
	path.PushBack({ 0.6f, 0.0f }, 40, &fly2);
	path.PushBack({ 0.0f, 0.0f }, 30, &idle);
	path.PushBack({ 0.6f, 0.0f }, 180, &fly2);



}

void FarIndian2::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	if (path.GetFrame() == 80 && isdead == false){

	}
	if (path.GetFrame() == 530 || isdead == true && dead.Finished() == true) {
		to_delete = true;
	}

}
void FarIndian2::OnCollision(Collider* c1, Collider* c2)
{
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 25, &dead);
	path.loop = false;
	collider->to_delete = true;
	collider = nullptr;
	isdead = true;
}