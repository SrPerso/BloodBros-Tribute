#include "Application.h"
#include "PurplePlane.h"
#include "ModuleCollision.h"
#include "Path.h"
#include "Enemy.h"
PurplePlane::PurplePlane(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 118, 361, 113, 47 });
	fly.PushBack({ 118, 310, 113, 47 });
	fly.PushBack({ 118, 259, 113, 47 });
	fly.PushBack({ 118, 208, 113, 47 });
	fly.speed = 0.05f;
	fly.loop = false;
	fly2.PushBack({ 118, 157, 113, 47 });
	fly2.PushBack({ 118, 106, 113, 47 });
	fly2.PushBack({ 118, 55, 113, 47 });
	fly2.PushBack({ 118, 3, 113, 47 });
	fly2.speed = 0.05f;
	fly2.loop = false;
	
	

	collider = App->collision->AddCollider({x , y, 113, 47 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	path.PushBack({ 0.0f, 0.3f }, 50, &fly);	
	path.PushBack({ 0.0f, -0.5f }, 50, &fly2);
	
	
	
}

void PurplePlane::Move()
{
	
	
	position = original_pos + path.GetCurrentSpeed(&animation);
	
}
void PurplePlane::OnCollision(Collider* c1, Collider* c2)
{
	
}