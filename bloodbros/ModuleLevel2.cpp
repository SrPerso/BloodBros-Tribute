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
#include "ModuleUi.h"

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
	extra = true;
	greencowboy = true;
	bluecowboy = true;
	buildings = true;
	plane = true;
	jumper = true;
	greencowboymedium = true;
	graphics = App->textures->Load("Images/level2.png");
	timestart = SDL_GetTicks();
	App->player->Enable();
	App->audio->Enable();
	App->audio->Load("Music/level.ogg");
	App->particles->Enable();
	App->scope->Enable();
	
	
	App->building->Enable();
	App->enemies->Enable();
	App->collision->Enable();
	App->extra->Enable();
	App->collision->AddCollider({ 0, 200, 256, 46 }, COLLIDER_WALL, this);
	App->enemies->hits = 0;
	App->building->AddBuilding(App->building->trees, -25, 30);
	App->building->AddBuilding(App->building->trees, 15, 30);
	App->building->AddBuilding(App->building->trees, 55, 30);
	App->building->AddBuilding(App->building->trees, 196, 30);
	App->building->AddBuilding(App->building->trees, 162, 30);
	App->building->AddBuilding(App->building->trees, 230, 30);
	App->building->AddBuilding(App->building->yellow, 160, 30);
	App->building->AddBuilding(App->building->purple, 0, 53);
	App->building->AddBuilding(App->building->mill, 30, 74);
	App->ui->Enable();

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
	App->collision->Disable();
	App->particles->Disable();
	App->extra->Disable();
	App->ui->Disable();
	return true;
}

// Update: draw background
update_status ModuleLevel2::Update()
{
	// Draw everything --------------------------------------	

	App->render->Blit(graphics, 0, 0, &background, 0); // level 2
	App->ui->Update();
	if (SDL_GetTicks() >= timestart+10000 && extra == true){
		App->extra->AddExtra(App->extra->pig, 0, 140);
		App->extra->AddExtra(App->extra->blackpig, 224, 140);
		App->extra->AddExtra(App->extra->zepe, 224, 35);
		extra = false;
	}
	if (SDL_GetTicks() >= timestart + 5000 && plane == true){
		App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 70,-20);
		
		App->extra->AddExtra(App->extra->cask, 0, 160);
		plane = false;
	}
	if (SDL_GetTicks() >=  timestart + 6000 && greencowboy == true && App->building->purplealive==true){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 58, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 67);
		greencowboy = false;
	}
	else if (SDL_GetTicks() >= timestart + 6000 && greencowboy == true && App->building->purplealive == false){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 0, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 10, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 20, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 80);
		greencowboy = false;
	}
	else if (SDL_GetTicks() >= timestart + 6000 && jumper == true && App->building->windmillalive == true){
		App->enemies->AddEnemy(ENEMY_TYPES::JUMPER, 30, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::JUMPER, 50, 100);
		jumper = false;
	}

	if (SDL_GetTicks() >= timestart + 9000 && bluecowboy == true){
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 50, 62);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 60, 62);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 70, 62);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 80, 62);
		App->enemies->AddEnemy(ENEMY_TYPES::GREENRIGHTCOWBOY, 168, 80);
		bluecowboy = false;
	}

	if (SDL_GetTicks() >= timestart + 15000 && plane2 == true){
		App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 87, -20);
		
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOYMEDIUM, 0, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOYMEDIUM, 15, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOYMEDIUM, 30, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOYMEDIUM, 45, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOYMEDIUM, 60, 100);

		plane2 = false;
	}
	if (SDL_GetTicks() >= timestart + 20000 && green2 == true && App->building->purplealive == true){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 58, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 80);

		App->enemies->AddEnemy(ENEMY_TYPES::INDIANMEDIUM, 00, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::INDIANMEDIUM, 15, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::INDIANMEDIUM, 30, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::INDIANMEDIUM, 45, 100);
		
		green2 = false;
	}
	else if (SDL_GetTicks() >= timestart + 20000 && green2 == true && App->building->purplealive == false){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 0, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 10, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 20, 80);

		App->enemies->AddEnemy(ENEMY_TYPES::INDIANMEDIUM, 00, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::INDIANMEDIUM, 15, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::INDIANMEDIUM, 30, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::INDIANMEDIUM, 45, 100);


		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 80);
		green2 = false;
	}
	


	if (App->player->hp == 0){
		App->fade->FadeToBlack(App->level2, App->victoryscreen, 2);
	}
	if (App->enemies->hits >= 10){
		App->player->current_animation = &(App->player->dance);
		App->player->status = WIN;
		App->audio->Load("Music/victory.ogg");
		App->enemies->hits = 0;
	}
	

	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->level2, App->victoryscreen, 2);
	}
	return UPDATE_CONTINUE;
}