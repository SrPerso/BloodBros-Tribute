#include "Application.h"
#include "GreenCowBoy.h"
#include "ModuleCollision.h"
#include "Enemy.h"


GreenCowboy::GreenCowboy(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 237, 26, 10, 21 });
	fly.PushBack({ 251, 26, 13, 21 });
	fly.PushBack({ 266, 26, 16, 21 });
	fly.PushBack({ 285, 26, 10, 21 });
	fly.PushBack({ 301, 26, 11, 21 });
	fly.PushBack({ 315, 26, 15, 21 });
	fly.PushBack({ 331, 26, 13, 21 });//moviendose a la derecha
	fly.speed = 0.09f;

	idle.PushBack({ 347, 3, 13, 21 });
	fly2.PushBack({ 331, 3, 13, 21 });
	fly2.PushBack({ 315, 3, 15, 21 });
	fly2.PushBack({ 301, 3, 11, 21 });
	fly2.PushBack({ 285, 3, 10, 21 });
	fly2.PushBack({ 266, 3, 16, 21 });
	fly2.PushBack({ 251, 3, 13, 21 });
	fly2.PushBack({ 237, 3, 10, 21 });//moviendose izquierda
	fly2.speed = 0.09f;

	dead.PushBack({ 362, 3, 15, 21 });
	dead.PushBack({ 380, 3, 11, 21 });
	dead.PushBack({ 393, 3, 17, 21 });
	dead.PushBack({ 410, 3, 17, 21 });
	dead.speed = 0.09f;
	dead.loop = false;
	

	collider = App->collision->AddCollider({ 0, 0, 16, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	path.PushBack({ 0.3f, 0.0f }, 150, &fly);
	path.PushBack({ 0.0f, 0.0f }, 75, &idle);
	path.PushBack({ -0.3f, 0.0f }, 150, &fly2);
	
}

void GreenCowboy::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	if (isdead == true && dead.Finished()==true) {
		to_delete = true;
	}

}
void GreenCowboy::OnCollision(Collider* c1, Collider* c2)
{
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 25, &dead);
	path.loop = false;
	
	isdead = true;
}