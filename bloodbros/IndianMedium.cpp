#include "Application.h"
#include "IndianMedium.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "ModuleParticles.h"


IndianMedium::IndianMedium(int x, int y) : Enemy(x, y)
{

	fly.PushBack({ 666, 175, 32, 32 });//1
	fly.PushBack({ 699, 175, 32, 32 });//2
	fly.PushBack({ 534, 208, 32, 32 });//3
	fly.PushBack({ 567, 208, 32, 32 });//4
	fly.PushBack({ 600, 208, 32, 32 });//5
	fly.PushBack({ 633, 208, 32, 32 });//6//moviendose izquierda
	fly.speed = 0.2f;


	idle.PushBack({ 567, 142, 32, 32 });//idle


	fly2.PushBack({ 534, 109, 32, 32 });//1
	fly2.PushBack({ 567, 109, 32, 32 });//2
	fly2.PushBack({ 600, 109, 32, 32 });//3
	fly2.PushBack({ 633, 109, 32, 32 });//4
	fly2.PushBack({ 666, 109, 32, 32 });//5
	fly2.PushBack({ 699, 109, 32, 32 });//6/moviendose a la derecha
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
	path.PushBack({ 0.8f, 0.0f }, 50, &fly);
	path.PushBack({ 0.0f, 0.0f }, 40, &idle);
	path.PushBack({ -0.8f, 0.0f }, 150, &fly2);

}

void IndianMedium::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	if (path.GetFrame() == 80 && isdead == false){
		App->particles->AddParticle(App->particles->gunflare, position.x, position.y + 10);
		//if (App->particles->gunflare.anim.Finished()){
		App->particles->AddParticle(App->particles->Cowboyshot, position.x, position.y + 10, COLLIDER_ENEMY, 0);
		//}
	}
	if (path.GetFrame() == 230 || isdead == true && dead.Finished() == true) {
		to_delete = true;
	}

}
void IndianMedium::OnCollision(Collider* c1, Collider* c2)
{
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 25, &dead);
	path.loop = false;
	collider->to_delete = true;
	collider = nullptr;
	isdead = true;
}