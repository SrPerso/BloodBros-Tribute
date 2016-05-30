#include "Application.h"
#include "FarGreenCowBoy2.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "ModuleParticles.h"


FarGreenCowBoy2::FarGreenCowBoy2(int x, int y) : Enemy(x, y)
{

	fly.PushBack({ 534, 38, 16, 16 });//1
	fly.PushBack({ 551, 38, 16, 16 });//2
	fly.PushBack({ 568, 38, 16, 16 });//3
	fly.PushBack({ 585, 38, 16, 16 });//4
	fly.PushBack({ 602, 38, 16, 16 });//5
	fly.PushBack({ 619, 38, 16, 16 });//5moviendose izquierda
	fly.speed = 0.1f;


	idle.PushBack({ 636, 38, 16, 16 });//iddle


	fly2.PushBack({ 534, 55, 16, 16 });//1
	fly2.PushBack({ 551, 55, 16, 16 });//2
	fly2.PushBack({ 568, 55, 16, 16 });//3
	fly2.PushBack({ 585, 55, 16, 16 });//4
	fly2.PushBack({ 602, 55, 16, 16 });//5
	fly2.PushBack({ 619, 55, 16, 16 });//5/moviendose a la derecha
	fly2.speed = 0.1f;


	dead.PushBack({ 670, 38, 16, 16 });//1
	dead.PushBack({ 687, 38, 16, 16 });//2
	dead.PushBack({ 704, 38, 16, 16 });//3
	dead.PushBack({ 721, 38, 16, 16 });//4
	dead.speed = 0.12f;
	dead.loop = false;


	collider = App->collision->AddCollider({ 0, 0, 16, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->front);

	original_pos.x = x;
	original_pos.y = y;
	path.PushBack({ 0.6f, 0.0f }, 130, &fly2);
	path.PushBack({ 0.0f, 0.0f }, 30, &idle);
	path.PushBack({ 0.6f, 0.0f }, 40, &fly2);
	path.PushBack({ 0.0f, 0.0f }, 30, &idle);
	path.PushBack({ 0.6f, 0.0f }, 40, &fly2);
	path.PushBack({ 0.0f, 0.0f }, 30, &idle);
	path.PushBack({ 0.6f, 0.0f }, 190, &fly2);



}

void FarGreenCowBoy2::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	if (path.GetFrame() == 140 && isdead == false){
		App->particles->AddParticle(App->particles->gunflare, position.x, position.y);
		//if (App->particles->gunflare.anim.Finished()){
		App->particles->AddParticle(App->particles->Cowboyshot, position.x, position.y, COLLIDER_ENEMY, 0);
		//}
	}
	if (path.GetFrame() == 530 || isdead == true && dead.Finished() == true) {
		to_delete = true;
	}

}
void FarGreenCowBoy2::OnCollision(Collider* c1, Collider* c2)
{
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 25, &dead);
	path.loop = false;
	collider->to_delete = true;
	collider = nullptr;
	isdead = true;
}