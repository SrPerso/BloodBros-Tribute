#include "Application.h"
#include "PurplePlane.h"
#include "ModuleCollision.h"

PurplePlane::PurplePlane(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 118, 361, 113, 47 });
	fly.PushBack({ 118, 310, 113, 47 });
	fly.PushBack({ 118, 259, 113, 47 });
	fly.PushBack({ 118, 208, 113, 47 });
	fly.PushBack({ 118, 157, 113, 47 });
	fly.PushBack({ 118, 106, 113, 47 });
	fly.PushBack({ 118, 55, 113, 47 });
	fly.PushBack({ 118, 3, 113, 47 });
	fly.speed = 0.05f;

	fly.loop = false;
	animation = &fly;
	

	collider = App->collision->AddCollider({position.x,position.y--, 70, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void PurplePlane::Move()
{
	if (fly.Finished()&& this !=nullptr){
		delete[]this;
		
	}
}
