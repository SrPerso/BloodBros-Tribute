#include "Application.h"
#include "Jumper2.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "ModuleParticles.h"
#include <time.h>
#include <stdlib.h>

Jumper2::Jumper2(int x, int y) : Enemy(x, y)
{

	left.PushBack({ 738, 38, 32, 32 });//1
	left.PushBack({ 738, 71, 32, 32 });//2
	left.PushBack({ 738, 104, 32, 32 });//3
	left.PushBack({ 738, 137, 32, 32 });//4
	left.PushBack({ 738, 170, 32, 32 });//5
	left.PushBack({ 738, 203, 32, 32 });//6//moviendose izquierda
	left.speed = 0.2f;


	right.PushBack({ 771, 38, 32, 32 });//1
	right.PushBack({ 771, 71, 32, 32 });//2
	right.PushBack({ 771, 104, 32, 32 });//3
	right.PushBack({ 771, 137, 32, 32 });//4
	right.PushBack({ 771, 170, 32, 32 });//5
	right.PushBack({ 771, 203, 32, 32 });//6//moviendose a la derecha
	right.speed = 0.2f;

	shotidle.PushBack({ 738, 302, 32, 32 });//sin disparar
	shot.PushBack({ 771, 302, 32, 32 });// disparando
	shot.speed = 0.14f;



	jump.PushBack({ 683, 208, 16, 48 });//crouch


	dead.PushBack({ 804, 38, 32, 32 });//1
	dead.PushBack({ 804, 71, 32, 32 });//2
	dead.PushBack({ 804, 104, 32, 32 });//3
	dead.PushBack({ 804, 137, 32, 32 });//4
	dead.speed = 0.16f;
	dead.loop = false;

	collider = App->collision->AddCollider({ 5, 15, 30, 40 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	path.PushBack({ 0.0f, -1.2f }, 60, &jump);
	path.PushBack({ 0.0f, 1.2f }, 78, &jump);
	path.PushBack({ 0.0f, 0.0f }, 55, &shotidle);
	path.PushBack({ 1.0f, 0.0f }, 50, &right);



	srand(time(NULL));
}

void Jumper2::Move()
{


	position = original_pos + path.GetCurrentSpeed(&animation);
	if (path.GetFrame() == 200 && isdead == false){


		//if (App->particles->gunflare.anim.Finished()){
		//App->particles->AddParticle(App->particles->orangebomb, position.x, position.y, -(rand() % 3), rand() % 3 + 1, COLLIDER_BOMB, 0);
		//}
		//}
	}
	if (path.GetFrame() == 243 || isdead == true && dead.Finished() == true) {
		to_delete = true;
	}

}
void Jumper2::OnCollision(Collider* c1, Collider* c2)
{
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 80, &dead);
	path.loop = false;
	collider->to_delete = true;
	collider = nullptr;
	isdead = true;
}