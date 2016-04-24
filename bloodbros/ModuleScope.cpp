#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "Audio.h"
#include "ModuleCollision.h"
#include "ModuleScope.h"
#include "Extras.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScope::ModuleScope()
{

	graphics = NULL;
	current_animation = NULL;

	position.x = 105;
	position.y = 155;
	
	scope.PushBack({ 3, 2, 24, 22 });
	scope.PushBack({ 35, 2, 24, 22 });
	scope.loop = true;
	scope.speed = 0.1f;

	shoots.PushBack({ 67, 2, 22, 22 });
	shoots.PushBack({ 95, 2, 22, 22 });
	shoots.PushBack({ 120, 2, 22, 22 });
}

ModuleScope::~ModuleScope()
{}

// Load assets
bool ModuleScope::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Particles.png"); // arcade version

	position.x = 105;
	position.y = 45;

	shot = App->collision->AddCollider({ position.x+3, position.y+3, 22, 20 }, COLLIDER_PLAYER_SHOT);
	return ret;
}	
bool ModuleScope::CleanUp()
{
	LOG("Unloading player");
	App->collision->CleanUp();
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleScope::Update()
{
	float speed = 3.5;
	if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT){
		
		App->render->Blit(graphics, position.x, position.y, &(shoots.GetCurrentFrame()));
		App->extra->OnCollision(App->extra->pig.collider, App->scope->shot);

			//extra->OnCollision(extra,  shot);

	}
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT){
		if (position.y <= 0){
			speed = 0;
		}
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT){
		if (position.y >= 200){
			speed = 0;
		}
		position.y += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT){
		if (position.x <= 0){
			speed = 0;
		}
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT){
		if (position.x >= 230){
			speed = 0;
		}
		position.x += speed;
	}


	shot->rect.x = position.x+1;
	shot->rect.y = position.y+1;
	current_animation = &scope;
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));


	return UPDATE_CONTINUE;
}

/*void ModuleScope::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->CheckCollision(c2->rect) == true){
		c2 = nullptr;
	}
}*/