#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "Audio.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{

	graphics = NULL;
	current_animation = NULL;

	position.x = 105;
	position.y = 155;
	idle.PushBack({ 119, 1, 30, 61 });
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
	jump_left.speed = 0.2f;

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
	jump_right.speed = 0.2f;

	
	


}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("cowboy.png"); // arcade version

	position.x = 105;
	position.y = 155;

	player = App->collision->AddCollider({ position.x+10, position.y+20, 12, 8}, COLLIDER_PLAYER, this);
	return ret;
}
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->collision->CleanUp(); 
	App->textures->Unload(graphics);
	
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	float speed = 1.4f;
	
		
	
	
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{	
		if (position.x >= 220){
			speed = 0;
		}
		
		position.x += speed;
		if (current_animation != &right && App->input->keyboard[SDL_SCANCODE_LALT] != KEY_STATE::KEY_REPEAT)
		{
			right.Reset();
			current_animation = &right;
		}
		else if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x <= 0){
				speed = 0;
			}
			//position.x -= speed;
			if (current_animation != &jump_right)
			{
				jump_right.Reset();
				current_animation = &jump_right;
				position.x += speed+1;

			}
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x <= 0){
			speed = 0;
		}
		position.x -= speed;
		if (current_animation != &left && App->input->keyboard[SDL_SCANCODE_LALT] != KEY_STATE::KEY_REPEAT)
		{
			left.Reset();
			current_animation = &left;
		}
		else if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x <= 0){
				speed = 0;
			}
			//position.x -= speed;
			if (current_animation != &jump_left)
			{
				jump_left.Reset();
				current_animation = &jump_left;
				position.x -= speed+1;

			}
		}
	}


	else if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN)
	{
		if (position.x <= 0){
			speed = 0;
		}
		position.x -= speed;
		if (current_animation != &jump_left)
		{
			jump_left.Reset();
			current_animation = &jump_left;
			
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	player->rect.x = position.x+10;
	player->rect.y = position.y+20;
	player->rect.h = 8;
	player->rect.w = 12;

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	
	return UPDATE_CONTINUE;
}