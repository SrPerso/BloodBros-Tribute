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

	player = App->collision->AddCollider({ position.x+10, position.y+20, 12, 8}, COLLIDER_PLAYER);
	return ret;
}
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	if (App->input->keyboard[SDL_SCANCODE_Z] == 1){
		App->audio->Loadfx("shot.wav");
		App->particles->AddParticle(App->particles->laser, position.x+13, position.y -4);
	}
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{	
		if (position.x == 220){
			speed = 0;
		}
		
		position.x += speed;
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x == 0){
			speed = 0;
		}
		position.x -= speed;
		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	player->rect.x = position.x+10;
	player->rect.y = position.y+20;
	player->rect.h = 8;
	player->rect.w = 12;

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	
	
	return UPDATE_CONTINUE;
}