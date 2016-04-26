#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
#include "ModuleVictory.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Audio.h"
#include "ModuleScope.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL_timer.h"
#include "Extras.h"
#include "ModuleBuildings.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleLevel2::ModuleLevel2()
{
	// Background
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 224;
	
}

ModuleLevel2::~ModuleLevel2()
{}

// Load assets
bool ModuleLevel2::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("level2.png");

	App->player->Enable();
	App->audio->Enable();
	App->audio->Load("level.wav");
	App->particles->Enable();
	App->scope->Enable();
	App->enemies->Enable();

	App->building->Enable();

	return ret;
}

// Load assets
bool ModuleLevel2::CleanUp()
{
	LOG("Unloading level 2");
	App->player->Disable();
	App->audio->Disable();
	App->scope->Disable();
	App->enemies->Disable();
	App->building->Disable();

	return true;
}

// Update: draw background
update_status ModuleLevel2::Update()
{
	// Draw everything --------------------------------------	

	App->render->Blit(graphics, 0, 0, &background, 0); // level 2
	if(buildings==true){
		App->building->AddBuilding(App->building->yellow, 160, 30);
		buildings = false;
	}
	if (SDL_GetTicks() >= 10000 && extra == true){
		App->extra->AddExtra(App->extra->pig, 224, 140);
		extra = false;
	}
	if (SDL_GetTicks() >= 1000 && plane==true){
		App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 87,-20);
		plane = false;
	}
	if (SDL_GetTicks() >= 5000 && greencowboy == true){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 0, 100);
		greencowboy = false;
	}
	

	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->level2, App->victoryscreen, 2);
	}
	return UPDATE_CONTINUE;
}