#include "Application.h"
#include "IndianLeavingTheHouse.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "ModuleParticles.h"


IndianLeavingTheHouse::IndianLeavingTheHouse(int x, int y) : Enemy(x, y)
{

	appear.PushBack({ 534, 241, 32, 32 });//4
	appear.PushBack({ 567, 24132, 32 });//3
	appear.PushBack({ 600, 241, 32, 32 });//2
	appear.PushBack({ 633, 241, 32, 32 });//1
	appear.loop = false;
	appear.speed = 0.2f;


	fly.PushBack({ 666, 175, 32, 32 });//1
	fly.PushBack({ 699, 175, 32, 32 });//2
	fly.PushBack({ 534, 208, 32, 32 });//3
	fly.PushBack({ 567, 208, 32, 32 });//4
	fly.PushBack({ 600, 208, 32, 32 });//5
	fly.PushBack({ 633, 208, 32, 32 });//6//moviendose a la derecha
	fly.speed = 0.2f;

	jump.PushBack({ 666, 208, 16, 48 });//1

	idle.PushBack({ 567, 142, 32, 32 });//sin disparar


	fly2.PushBack({ 534, 109, 32, 32 });//1
	fly2.PushBack({ 567, 109, 32, 32 });//2
	fly2.PushBack({ 600, 109, 32, 32 });//3
	fly2.PushBack({ 633, 109, 32, 32 });//4
	fly2.PushBack({ 666, 109, 32, 32 });//5
	fly2.PushBack({ 699, 109, 32, 32 });//6//IZQUIERDA
	fly2.speed = 0.2f;


	dead.PushBack({ 600, 142, 32, 32 });//1
	dead.PushBack({ 633, 142, 32, 32 });//2
	dead.PushBack({ 666, 142, 32, 32 });//3
	dead.PushBack({ 699, 142, 32, 32 });//4

	dead.speed = 0.12f;
	dead.loop = false;


	collider = App->collision->AddCollider({ 0, 0, 16, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->front);

	original_pos.x = x;
	original_pos.y = y;
	path.PushBack({ 0.0f, 0.0f }, 30, &appear);
	path.PushBack({ -0.8f, 0.0f }, 10, &fly2);
	path.PushBack({ 0.0f, 0.0f }, 30, &idle);
	path.PushBack({ 0.0f, 0.8f }, 20, &jump);
	path.PushBack({ 0.0f, 0.0f }, 40, &idle);
	path.PushBack({ 0.8f, 0.0f }, 80, &fly);

}

void IndianLeavingTheHouse::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	if (path.GetFrame() == 80 && isdead == false){
		//App->particles->AddParticle(App->particles->gunflare, position.x, position.y + 10);
		//if (App->particles->gunflare.anim.Finished()){
		//App->particles->AddParticle(App->particles->Cowboyshot, position.x, position.y + 10, COLLIDER_ENEMY, 0);
		//}
	}
	if (path.GetFrame() == 190 || isdead == true && dead.Finished() == true) {
		to_delete = true;
	}

}
void IndianLeavingTheHouse::OnCollision(Collider* c1, Collider* c2)
{
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 25, &dead);
	path.loop = false;

	isdead = true;
}