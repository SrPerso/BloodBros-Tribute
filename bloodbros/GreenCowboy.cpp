#include "Application.h"
#include "GreenCowBoy.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "ModuleParticles.h"


GreenCowboy::GreenCowboy(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 251, 24, 16, 20 });
	fly.PushBack({ 268, 24, 16, 20 });
	fly.PushBack({ 285, 24, 16, 20 });
	fly.PushBack({ 302, 24, 16, 20 });
	fly.PushBack({ 319, 24, 16, 20 });
	fly.PushBack({ 336, 24, 16, 20 });
	fly.PushBack({ 353, 24, 16, 20 });//moviendose a la derecha
	fly.speed = 0.09f;

	idle.PushBack({ 370, 3, 16, 20 });
	fly2.PushBack({ 353, 3, 16, 20 });
	fly2.PushBack({ 336, 3, 16, 20 });
	fly2.PushBack({ 319, 3, 16, 20 });
	fly2.PushBack({ 302, 3, 16, 20 });
	fly2.PushBack({ 285, 3, 16, 20 });
	fly2.PushBack({ 268, 3, 16, 20 });
	fly2.PushBack({ 251, 3, 16, 20 });//moviendose izquierda
	fly2.speed = 0.09f;

	dead.PushBack({ 387, 3, 16, 20 });
	dead.PushBack({ 404, 3, 16, 20 });
	dead.PushBack({ 421, 3, 16, 20 });
	dead.PushBack({ 438, 3, 16, 20 });
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
	if (path.GetFrame()==200 && isdead==false){
		App->particles->AddParticle(App->particles->gunflare, position.x, position.y);
		//if (App->particles->gunflare.anim.Finished()){
			App->particles->AddParticle(App->particles->Cowboyshot, position.x, position.y, COLLIDER_ENEMY, 0);
		//}
	}
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