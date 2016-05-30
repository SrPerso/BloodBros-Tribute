#include "Application.h"
#include "GreenCowBoyLeavingTheHouse.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "ModuleParticles.h"


GreenCowBoyLeavingTheHouse::GreenCowBoyLeavingTheHouse(int x, int y) : Enemy(x, y)
{

	appear.PushBack({ 804, 269, 32, 32 });//1
	appear.PushBack({ 804, 236, 32, 32 });//2
	appear.PushBack({ 804, 203, 32, 32 });//3
	appear.PushBack({ 804, 170, 32, 32 });//4
	appear.loop = false;
	appear.speed = 0.1f;


	fly.PushBack({ 771, 38, 32, 32 });//1
	fly.PushBack({ 771, 71, 32, 32 });//2
	fly.PushBack({ 771, 104, 32, 32 });//3
	fly.PushBack({ 771, 137, 32, 32 });//4
	fly.PushBack({ 771, 170, 32, 32 });//5
	fly.PushBack({ 771, 203, 32, 32 });//6//moviendose a la derecha
	fly.speed = 0.2f;

	jump.PushBack({ 836, 38, 32, 32 });//jump

	idle.PushBack({ 738, 302, 32, 32 }); //idle


	fly2.PushBack({ 738, 38, 32, 32 });//1
	fly2.PushBack({ 738, 71, 32, 32 });//2
	fly2.PushBack({ 738, 104, 32, 32 });//3
	fly2.PushBack({ 738,137, 32, 32 });//4
	fly2.PushBack({ 738, 170, 32, 32 });//5
	fly2.PushBack({ 738, 203, 32, 32 });//6
	fly2.speed = 0.2f;


	dead.PushBack({ 804, 38, 32, 32 });//1
	dead.PushBack({ 804, 71, 32, 32 });//2
	dead.PushBack({ 804, 104, 32, 32 });//3
	dead.PushBack({ 804, 137, 32, 32 });//4
	dead.speed = 0.12f;
	dead.loop = false;


	collider = App->collision->AddCollider({ 0, 0, 16, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->front);

	original_pos.x = x;
	original_pos.y = y;
	path.PushBack({ 0.0f, 0.0f }, 30, &appear);
	path.PushBack({ -0.8f, 0.0f }, 10, &fly2);
	path.PushBack({ 0.0f, 0.0f },30, &idle);
	path.PushBack({ 0.0f, 0.8f }, 20, &jump);
	path.PushBack({ 0.0f, 0.0f }, 40, &idle);
	path.PushBack({ 0.8f, 0.0f },80, &fly);

}

void GreenCowBoyLeavingTheHouse::Move()
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
void GreenCowBoyLeavingTheHouse::OnCollision(Collider* c1, Collider* c2)
{
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 25, &dead);
	path.loop = false;
	collider->to_delete = true;
	collider = nullptr;
	isdead = true;
}