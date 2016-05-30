#include "Application.h"
#include "Jumpershoot.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "ModuleParticles.h"
#include <time.h>
#include <stdlib.h>

Jumpershoot::Jumpershoot(int x, int y) : Enemy(x, y)
{
	left.PushBack({ 528, 347, 32, 48 });// 1
	left.PushBack({ 561, 347, 32, 48 });//2
	left.PushBack({ 594, 347, 32, 48 });//3
	left.PushBack({ 627, 347, 32, 48 });//4
	left.PushBack({ 660, 347, 32, 48 });//5
	left.PushBack({ 693, 347, 32, 48 });//6
	left.speed = 0.2f;

	right.PushBack({ 528, 395, 32, 48 });// 1
	right.PushBack({ 561, 395, 32, 48 });//2
	right.PushBack({ 594, 395, 32, 48 });//3
	right.PushBack({ 627, 395, 32, 48 });//4
	right.PushBack({ 660, 39532, 48 });//5
	right.PushBack({ 693, 395, 32, 48 });//6
	right.speed = 0.2f;

	shotidle.PushBack({ 726, 347, 32, 48 });//sin disparar
	shot.PushBack({ 759, 347, 32, 48 });//disparando
	shot.speed = 0.14f;

	jump.PushBack({ 830, 357, 32, 26 });//crouch
	jump.PushBack({ 792, 347, 32, 48 });//en vuelo
	jump.loop = false;
	jump.speed = 0.1f;

	dead.PushBack({ 841, 127, 32, 48 });//1
	dead.PushBack({ 841, 186, 32, 48 });//2
	dead.PushBack({ 841, 235, 32, 48 });//3
	dead.PushBack({ 841, 284, 32, 48 });//4	
	dead.speed = 0.16f;
	dead.loop = false;

	collider = App->collision->AddCollider({ 5, 15, 30, 40 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	path.PushBack({ 0.0f, -2.0f }, 25, &jump);
	path.PushBack({ 0.0f, -1.5f }, 15, &jump);
	path.PushBack({ 0.0f, -1.0f }, 10, &jump);
	path.PushBack({ 0.0f, -0.5f }, 5, &jump);
	path.PushBack({ 0.0f, 0.5f }, 5, &jump);
	path.PushBack({ 0.0f, 1.0f }, 10, &jump);
	path.PushBack({ 0.0f, 1.5f }, 15, &jump);
	path.PushBack({ 0.0f, 2.0f }, 30, &jump);
	path.PushBack({ 0.0f, 0.0f }, 25, &shotidle);
	path.PushBack({ 0.0f, 0.0f }, 20, &shot);
	path.PushBack({ 0.0f, 0.0f }, 20, &shotidle);
	path.PushBack({ -1.0f, 0.0f }, 90, &left);



	srand(time(NULL));
}

void Jumpershoot::Move()
{


	position = original_pos + path.GetCurrentSpeed(&animation);
	if (path.GetFrame() == 200 && isdead == false){

		App->particles->AddParticle(App->particles->gunflare, position.x, position.y + 10);
		App->particles->AddParticle(App->particles->Cowboyshot, position.x, position.y + 10, COLLIDER_ENEMY, 0);

		//if (App->particles->gunflare.anim.Finished()){
		//App->particles->AddParticle(App->particles->orangebomb, position.x, position.y, -(rand() % 3), rand() % 3 + 1, COLLIDER_BOMB, 0);
		//}
		//}
	}
	if (isdead == true && dead.Finished() == true) {
		to_delete = true;
	}

}
void Jumpershoot::OnCollision(Collider* c1, Collider* c2)
{
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 80, &dead);
	path.loop = false;
	collider->to_delete = true;
	collider = nullptr;
	isdead = true;
}