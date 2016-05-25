#include "Application.h"
#include "Charriot.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"

Enemy_Charriot::Enemy_Charriot(int x, int y) : Enemy(x, y)
{
	//Chariot - facing left
	
	left.PushBack({ 234, 52, 35, 33 });
	left.PushBack({ 270, 52, 35, 33 });
	left.PushBack({ 306, 52, 35, 33 });
	left.PushBack({ 342, 52, 35, 33 });
	left.speed = 0.1f;
	left.loop = true;
	//open cannon

	shot.PushBack({ 235, 83, 35, 32 });
	shot.PushBack({ 270, 83, 35, 32 });
	shot.PushBack({ 306, 83, 35, 32 });
	shot.PushBack({ 342, 83, 35, 32 });
	
	//aiming

	shot.PushBack({ 235, 116, 35, 32 });
	shot.PushBack({ 270, 116, 35, 32 });
	shot.PushBack({ 306, 116, 35, 32 });
	shot.PushBack({ 342, 116, 35, 32 });
	shot.PushBack({ 306, 323, 35, 32 });
	shot.PushBack({ 270, 323, 35, 32 });
	shot.PushBack({ 235, 323, 35, 32 });
	shot.PushBack({ 342, 290, 35, 32 });
	shot.PushBack({ 306, 290, 35, 32 });
	shot.PushBack({ 270, 290, 35, 32 });
	shot.PushBack({ 235, 290, 35, 32 });

	/*shot.PushBack({ 235, 157, 35, 32 });
	shot.PushBack({ 270, 157, 35, 32 });
	shot.PushBack({ 306, 157, 35, 32 });*/
	shot.loop = true;
	shot.speed = 0.1f;
	//Chariot - facing rigth
	
	right.PushBack({ 235, 259, 35, 32 });
	right.PushBack({ 270, 259, 35, 32 });
	right.PushBack({ 306, 259, 35, 32 });
	right.PushBack({ 342, 259, 35, 32 });
	right.speed = 0.1f;
	right.loop = true;

	collider = App->collision->AddCollider({ 0, 0, 35, 33 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	path.PushBack({ -0.4f, 0.0f }, 300, &left);
	path.PushBack({ 0.0f, 0.0f }, 150, &shot);
	path.PushBack({ 0.4f, 0.0f }, 300, &right);
	
	original_pos.y = y;
	original_pos.x = x;
}

void Enemy_Charriot::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	/*if (path.GetFrame() == 375 && isdead == false){
		App->particles->AddParticle(App->particles->gunflare, position.x+17, position.y);
		//if (App->particles->gunflare.anim.Finished()){
		App->particles->AddParticle(App->particles->Cowboyshot, position.x+17, position.y, COLLIDER_ENEMY, 0);
		//}
	}*/
	if (isdead == true) {
		to_delete = true;

	}
}
void Enemy_Charriot::OnCollision(Collider* c1, Collider* c2)
{
	isdead = true;
}