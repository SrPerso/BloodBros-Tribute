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
#include "ModuleEnemies.h"
#include "SDL/include/SDL_timer.h"

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
	shoots.loop = true;
	shoots.speed = 0.1f;

	shotgunscope.PushBack({ 450, 38, 31, 29 });
	shotgunscope.PushBack({ 486, 38, 31, 29 });
	shotgunscope.loop = true;
	shotgunscope.speed = 0.1f;

}

ModuleScope::~ModuleScope()
{}

// Load assets
bool ModuleScope::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Images/particles.png"); 

	position.x = 105;
	position.y = 45;

	shot = App->collision->AddCollider({ position.x+3, position.y+3, 22, 20 }, COLLIDER_NONE);
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
	if ((App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT && App->player->status == NORMAL) || (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT && App->player->status == CROUCH)){
		if (SDL_GetTicks() > time){
			time = SDL_GetTicks() +300;
			shot->type = COLLIDER_PLAYER_SHOT;
			App->audio->Loadfx("Music/shot.ogg");
		}
		else{
			shot->type = COLLIDER_NONE;
		}
	}
	else if (App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_REPEAT){
		
		shot->type = COLLIDER_NONE;
		didsound = false;
	}
	if ((App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && App->player->tntammo >= 1 && App->player->status == NORMAL) || (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && App->player->tntammo >= 1 && App->player->status == CROUCH)){

		App->particles->AddParticle(App->particles->tnt, App->player->position.x + 3, App->player->position.y + 3, COLLIDER_NONE, 0);
		App->player->tntammo--;
	}
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT){
		if (position.y <= 0){
			speed = 0;
		}
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_UP] != KEY_STATE::KEY_UP){
		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT){
			if (position.y <= 0){
				speed = 0;
			}
			position.y -= speed;
		}
		else if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT){
			if (position.x <= 0){
				speed = 0;
			}
			position.x -= speed;
		}
		else if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT){
			if (position.x >= 230){
				speed = 0;
			}
			position.x += speed;
		}
		else{
			if (position.y >= 180){
				speed = 0;
			}
			position.y += speed;
		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT){
		if (position.x <= 0){
			speed = 0;
		}
		position.x -= speed;
	}
	else if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT){
		if (position.x >= 230){
			speed = 0;
		}
		position.x += speed;
	}

	if (shotgun == true || App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN){
		current_animation = &shotgunscope;
		shot->rect.w = 31;
		shot->rect.h = 29;
		if (firstime == true){
			poweruptime = SDL_GetTicks() + 6000;//shotgun scope duration=6s
			firstime = false;
		}
		if (SDL_GetTicks() > poweruptime){
			shotgun = false;
		}
	}
	if (shotgun==false){
		shotgun = false;
		current_animation = &scope;
		shot->rect.w = 22;
		shot->rect.h = 20;
		firstime = true;
	}
	shot->rect.x = position.x+1;
	shot->rect.y = position.y+1;
	
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));


	return UPDATE_CONTINUE;
}

/*void ModuleScope::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->CheckCollision(c2->rect) == true){
		c2 = nullptr;
	}
}*/