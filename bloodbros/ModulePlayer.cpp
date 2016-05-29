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
#include "ModuleFonts.h"
#include <stdio.h>


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
	right.speed = 0.25f;

	//cowboy animation

	left.PushBack({ 242, 516, 46, 72 });
	left.PushBack({ 196, 516, 46, 72 });
	left.PushBack({ 150, 516, 46, 72 });
	left.PushBack({ 104, 516, 46, 72 });
	left.PushBack({ 58, 516, 46, 72 });
	left.PushBack({ 12, 516, 46, 72 });
	left.loop = true;
	left.speed = 0.25f;

	//cowboy animation

	jump_left.PushBack({ 352, 156, 84, 72 });
	jump_left.PushBack({ 352, 156, 84, 72 });
	jump_left.PushBack({ 352, 156, 84, 72 });

	jump_left.PushBack({ 436, 156, 92, 72 });
	jump_left.PushBack({ 436, 156, 92, 72 });
	jump_left.PushBack({ 436, 156, 92, 72 });
	
	jump_left.PushBack({ 518, 156, 92, 72 });
	jump_left.PushBack({ 518, 156, 92, 72 });
	jump_left.PushBack({ 518, 156, 92, 72 });

	jump_left.PushBack({ 334, 228, 92, 72 });
	jump_left.PushBack({ 334, 228, 92, 72 });
	jump_left.PushBack({ 334, 228, 92, 72 });

	
	jump_left.PushBack({ 426, 228, 92, 72 });
	jump_left.PushBack({ 426, 228, 92, 72 });

	
	jump_left.PushBack({ 610, 228, 92, 72 });
	
	jump_left.loop = false;
	jump_left.speed = 0.30f;

	//cowboy animation


	jump_right.PushBack({ 352, 12, 84, 72 });
	jump_right.PushBack({ 352, 12, 84, 72 });
	jump_right.PushBack({ 352, 12, 84, 72 });

	jump_right.PushBack({ 436, 12, 92, 72 });
	jump_right.PushBack({ 436, 12, 92, 72 });
	jump_right.PushBack({ 436, 12, 92, 72 });

	jump_right.PushBack({ 518, 12, 92, 72 });
	jump_right.PushBack({ 518, 12, 92, 72 });
	jump_right.PushBack({ 518, 12, 92, 72 });

	jump_right.PushBack({ 334, 84, 92, 72 });
	jump_right.PushBack({ 334, 84, 92, 72 });
	jump_right.PushBack({ 334, 84, 92, 72 });


	jump_right.PushBack({ 426, 84, 92, 72 });
	jump_right.PushBack({ 426, 84, 92, 72 });


	jump_right.PushBack({ 610, 84, 92, 72 });

	jump_right.loop = false;
	jump_right.speed = 0.30f;

	dead.PushBack({ 314, 444, 80, 72 });
	dead.PushBack({ 406, 444, 80, 72 });
	dead.PushBack({ 498, 444, 80, 72 });
	dead.PushBack({ 590, 444, 80, 72 });
	dead.PushBack({ 314, 516, 80, 72 });
	dead.PushBack({ 406, 516, 80, 72 });
	dead.PushBack({ 406, 516, 80, 72 });
	dead.PushBack({ 314, 516, 80, 72 });
	dead.PushBack({ 314, 516, 80, 72 });
	dead.PushBack({ 406, 516, 80, 72 });
	dead.loop = true;
	dead.speed = 0.1f;
	
	//shot idle

	shotidle.PushBack({ 150, 12, 46, 72 }); 
	shotidle.PushBack({ 150, 84, 46, 72 }); 
	shotidle.PushBack({ 150, 12, 46, 72 });
	shotidle.PushBack({ 150, 156, 46, 72 }); 
	shotidle.speed = 0.12f;


	shotidle.speed = 0.12f;
	//aiming left

	shotleft.PushBack({ 12, 84, 46, 72 });
	shotleft.PushBack({ 12, 12, 46, 72 });
	shotleft.PushBack({ 12, 156, 46, 72 });
	shotleft.PushBack({ 12, 12, 46, 72 });
	shotleft.speed = 0.12f;

	//aiming left top

	shotleftop.PushBack({ 58, 84, 46, 72 });
	shotleftop.PushBack({ 58, 12, 46, 72 });
	shotleftop.PushBack({ 58, 156, 46, 72 });
	shotleftop.PushBack({ 58, 12, 46, 72 });
	shotleftop.speed = 0.12f;
	//aiming top left

	shotopleft.PushBack({ 104, 84, 46, 72 });
	shotopleft.PushBack({ 104, 12, 46, 72 });
	shotopleft.PushBack({ 104, 156, 46, 72 });
	shotopleft.PushBack({ 104, 12, 46, 72 });
	shotopleft.speed = 0.12f;
	//aiming top

	shotop.PushBack({ 150, 84, 46, 72 });
	shotop.PushBack({ 150, 12, 46, 72 });
	shotop.PushBack({ 150, 156, 46, 72 });
	shotop.PushBack({ 150, 12, 46, 72 });
	shotop.speed = 0.12f;
	//aiming right

	shotright.PushBack({ 288, 84, 46, 72 });
	shotright.PushBack({ 288, 12, 46, 72 });
	shotright.PushBack({ 288, 156, 46, 72 });
	shotright.PushBack({ 288, 12, 46, 72 });
	shotright.speed = 0.12f;


	//aiming right top
	
	shotrighttop.PushBack({ 242, 84, 46, 72 });
	shotrighttop.PushBack({ 242, 12, 46, 72 });
	shotrighttop.PushBack({ 242, 156, 46, 72 });
	shotrighttop.PushBack({ 242, 12, 46, 72 });
	shotrighttop.speed = 0.12f;
	
	//aiming top right

	shotopright.PushBack({ 196, 84, 46, 72 });
	shotopright.PushBack({ 196, 12, 46, 72 });
	shotopright.PushBack({ 196, 156, 46, 72 });
	shotopright.PushBack({ 196, 12, 46, 72 });
	shotopright.speed = 0.12f;

	//looking left
	lookingleft.PushBack({ 104, 12, 46, 72 });
	lookingfarleft.PushBack({ 58, 12, 46, 72 });
	lookingveryfarleft.PushBack({ 12, 12, 46, 72 });

	//looking right

	lookingright.PushBack({ 196, 12, 46, 72 });
	lookingfarright.PushBack({ 242, 12, 46, 72 });
	lookingveryfarright.PushBack({ 288, 12, 46, 72 });

	//dancing

	dance.PushBack({ 334, 300, 46, 72 });
	dance.PushBack({ 380, 300, 46, 72 });
	dance.PushBack({ 426, 300, 46, 72 });
	dance.PushBack({ 472, 300, 46, 72 });

	dance.PushBack({ 518, 300, 46, 72 });
	dance.PushBack({ 564, 300, 46, 72 });
	dance.PushBack({ 610, 300, 46, 72 });
	dance.PushBack({ 656, 300, 46, 72 });


	dance.PushBack({ 334, 372, 46, 72 });
	dance.PushBack({ 380, 372, 46, 72 });
	dance.PushBack({ 426, 372, 46, 72 });
	dance.PushBack({ 472, 372, 46, 72 });
	dance.PushBack({ 518, 372, 46, 72 }); 

	dance.loop = false;
	dance.speed = 0.05f;

	crouch.PushBack({ 150, 228, 46, 72 });

	crouchshotidle.PushBack({ 150, 228, 46, 72 });
	crouchshotidle.PushBack({ 150, 300, 46, 72 });
	crouchshotidle.PushBack({ 150, 228, 46, 72 });
	crouchshotidle.PushBack({ 150, 372, 46, 72 });
	crouchshotidle.speed = 0.12f;

	crouchshotrighttop.PushBack({ 288, 228, 46, 72 });
	crouchshotrighttop.PushBack({ 288, 300, 46, 72 });
	crouchshotrighttop.PushBack({ 288, 228, 46, 72 });
	crouchshotrighttop.PushBack({ 288, 372, 46, 72 });
	crouchshotrighttop.speed = 0.12f;

	crouchshotopright.PushBack({ 242, 228, 46, 72 });
	crouchshotopright.PushBack({ 242, 300, 46, 72 });
	crouchshotopright.PushBack({ 242, 228, 46, 72 });
	crouchshotopright.PushBack({ 242, 372, 46, 72 });
	crouchshotopright.speed = 0.12f;

	crouchshotright.PushBack({ 196, 228, 46, 72 });
	crouchshotright.PushBack({ 196, 300, 46, 72 });
	crouchshotright.PushBack({ 196, 228, 46, 72 });
	crouchshotright.PushBack({ 196, 372, 46, 72 });
	crouchshotright.speed = 0.12f;

	crouchshotlefttop.PushBack({ 12, 228, 46, 72 });
	crouchshotlefttop.PushBack({ 12, 300, 46, 72 });
	crouchshotlefttop.PushBack({ 12, 228, 46, 72 });
	crouchshotlefttop.PushBack({ 12, 372, 46, 72 });
	crouchshotlefttop.speed = 0.12f;

	crouchshottopleft.PushBack({ 58, 228, 46, 72 });
	crouchshottopleft.PushBack({ 58, 300, 46, 72 });
	crouchshottopleft.PushBack({ 58, 228, 46, 72 });
	crouchshottopleft.PushBack({ 58, 372, 46, 72 });
	crouchshottopleft.speed = 0.12f;

	crouchshotleft.PushBack({ 104, 228, 46, 72 });
	crouchshotleft.PushBack({ 104, 300, 46, 72 });
	crouchshotleft.PushBack({ 104, 228, 46, 72 });
	crouchshotleft.PushBack({ 104, 372, 46, 72 });
	crouchshotleft.speed = 0.12f;

	crouchjumpleft.PushBack({ 610, 156, 92, 72 });
	crouchjumpleft.PushBack({ 610, 156, 92, 72 });
	crouchjumpleft.PushBack({ 334, 228, 92, 72 });
	crouchjumpleft.PushBack({ 334, 228, 92, 72 });
	crouchjumpleft.PushBack({ 426, 228, 92, 72 });
	crouchjumpleft.PushBack({ 610, 228, 92, 72 });
	crouchjumpleft.loop = false;
	crouchjumpleft.speed = 0.20f;

	crouchjumpright.PushBack({ 635, 12, 92, 72 });
	crouchjumpright.PushBack({ 635, 12, 92, 72 });
	crouchjumpright.PushBack({ 335, 84, 92, 72 });
	crouchjumpright.PushBack({ 335, 84, 92, 72 });
	crouchjumpright.PushBack({ 427, 84, 92, 72 });
	crouchjumpright.PushBack({ 611, 84, 92, 72 });
	crouchjumpright.loop = false;
	crouchjumpright.speed = 0.20f;

	//looking while crouching
	crouchlookingleft.PushBack({ 104, 228, 46, 72 });
	crouchlookingfarleft.PushBack({ 58, 228, 46, 72 });
	crouchlookingveryfarleft.PushBack({ 12, 228, 46, 72 });
	crouchlookingright.PushBack({ 196, 228, 46, 72 });
	crouchlookingfarright.PushBack({ 242, 228, 46, 72 });
	crouchlookingveryfarright.PushBack({ 288, 228, 46, 72 });
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Images/Main_character_CowBoy.png"); // arcade version
	score = 0;

	position.x = 105;
	position.y = 140;
	status = NORMAL;
	hp = 3;
	player = App->collision->AddCollider({ position.x+14, position.y+20, 12, 8}, COLLIDER_PLAYER, this);
	font_score = App->font->Load("Images/fonts2.png", "0123456789abcdefghijklmnopqrstuvwxyz", 1);
	return ret;
}
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->collision->CleanUp(); 
	App->textures->Unload(graphics);
	App->font->UnLoad(font_score);
	status = NORMAL;
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	float speed = 1.6f;


	switch (status){
	case NORMAL:
	{
		if (god == false){
			player->type = COLLIDER_PLAYER;
		}
		else if (god == true){
			player->type = COLLIDER_NONE;
		}
		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x >= 200){
				speed = 0;
			}
			position.x += speed;
			if (current_animation != &right && App->input->keyboard[SDL_SCANCODE_LALT] != KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_REPEAT)
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
				score += 10;
				position.x -= speed;
				if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
					current_animation = &shotidle;
				}
				else if ((App->scope->position.x - position.x) > 10 && (App->scope->position.x - position.x) <= 38.6f){
					current_animation = &shotopright;

				}
				else if ((App->scope->position.x - position.x) > 38.6f && (App->scope->position.x - position.x) <= 77.3f){
					current_animation = &shotrighttop;

				}
				else if ((App->scope->position.x - position.x) > 77.3f){
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
				score += 10;
				position.x += speed;
				if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
					current_animation = &shotidle;
				}
				else if ((position.x - App->scope->position.x) > 10 && (position.x - App->scope->position.x) <= 38.6f){
					current_animation = &shotopleft;
				}
				else if ((position.x - App->scope->position.x) > 38.6f && (position.x - App->scope->position.x) <= 77.3f){
					current_animation = &shotleftop;
				}
				else if ((position.x - App->scope->position.x) > 77.3f){
					current_animation = &shotleft;

				}



			}
		}

		else if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT || (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_RIGHT] != KEY_STATE::KEY_REPEAT  && App->input->keyboard[SDL_SCANCODE_LEFT] != KEY_STATE::KEY_REPEAT)){
			if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
				current_animation = &shotidle;
			}

			else if ((position.x - App->scope->position.x) > 10 && (position.x - App->scope->position.x) <= 38.6f){
				current_animation = &shotopleft;
			}
			else if ((position.x - App->scope->position.x) > 38.6f && (position.x - App->scope->position.x) <= 77.3f){
				current_animation = &shotleftop;
			}
			else if ((position.x - App->scope->position.x) > 77.3f){
				current_animation = &shotleft;

			}

			else if ((App->scope->position.x - position.x) > 10 && (App->scope->position.x - position.x) <= 38.6f){
				current_animation = &shotopright;
			}

			else if ((App->scope->position.x - position.x) > 38.6f && (App->scope->position.x - position.x) <= 77.3f){
				current_animation = &shotrighttop;
			}

			else if ((App->scope->position.x - position.x) > 77.3f){
				current_animation = &shotright;

			}

		}


		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_IDLE){
				if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
					current_animation = &idle;
				}
				else if ((position.x - App->scope->position.x) > 10 && (position.x - App->scope->position.x) <= 38.6f){
					current_animation = &lookingleft;
				}
				else if ((position.x - App->scope->position.x) > 38.6f && (position.x - App->scope->position.x) <= 77.3f){
					current_animation = &lookingfarleft;
				}
				else if ((position.x - App->scope->position.x) > 77.3f){
					current_animation = &lookingveryfarleft;

				}

				else if ((App->scope->position.x - position.x) > 10 && (App->scope->position.x - position.x) <= 38.6f){
					current_animation = &lookingright;//
				}

				else if ((App->scope->position.x - position.x) > 38.6f && (App->scope->position.x - position.x) <= 77.3f){
					current_animation = &lookingfarright;
				}

				else if ((App->scope->position.x - position.x) > 77.3f){
					current_animation = &lookingveryfarright;
				}
				else{
					current_animation = &idle;
				}
		}
		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN){
			current_animation = &crouch;
			status = CROUCH;
		}
		player->rect.x = position.x + 14;
		player->rect.y = position.y + 20;
		player->rect.h = 16;
		player->rect.w = 12;
	} break;

	case ROLL:
	{
		player->type = COLLIDER_NONE;
		if (current_animation == &jump_right){
			if (position.x >= 180){
				speed = 0;
			}
			else
			{
				position.x += speed;
			}
			if (current_animation->Finished() == true){
				if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT){
					current_animation = &crouch;
					status = CROUCH;
				}
				else{
					status = NORMAL;
				}
				break;
			}
		}
		if (current_animation == &jump_left){
			if (position.x <= 0){
				speed = 0;
			}
			else
			{
				position.x -= speed;
			}
			if (current_animation->Finished() == true){
				if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT){
					current_animation = &crouch;
					status = CROUCH;
				}
				else{
					status = NORMAL;
				}
				break;
			}
		}
	} break;
	case CROUCHROLL:
	{
		player->type = COLLIDER_NONE;
		if (current_animation == &crouchjumpright){
			if (position.x >= 180){
				speed = 0;
			}
			else
			{
				position.x += (speed*2)/3;
			}
			if (current_animation->Finished() == true){
				if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT){
					current_animation = &crouch;
					status = CROUCH;
				}
				else{
					status = NORMAL;
				}
				break;
			}
		}
		if (current_animation == &crouchjumpleft){
			if (position.x <= 0){
				speed = 0;
			}
			else
			{
				position.x -= (speed * 2) / 3;
			}
			if (current_animation->Finished() == true){
				if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT){
					current_animation = &crouch;
					status = CROUCH;
				}
				else{
					status = NORMAL;
				}
				break;
			}
		}
	} break;
	case DEAD:
	{
		player->type = COLLIDER_NONE;
		if (current_animation->Finished() == true){
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
			current_animation->Reset();
			current_animation->loops = 0;
			App->fade->FadeToBlack(App->level2, App->victoryscreen, 2);
			status = NORMAL;
			break;
		}
	}break;

	case CROUCH:
	{
		player->rect.x = position.x + 10;
		player->rect.y = position.y + 40;
		player->rect.h = 8;
		player->rect.w = 12;
		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT){
			if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT){
				if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
					current_animation = &crouchshotidle;
				}

				else if ((position.x - App->scope->position.x) > 10 && (position.x - App->scope->position.x) <= 38.6f){
					current_animation = &crouchshotleft;
				}
				else if ((position.x - App->scope->position.x) > 38.6f && (position.x - App->scope->position.x) <= 77.3f){
					current_animation = &crouchshottopleft;
				}
				else if ((position.x - App->scope->position.x) > 77.3f){
					current_animation = &crouchshotlefttop;

				}

				else if ((App->scope->position.x - position.x) > 10 && (App->scope->position.x - position.x) <= 38.6f){
					current_animation = &crouchshotright;//
				}

				else if ((App->scope->position.x - position.x) > 38.6f && (App->scope->position.x - position.x) <= 77.3f){
					current_animation = &crouchshotopright;
				}

				else if ((App->scope->position.x - position.x) > 77.3f){
					current_animation = &crouchshotrighttop;

				}

			}
			else{
				if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
					current_animation = &crouch;
				}
				else if ((position.x - App->scope->position.x) > 10 && (position.x - App->scope->position.x) <= 38.6f){
					current_animation = &crouchlookingleft;
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpleft.loops = 0;
						crouchjumpleft.Reset();
						current_animation = &crouchjumpleft;
						status = CROUCHROLL;
					}
				}
				else if ((position.x - App->scope->position.x) > 38.6f && (position.x - App->scope->position.x) <= 77.3f){
					current_animation = &crouchlookingfarleft;
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpleft.loops = 0;
						crouchjumpleft.Reset();
						current_animation = &crouchjumpleft;
						status = CROUCHROLL;
					}
				}
				else if ((position.x - App->scope->position.x) > 77.3f){
					current_animation = &crouchlookingveryfarleft;
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpleft.loops = 0;
						crouchjumpleft.Reset();
						current_animation = &crouchjumpleft;
						status = CROUCHROLL;
					}

				}

				else if ((App->scope->position.x - position.x) > 10 && (App->scope->position.x - position.x) <= 38.6f){
					current_animation = &crouchlookingright;//
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpright.loops = 0;
						crouchjumpright.Reset();
						current_animation = &crouchjumpright;
						status = CROUCHROLL;
					}
				}

				else if ((App->scope->position.x - position.x) > 38.6f && (App->scope->position.x - position.x) <= 77.3f){
					current_animation = &crouchlookingfarright;
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpright.loops = 0;
						crouchjumpright.Reset();
						current_animation = &crouchjumpright;
						status = CROUCHROLL;
					}
				}

				else if ((App->scope->position.x - position.x) > 77.3f){
					current_animation = &crouchlookingveryfarright;
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpright.loops = 0;
						crouchjumpright.Reset();
						current_animation = &crouchjumpright;
						status = CROUCHROLL;
					}
				}
			}
			
		}
		else{
			status = NORMAL;
		}
	}break;
	}
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN){
		if (god == false){
			player->type = COLLIDER_NONE;
			App->textures->Unload(graphics);
			graphics = App->textures->Load("Images/Main_character_CowBoy_GodMode.png");
			god = true;

		}
		else if (god == true){
			App->textures->Unload(graphics);
			graphics = App->textures->Load("Images/Main_character_CowBoy.png");
			god = false;
			player->type = COLLIDER_PLAYER;
		}
	}
	/*player->rect.x = position.x + 10;
	player->rect.y = position.y + 20;
	player->rect.h = 8;
	player->rect.w = 12;*/
	hit = true;

	

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	sprintf_s(score_text, 10, "%7d", score);
	sprintf_s(tnt_text, 10, "%7d", tntammo);
	App->font->Blit(18, 1, font_score, score_text);
	App->font->Blit(0, 201, font_score, tnt_text);

	return UPDATE_CONTINUE;
}
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	App->audio->Loadfx("Music/playerhit.ogg");
	hp--;
	dead.loops = 0;
	current_animation->Reset();
	current_animation = &dead;

	status = DEAD;

}