#include "Application.h"
#include "BlueCowBoy.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "ModuleParticles.h"


BlueCowboy::BlueCowboy(int x, int y) : Enemy(x, y)
{
	left.PushBack({ 501, 0, 16, 16 });
	left.PushBack({ 518, 0, 16, 16 });
	left.PushBack({ 535, 0, 16, 16 });
	left.PushBack({ 518, 0, 16, 16 });
	left.PushBack({ 552, 0, 16, 16 });
	left.PushBack({ 569, 0, 16, 16 });
	left.PushBack({ 586, 0, 16, 16 });
	left.PushBack({ 603, 0, 16, 16 });//idle	
	left.speed = 0.09f;

	shot.PushBack({ 620, 0, 16, 16 });
	shot.PushBack({ 637, 0, 16, 16 });
	shot.PushBack({ 654, 0, 16, 16 });
	shot.speed = 0.09f;


	right.PushBack({ 501, 17, 16, 16 });
	right.PushBack({ 518, 17, 16, 16 });
	right.PushBack({ 535, 17, 16, 16 });
	right.PushBack({ 552, 17, 16, 16 });
	right.PushBack({ 569, 17, 16, 16 });
	right.PushBack({ 586, 17, 16, 16 });

	right.speed = 0.09f;

	dead.PushBack({ 603, 17, 16, 16 });
	dead.PushBack({ 620, 17, 16, 16 });
	dead.PushBack({ 637, 17, 16, 16 });
	dead.PushBack({ 654, 17, 16, 16 });
	dead.PushBack({ 671, 17, 16, 16 });
	dead.PushBack({ 688, 17, 16, 16 });
	dead.speed = 0.09f;
	dead.loop = false;

	


	collider = App->collision->AddCollider({ 0, 0, 10, 12 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	path.PushBack({ 0.3f, 0.0f }, 150, &left);
	path.PushBack({ 0.0f, 0.0f }, 75, &shot);
	path.PushBack({ -0.3f, 0.0f }, 150, &right);

}

void BlueCowboy::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	if (path.GetFrame() == 200 && isdead == false){
		//if (App->particles->gunflare.anim.Finished()){
		App->particles->AddParticle(App->particles->orangebomb, position.x, position.y, 1, -1, COLLIDER_BOMB, 0);
		//}
	}
	if (isdead == true && dead.Finished() == true) {
		to_delete = true;
	}

}
void BlueCowboy::OnCollision(Collider* c1, Collider* c2)
{
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 25, &dead);
	path.loop = false;

	isdead = true;
}