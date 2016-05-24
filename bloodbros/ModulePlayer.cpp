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
	idle.PushBack({ 150, 12, 46, 72 });
	//cowboy animation

	right.PushBack({ 12, 444, 46, 72 });
	right.PushBack({ 58, 444, 46, 72 });
	right.PushBack({ 104, 444, 46, 72 });
	right.PushBack({ 150, 444, 46, 72 });
	right.PushBack({ 196, 444, 46, 72 });
	right.PushBack({ 242, 444, 46, 72 });
	right.loop = true;
	right.speed = 0.1f;

	//cowboy animation

	left.PushBack({ 242, 516, 46, 72 });
	left.PushBack({ 196, 516, 46, 72 });
	left.PushBack({ 150, 516, 46, 72 });
	left.PushBack({ 104, 516, 46, 72 });
	left.PushBack({ 58, 516, 46, 72 });
	left.PushBack({ 12, 516, 46, 72 });
	left.loop = true;
	left.speed = 0.1f;

	//cowboy animation

	jump_left.PushBack({ 334, 156, 92, 72 });
	jump_left.PushBack({ 426, 156, 92, 72 });
	jump_left.PushBack({ 518, 156, 92, 72 });
	jump_left.PushBack({ 610, 156, 92, 72 }); 
	jump_left.PushBack({ 334, 228, 92, 72 });
	jump_left.PushBack({ 426, 228, 92, 72 });
	jump_left.PushBack({ 518, 228, 92, 72 });
	jump_left.PushBack({ 610, 228, 92, 72 });
	
	jump_left.loop = true;
	jump_left.speed = 0.15f;

	//cowboy animation


	jump_right.PushBack({ 334, 12, 92, 72 });
	jump_right.PushBack({ 426, 12, 92, 72 });
	jump_right.PushBack({ 518, 12, 92, 72 });
	jump_right.PushBack({ 610, 12, 92, 72 });
	jump_right.PushBack({ 334, 84, 92, 72 });
	jump_right.PushBack({ 426, 84, 92, 72 });
	jump_right.PushBack({ 518, 84, 92, 72 });
	jump_right.PushBack({ 610, 84, 92, 72 });

	jump_right.loop = true;
	jump_right.speed = 0.15f;

	dead.PushBack({ 334, 444, 92, 72 });
	dead.PushBack({ 426, 444, 92, 72 });
	dead.PushBack({ 518, 444, 92, 72 });
	dead.PushBack({ 610, 444, 92, 72 });
	dead.PushBack({ 334, 516, 92, 72 });
	dead.PushBack({ 426, 516, 92, 72 });
	dead.loop = true;
	dead.speed = 0.1f;
	
	//shot idle

	shotidle.PushBack({ 12, 12, 46, 72 }); //cowboy de pie apuntando extremo izquierda  <<<-
	shotidle.PushBack({ 58, 12, 46, 72 }); //cowboy de pie apuntando izquierda  <<-
	shotidle.PushBack({ 104, 12, 46, 72 }); //cowboy de pie apuntando un poco a la izquierda  <-
	shotidle.PushBack({ 196, 12, 46, 72 }); //cowboy de pie apuntando un poco derecha ->
	shotidle.PushBack({ 242, 12, 46, 72 }); //cowboy de pie apuntando derecha ->>
	shotidle.PushBack({ 288, 12, 46, 72 }); //cowboy de pie apuntando extremo derecha ->>>

	shotidle.speed = 0.1f;
	//aiming left

	shotleft.PushBack({ 12, 84, 46, 72 });
	shotleft.PushBack({ 12, 12, 46, 72 });
	shotleft.PushBack({ 12, 156, 46, 72 });
	shotleft.PushBack({ 12, 12, 46, 72 });
	shotleft.speed = 0.1f;

	//aiming left top

	shotleftop.PushBack({ 58, 84, 46, 72 });
	shotleftop.PushBack({ 58, 12, 46, 72 });
	shotleftop.PushBack({ 58, 156, 46, 72 });
	shotleftop.PushBack({ 58, 12, 46, 72 });
	shotleftop.speed = 0.1f;
	//aiming top left

	shotopleft.PushBack({ 104, 84, 46, 72 });
	shotopleft.PushBack({ 104, 12, 46, 72 });
	shotopleft.PushBack({ 104, 156, 46, 72 });
	shotopleft.PushBack({ 104, 12, 46, 72 });
	shotopleft.speed = 0.1f;
	//aiming top

	shotop.PushBack({ 150, 84, 46, 72 });
	shotop.PushBack({ 150, 12, 46, 72 });
	shotop.PushBack({ 150, 156, 46, 72 });
	shotop.PushBack({ 150, 12, 46, 72 });
	shotop.speed = 0.1f;
	//aiming right

	shotright.PushBack({ 288, 84, 46, 72 });
	shotright.PushBack({ 288, 12, 46, 72 });
	shotright.PushBack({ 288, 156, 46, 72 });
	shotright.PushBack({ 288, 12, 46, 72 });
	shotright.speed = 0.1f;


	//aiming right top
	
	shotrighttop.PushBack({ 242, 84, 46, 72 });
	shotrighttop.PushBack({ 242, 12, 46, 72 });
	shotrighttop.PushBack({ 242, 156, 46, 72 });
	shotrighttop.PushBack({ 242, 12, 46, 72 });
	shotrighttop.speed = 0.1f;
	
	//aiming top right

	shotopright.PushBack({ 196, 84, 46, 72 });
	shotopright.PushBack({ 196, 12, 46, 72 });
	shotopright.PushBack({ 196, 156, 46, 72 });
	shotopright.PushBack({ 196, 12, 46, 72 });
	shotopright.speed = 0.1f;

	//dancing



	dance.PushBack({ 334, 300, 46, 72 }); //cowboy cuando gana y esta parado // la inicial
	dance.PushBack({ 406, 300, 46, 72 }); //cowboy apunto de levantar la mano
	dance.PushBack({ 478, 300, 46, 72 }); //cowboy levanta la mano
	dance.PushBack({ 550, 300, 46, 72 }); // cowboy baila levantando pierna izquierda
	dance.PushBack({ 622, 300, 46, 72 }); //cowboy baila levantando pierna derecha
	dance.PushBack({ 694, 300, 46, 72 }); //cowboy baila levantando pierna izquierda un pcoo alejado
	dance.PushBack({ 766, 300, 46, 72 }); //cowboy baila levantando las dos manos y una pierna un poco alejado
	dance.PushBack({ 838, 300, 46, 72 }); //cowboy baila un pcoo mas alejado 1
	dance.PushBack({ 334, 372, 46, 72 }); //cowboy baila un pcoo mas alejado 2
	dance.PushBack({ 406, 372, 46, 72 }); // cowboy casi no se ve 1 saltando como una rana
	dance.PushBack({ 478, 372, 46, 72 }); //cowboy casi no se ve 2 saltando sin tocar el suelo
	dance.PushBack({ 550, 372, 46, 72 }); //cowboy esta tan lejos que casi no se ve 1
	dance.PushBack({ 622, 372, 46, 72 }); //cowboy esta tan lejos que casi no se ve 2

	dance.loop = false;
	dance.speed = 0.05f;
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Images/Main_character_CowBoy.png"); // arcade version

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
		position.y -= 0.3;
		position.x = 100;
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
	hit = true;

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