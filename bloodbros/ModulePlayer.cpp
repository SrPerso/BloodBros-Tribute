#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "Audio.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
#include "ModuleVictory.h"
#include "ModuleScope.h"


#include "SDL/include/SDL_timer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{

	graphics = NULL;
	current_animation = NULL;

	position.x = 105;
	position.y = 155;
	idle.PushBack({ 160, 0, 46, 70 });
	//cowboy animation
	right.PushBack({ 7, 195, 35, 64 });
	right.PushBack({ 48, 195, 33, 64 });
	right.PushBack({ 88, 195, 41, 64 });
	right.PushBack({ 139, 195, 32, 64 });
	right.PushBack({ 175, 195, 32, 64 });
	right.PushBack({ 218, 195, 40, 64 });
	right.loop = true;
	right.speed = 0.1f;

	//cowboy animation
	left.PushBack({ 3, 266, 40, 64 });
	left.PushBack({ 54, 266, 32, 64 });
	left.PushBack({ 90, 266, 32, 64 });
	left.PushBack({ 132, 266, 43, 64 });
	left.PushBack({ 180, 266, 33, 64 });
	left.PushBack({ 219, 266, 35, 64 });
	left.loop = true;
	left.speed = 0.1f;

	//cowboy animation
	jump_left.PushBack({ 707, 264, 33, 63 });
	jump_left.PushBack({ 628, 264, 65, 63 });
	jump_left.PushBack({ 585, 264, 39, 63 });
	jump_left.PushBack({ 533, 264, 44, 63 });
	jump_left.PushBack({ 499, 264, 33, 63 });
	jump_left.PushBack({ 445, 264, 49, 63 });
	jump_left.PushBack({ 397, 264, 46, 63 });
	jump_left.PushBack({ 363, 264, 33, 63 });

	jump_left.loop = true;
	jump_left.speed = 0.1f;

	//cowboy animation

	jump_right.PushBack({ 369, 197, 33, 63 });
	jump_right.PushBack({ 416, 197, 65, 63 });
	jump_right.PushBack({ 485, 197, 39, 63 });
	jump_right.PushBack({ 532, 197, 44, 63 });
	jump_right.PushBack({ 577, 197, 33, 63 });
	jump_right.PushBack({ 615, 197, 49, 63 });
	jump_right.PushBack({ 665, 197, 47, 63 });
	jump_right.PushBack({ 713, 197, 33, 63 });
	jump_right.loop = true;
	jump_right.speed = 0.1f;

	dead.PushBack({ 353, 709, 29, 53 });
	dead.PushBack({ 391, 709, 34, 53 });
	dead.PushBack({ 431, 709, 42, 53 });
	dead.PushBack({ 475, 709, 44, 53 });
	dead.PushBack({ 522, 709, 52, 53 });
	dead.PushBack({ 579, 709, 53, 53 });
	dead.loop = true;
	dead.speed = 0.1f;
	
	//shot idle
	shotidle.PushBack({ 15, 0, 46, 70 });//izquierda total
	shotidle.PushBack({ 63, 0, 46, 70 });//medio izc
	shotidle.PushBack({ 113, 0, 46, 70 });//casi centr
	shotidle.PushBack({ 201, 0, 46, 70 });//casi centr
	shotidle.PushBack({ 246, 0, 46, 70 });//medio derech
	shotidle.PushBack({ 287, 0, 46, 70 });//derech total
	shotidle.speed = 0.1f;
	//aiming left

	shotleft.PushBack({ 9, 71, 46, 71 });
	shotleft.PushBack({ 15, 0, 46, 70 });
	shotleft.PushBack({ 2, 340, 46, 71 });
	shotleft.PushBack({ 15, 0, 46, 70 });
	shotleft.speed = 0.1f;

	//aiming left top

	shotleftop.PushBack({ 63, 71, 46, 71 });
	shotleftop.PushBack({ 63, 0, 46, 70 });
	shotleftop.PushBack({ 55, 340, 46, 71 });
	shotleftop.PushBack({ 63, 0, 46, 70 });
	shotleftop.speed = 0.1f;
	//aiming top left

	shotopleft.PushBack({ 110, 71, 46, 71 });
	shotopleft.PushBack({ 113, 0, 46, 70 });
	shotopleft.PushBack({ 107, 340, 46, 71 });
	shotopleft.PushBack({ 113, 0, 46, 70 });
	shotopleft.speed = 0.1f;
	//aiming top

	shotop.PushBack({ 162, 71, 46, 71 });
	shotop.PushBack({ 160, 0, 46, 70 });
	shotop.PushBack({ 159, 340, 46, 71 });
	shotop.PushBack({ 160, 0, 46, 70 });
	shotop.speed = 0.1f;
	//aiming right

	shotright.PushBack({ 295, 71, 46, 71 });
	shotright.PushBack({ 287, 0, 46, 70 });
	shotright.PushBack({ 292, 340, 46, 71 });
	shotright.PushBack({ 287, 0, 46, 70 });
	shotright.speed = 0.1f;
	//aiming right top
	
	shotrighttop.PushBack({ 249, 71, 46, 71 });
	shotrighttop.PushBack({ 246, 0, 46, 70 });
	shotrighttop.PushBack({ 246, 340, 46, 71 });
	shotrighttop.PushBack({ 246, 0, 46, 70 });
	shotrighttop.speed = 0.1f;
	
	//aiming top right

	shotopright.PushBack({ 202, 71, 46, 71 });
	shotopright.PushBack({ 201, 0, 46, 70 });
	shotopright.PushBack({ 198, 340, 46, 71 });
	shotopright.PushBack({ 201, 0, 46, 70 });
	shotopright.speed = 0.1f;
	
	dance.PushBack({ 348, 500, 40, 75 });
	dance.PushBack({ 396, 500, 40, 75 });
	dance.PushBack({ 437, 500, 40, 75 });
	dance.PushBack({ 481, 511, 38, 64 });
	dance.PushBack({ 519, 511, 38, 64 });
	dance.PushBack({ 566, 529, 25, 43 });
	dance.PushBack({ 598, 529, 25, 43 });
	dance.PushBack({ 628, 533, 19, 30 });
	dance.PushBack({ 651, 533, 25, 43 });
	dance.PushBack({ 682, 538, 13, 19 }); 
	dance.PushBack({ 703, 538, 13, 19 });
	dance.PushBack({ 727, 548, 7, 10 });
	dance.PushBack({ 745, 548, 7, 10 });

	dance.loop = false;
	dance.speed = 0.1f;
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Images/Main_Characters.png"); // arcade version

	position.x = 105;
	position.y = 153;
	status = NORMAL;
	hp = 3;
	player = App->collision->AddCollider({ position.x+10, position.y+20, 12, 8}, COLLIDER_PLAYER, this);
	return ret;
}
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->collision->CleanUp(); 
	App->textures->Unload(graphics);
	status = NORMAL;
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	float speed = 1.4f;


	switch (status){
	case NORMAL:
	{
				   player->type = COLLIDER_PLAYER;
				   if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
				   {
					   if (position.x >= 220){
						   speed = 0;
					   }
					   position.x += speed;
					   if (current_animation!=&right && App->input->keyboard[SDL_SCANCODE_LALT] != KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_REPEAT)
					   {
						   right.Reset();
						   current_animation = &right;
					   }

					   else if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN)
					   {
						   jump_right.loops = 0;
						   jump_right.Reset();
						   current_animation = &jump_right;
						   status = ROLL;
					   }

					   else if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT)
					   {
						   position.x -= speed;
						   if ((App->scope->position.x - position.x)> 0  && (App->scope->position.x-position.x)<=38.6f){
							   current_animation = &shotopright;

						   }
						   else if ((App->scope->position.x - position.x)> 38.6f && (App->scope->position.x - position.x) <= 77.3f){
							   current_animation = &shotrighttop;
							  
						   }
						   else if ((App->scope->position.x - position.x)>77.3f){
							   current_animation = &shotright;
							   
						   }

						   
					   }
				   }
					   
				   else if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
				   {
					   
					   if (position.x <= 0){
						   speed = 0;
					   }
					   position.x -= speed;
					   if (current_animation != &left && App->input->keyboard[SDL_SCANCODE_LALT] != KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_REPEAT)
					   {
						   left.Reset();
						   current_animation = &left;
					   }
					   else if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						   jump_left.loops = 0;
						   jump_left.Reset();
						   current_animation = &jump_left;
						   status = ROLL;
					   }
					  
					   else if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT)
					   {
						   position.x += speed;
						   if ((position.x - App->scope->position.x)> 0 && (position.x - App->scope->position.x) <= 38.6f){
							   current_animation = &shotopleft;
						   }
						   else if ((position.x - App->scope->position.x)> 38.6f && (position.x - App->scope->position.x) <= 77.3f){
							   current_animation = &shotleftop;
						   }
						   else if ((position.x - App->scope->position.x)>77.3f){
							   current_animation = &shotleft;

						   }


					   }
				   }

				   else if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_RIGHT] != KEY_STATE::KEY_REPEAT  && App->input->keyboard[SDL_SCANCODE_LEFT] != KEY_STATE::KEY_REPEAT ){

					   if ((position.x - App->scope->position.x)> 0 && (position.x - App->scope->position.x) <= 38.6f){
						   current_animation = &shotopleft;
					   }
					   else if ((position.x - App->scope->position.x)> 38.6f && (position.x - App->scope->position.x) <= 77.3f){
						   current_animation = &shotleftop;
					   }
					   else if ((position.x - App->scope->position.x)>77.3f){
						   current_animation = &shotleft;

					   }

					   else if ((App->scope->position.x - position.x)> 0 && (App->scope->position.x - position.x) <= 38.6f){
						   current_animation = &shotopright;
					   }

					   else if ((App->scope->position.x - position.x)> 38.6f && (App->scope->position.x - position.x) <= 77.3f){
						   current_animation = &shotrighttop;
					   }

					   else if ((App->scope->position.x - position.x)>77.3f){
						   current_animation = &shotright;

					   }
				   }

				 
				   if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
					   && App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
					   && App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_IDLE){

					   current_animation = &idle;
				   }

	} break;

	case ROLL:
	{
				 player->type = COLLIDER_NONE;
				 if (current_animation == &jump_right){
					 if (position.x >= 220){
						 speed = 0;
					 }
					 else
					 {
						 position.x += speed + 1;
					 }
					 if (current_animation->Finished() == true){
						 status = NORMAL;
						 break;
					 }
				 }
				 if (current_animation == &jump_left){
					 if (position.x <= 0){
						 speed = 0;
					 }
					 else
					 {
						 position.x -= speed + 1;
					 }
					 if (current_animation->Finished() == true){
						 status = NORMAL;
						 break;
					 }
				 }
	} break;

	case DEAD:
	{
				 player->type = COLLIDER_NONE;
				 if (current_animation->Finished() ==true){
					 status = NORMAL;
					 break;
				 }

	} break;

	case WIN:
	{
		position.y = 100;
		player->type = COLLIDER_NONE;
		if (current_animation->Finished() == true){
			status = NORMAL;
			App->fade->FadeToBlack(App->level2, App->victoryscreen, 2);
			break;
		}
	}

	
	}
	player->rect.x = position.x + 10;
	player->rect.y = position.y + 20;
	player->rect.h = 8;
	player->rect.w = 12;

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));


	return UPDATE_CONTINUE;
}
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	hp--;
	dead.loops = 0;
	current_animation->Reset();
	current_animation = &dead;

	status = DEAD;

}