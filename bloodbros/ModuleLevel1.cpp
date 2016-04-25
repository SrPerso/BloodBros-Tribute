#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Audio.h"
#include "Animation.h"
#include "Extras.h"
#include "ModuleScope.h"
#include "ModuleEnemies.h"

#include "SDL/include/SDL_timer.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleLevel1::ModuleLevel1()
{
	// Background
	background.x = 0;
	background.y = 0;
	background.w = 254;
	background.h = 224;
	
	//house1
	house1.x = 257;
	house1.y = 0;
	house1.w = 89;
	house1.h = 136;

	//house2
	house2.x = 360;
	house2.y = 0;
	house2.w = 112;
	house2.h = 144;

	
	

}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("level12.png");

	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	App->audio->Enable();
	App->audio->Load("level.wav");
	App->scope->Enable();
	App->enemies->Enable();
	uint start = SDL_GetTicks();
	//plane:
	
	/*App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 625, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 665, 80);*/
	return ret;
}

// Load assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading level 1");
	App->player->Disable();
	App->audio->Disable();
	App->scope->Disable();
	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	// Draw everything --------------------------------------	

	App->render->Blit(graphics, 0, 0, &background, 0); // level 1
	App->render->Blit(graphics, 0, 0, &house1, 0);
	App->render->Blit(graphics, 144, 0, &house2, 0);
	
	App->player->position.x += 0;
	App->player->position.y += 0;
	
	if (SDL_GetTicks()>= 10000 && extra==true){
		App->extra->AddExtra(App->extra->pig, 224, 140);
		extra = false;
	}
	if (SDL_GetTicks() >= 15000){
		App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 87, 0);
	}

	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->level1, App->level2, 2);
	}
	
	App->extra->OnCollision(App->extra->pig.collider, App->scope->shot);
	
	return UPDATE_CONTINUE;
}