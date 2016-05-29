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
#include "ModuleEnemiesFront.h"
#include "ModuleBuildings2.h"
#include "ModuleEnemiesMid.h"

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
	App->player->Enable();
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
	
	App->audio->Enable();
	App->audio->Load("Music/level.ogg");
	App->particles->Enable();
	App->scope->Enable();
	App->front->Enable();
	
	App->building->Enable();
	App->building2->Enable();

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

	App->building2->AddBuilding2(App->building2->mill, 30, 74);

	App->building->AddBuilding(App->building->rock, 154, 150);

	App->ui->Enable();
	App->input->Enable();
	return ret;
}

// Load assets
bool ModuleLevel2::CleanUp()
{
	LOG("Unloading level 2");
	App->ui->UpdateScore();
	App->player->Disable();
	App->audio->Disable();
	App->scope->Disable();
	App->enemies->Disable();
	App->front->Disable();
	App->building->Disable();
	App->building2->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->extra->Disable();
	return true;
}

// Update: draw background
update_status ModuleLevel2::Update()
{
	// Draw everything --------------------------------------	

	App->render->Blit(graphics, 0, 0, &background, 0); // level 2
	App->ui->Update();


	if (SDL_GetTicks() >= timestart + 3000 && ole1 == true){

		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, 0, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -15, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -30, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -45, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -60, 80);
		

		ole1 = false;
	}
	/*if (SDL_GetTicks() >= timestart + 3300 && ole2 == true){
	
	App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 58, 80);		

		ole2 = false;
	}

	

	if (SDL_GetTicks() >= timestart+10000 && extra == true){
		App->extra->AddExtra(App->extra->pig, 0, 140);
		App->extra->AddExtra(App->extra->blackpig, 224, 140);
		App->extra->AddExtra(App->extra->zepe, 224, 35);
		extra = false;
	}
	if (SDL_GetTicks() >= timestart + 5000 && plane == true){
		App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 70,-20);
		
		App->extra->AddExtra(App->extra->cask, 0, 130);
		App->extra->AddExtra(App->extra->cask2, 230, 130);
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
		App->front->AddEnemy(ENEMY_TYPES2::JUMPER, 20, 100);
		App->front->AddEnemy(ENEMY_TYPES2::JUMPERSHOOT, 35, 100);
		App->front->AddEnemy(ENEMY_TYPES2::JUMPER, 50, 100);
		App->front->AddEnemy(ENEMY_TYPES2::JUMPERSHOOT, 65, 100);
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
		
		App->front->AddEnemy(ENEMY_TYPES2::GREENCOWBOYMEDIUM, 0, 100);
		App->front->AddEnemy(ENEMY_TYPES2::GREENCOWBOYMEDIUM, 15, 100);
		App->front->AddEnemy(ENEMY_TYPES2::GREENCOWBOYMEDIUM, 30, 100);
		App->front->AddEnemy(ENEMY_TYPES2::GREENCOWBOYMEDIUM, 45, 100);
		App->front->AddEnemy(ENEMY_TYPES2::GREENCOWBOYMEDIUM, 60, 100);

		plane2 = false;
	}
	if (SDL_GetTicks() >= timestart + 20000 && green2 == true && App->building->purplealive == true){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 58, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 80);

		App->front->AddEnemy(ENEMY_TYPES2::INDIANMEDIUM, 00, 100);
		App->front->AddEnemy(ENEMY_TYPES2::INDIANMEDIUM, 15, 100);
		App->front->AddEnemy(ENEMY_TYPES2::INDIANMEDIUM, 30, 100);
		App->front->AddEnemy(ENEMY_TYPES2::INDIANMEDIUM, 45, 100);		
		green2 = false;

	}
	else if (SDL_GetTicks() >= timestart + 20000 && green2 == true && App->building->purplealive == false){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 0, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 10, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 20, 80);

		App->front->AddEnemy(ENEMY_TYPES2::INDIANMEDIUM, 00, 100);
		App->front->AddEnemy(ENEMY_TYPES2::INDIANMEDIUM, 15, 100);
		App->front->AddEnemy(ENEMY_TYPES2::INDIANMEDIUM, 30, 100);
		App->front->AddEnemy(ENEMY_TYPES2::INDIANMEDIUM, 45, 100);


		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 80);
		green2 = false;
	}
	
	*/

	if (App->player->hp <= 0){
		App->fade->FadeToBlack(App->level2, App->victoryscreen, 2);
	}
	if (App->enemies->hits >= 10){
		App->player->current_animation = &(App->player->dance);
		App->player->status = WIN;
		App->audio->Load("Music/victory.ogg");
		App->enemies->hits = 0;
	
	}



	if (App->input->keyboard[SDL_SCANCODE_F3] == 1)
	{
		App->front->AddEnemy(ENEMY_TYPES2::GREENLEAVINGCOWBOY, 215, 90);
		App->front->AddEnemy(ENEMY_TYPES2::GREENLEAVINGCOWBOY, 225, 90);
	}


	if (App->input->keyboard[SDL_SCANCODE_F4] == 1)
	{
		App->front->AddEnemy(ENEMY_TYPES2::INDIANLEAVING, 215, 90);
		App->front->AddEnemy(ENEMY_TYPES2::INDIANLEAVING, 225, 90);
	}


	if (App->input->keyboard[SDL_SCANCODE_F5] == 1)
	{
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYJUMPERLEFT, 210, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYJUMPERRIGTH, 220, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYJUMPERRIGTH, 230, 80);
	}

	if (App->input->keyboard[SDL_SCANCODE_F6] == 1)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 80);
	}

	if (App->input->keyboard[SDL_SCANCODE_F7] == 1)
	{
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN, 230, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN2, 0, 70);
	}

	if (App->input->keyboard[SDL_SCANCODE_F8] == 1)
	{
		App->mid->AddEnemy(ENEMY_TYPES3::FARGREEN, 230, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARGREEN2, 0, 70);
	}




	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->level2, App->victoryscreen, 2);
	}
	return UPDATE_CONTINUE;
}