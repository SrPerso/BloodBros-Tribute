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
	ole1 = true;
	ole2 = true;
	ole3 = true;
	ole4 = true;
	ole5 = true;
	ole6 = true;
	ole7 = true;
	ole8 = true;
	ole9 = true;
	ole10 = true;
	win = false;
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
	App->building->AddBuilding(App->building->trees, -25, 30);
	App->building->AddBuilding(App->building->trees, 15, 30);
	App->building->AddBuilding(App->building->trees, 55, 30);
	App->building->AddBuilding(App->building->trees, 196, 30);
	App->building->AddBuilding(App->building->trees, 162, 30);
	App->building->AddBuilding(App->building->trees, 230, 30);
	App->building->AddBuilding(App->building->yellow, 160, 30);
	App->building->AddBuilding(App->building->purple, 0, 53);
	App->enemies->hits = 0;
	App->front->hits = 0;
	App->mid->hits = 0;
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
	App->mid->Disable();
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
	
	
	if (App->building->yellowalive == false && App->building->purplealive == false && SDL_GetTicks() >= timestart + 10000 && ole11==true ){
		App->mid->AddEnemy(ENEMY_TYPES3::FARGREEN, 230, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARGREEN2, 0, 70);
		ole11 = false;
	}
	if (App->building->yellowalive == false && App->building->purplealive == false && SDL_GetTicks() >= timestart + 14000 && ole12 == true){
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN, 230, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN, 222, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN, 214, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN, 206, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN2, 0, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN2, 8, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN2, 16, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN2, 24, 70);
		ole12 = false;
	}
	//////////////// 5 cowboys from left dist 2 first wave
	if (SDL_GetTicks() >= timestart + 6000 && ole1 == true){
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -15, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -30, 80);
		ole1 = false;
	}

	if (SDL_GetTicks() >= timestart + 6090 && ole1b == true){
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -45, 80);
		ole1b = false;
	}
	if (SDL_GetTicks() >= timestart + 6120 && ole1c == true){
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, 0, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -60, 80);
		ole1c = false;
	}
	//////////////// cowboy from left house dist 3 

	if (SDL_GetTicks() >= timestart + 10000 && ole2 == true){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 58, 80);		
		ole2 = false;
	}
	//////////////// cowboys from right house dist 2 

	if (SDL_GetTicks() >= timestart + 13750 && ole3 == true && App->building->yellowalive == true){
		App->front->AddEnemy(ENEMY_TYPES2::GREENLEAVINGCOWBOY, 215, 90);	
		ole3 = false;
	}
	else if (SDL_GetTicks() >= timestart + 13750 && ole3 == true && App->building->yellowalive == false){
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYJUMPERLEFT, 215, 80);
		ole3 = false;
	}
	if (SDL_GetTicks() >= timestart + 14000 && ole4 == true && App->building->yellowalive == true){
		App->front->AddEnemy(ENEMY_TYPES2::GREENLEAVINGCOWBOY, 225, 90);
		
		ole4 = false;
	}
<<<<<<< HEAD
	
=======
	else if (SDL_GetTicks() >= timestart + 14000 && ole4 == true && App->building->yellowalive == false){
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYJUMPERRIGTH, 225, 80);
		ole4 = false;
	}
>>>>>>> origin/master

	//////////////// cowboy from right house dist 3 

	if (SDL_GetTicks() >= timestart + 16000 && ole4b == true && App->building->yellowalive == true){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENRIGHTCOWBOY, 164, 80);
		ole4b = false;
	}

	//////////////// JUMPing cowboys from windmill dist 2 and both pigs (and charriot)

	if (SDL_GetTicks() >= timestart + 18000 && ole5 == true){
		App->extra->AddExtra(App->extra->pig, -30, 140);
		App->extra->AddExtra(App->extra->blackpig, 270, 140);
		App->front->AddEnemy(ENEMY_TYPES2::JUMPER, 20, 100);

		ole5 = false;
	}
	if (SDL_GetTicks() >= timestart + 18500 && ole6 == true){

		App->front->AddEnemy(ENEMY_TYPES2::JUMPERSHOOT, 35, 100);

		ole6 = false;
	}
	if (SDL_GetTicks() >= timestart +19000 && ole7== true){
		
		App->front->AddEnemy(ENEMY_TYPES2::JUMPER, 50, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 67);
		App->extra->AddExtra(App->extra->cask, -80, 130);

		ole7 = false;
	}
	if (SDL_GetTicks() >= timestart + 19500 && ole8 == true){

		App->front->AddEnemy(ENEMY_TYPES2::JUMPERSHOOT, 65, 100);
		App->extra->AddExtra(App->extra->zepe, 315, 28);

		ole8 = false;
	}

	if (App->building->yellowalive == false && App->building->purplealive == false && SDL_GetTicks() >= timestart + 30000 && ole13 == true){
		App->mid->AddEnemy(ENEMY_TYPES3::FARGREEN, 230, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARGREEN2, 0, 70);
		ole13 = false;
	}
	if (App->building->yellowalive == false && App->building->purplealive == false && SDL_GetTicks() >= timestart + 34000 && ole14 == true){
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN, 230, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN, 222, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN, 214, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN, 206, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN2, 0, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN2, 8, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN2, 16, 70);
		App->mid->AddEnemy(ENEMY_TYPES3::FARINDIAN2, 24, 70);
		ole14 = false;
	}

	//////////////// ROLLING BARREL FROM RIGHT TO LEFT
	if (SDL_GetTicks() >= timestart + 24500 && ole8b == true){

		App->extra->AddExtra(App->extra->cask2, 240, 130);

		ole8b = false;
	}

	
	//////////////// 5 indians from left dist 2 first wave

	if (SDL_GetTicks() >= timestart + 28000 && ole9 == true){
		App->mid->AddEnemy(ENEMY_TYPES3::INDIANMEDIUM, -15, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::INDIANMEDIUM, -30, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::INDIANMEDIUM, -60, 80);
		ole9 = false;
	}
	if (SDL_GetTicks() >= timestart + 28090 && ole9b == true){
		App->mid->AddEnemy(ENEMY_TYPES3::INDIANMEDIUM, -45, 80);
		ole9b = false;
	}
	if (SDL_GetTicks() >= timestart + 28130 && ole9c == true){
		App->mid->AddEnemy(ENEMY_TYPES3::INDIANMEDIUM, 0, 80);
		ole9c = false;
	}

	//////////////// indian from left house dist 3 

	if (SDL_GetTicks() >= timestart + 30070 && ole10 == true){

		App->enemies->AddEnemy(ENEMY_TYPES::INDIANLAST, 58, 68);
		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 67);

		ole10 = false;
	}

	//////////////// PLANE
	if (SDL_GetTicks() >= timestart + 31040 && plane == true){
		App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 70, -20);
		plane = false;
	}
		
	//////////////// BLUE INDIANS dist 4(and right indian dist 3)
	if (SDL_GetTicks() >= timestart + 34000 && bluecowboy == true){
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 50, 62);
		App->enemies->AddEnemy(ENEMY_TYPES::INDIANLAST2, 164, 68);
		bluecowboy = false;
	}

	if (SDL_GetTicks() >= timestart + 34100 && bluecowboyb == true){		
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 60, 62);
		bluecowboyb = false;
	}
	if (SDL_GetTicks() >= timestart + 34200 && bluecowboyc == true){
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 70, 62);
		bluecowboyc = false;
	}
	if (SDL_GetTicks() >= timestart + 34300 && bluecowboyd == true){
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 80, 62);
		bluecowboyd = false;
	}



	if (SDL_GetTicks() >= timestart + 38400 && greencowboy == true && App->building->purplealive == true){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 58, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 67);
		App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 70, -20);
		greencowboy = false;
	}

	if (SDL_GetTicks() >= timestart + 42400 && greencowboyb == true){
		App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 70, -20);
		greencowboyb = false;
	}

	////////////// 2nd WAVE, ALL

	//////////////// 5 cowboys from left dist 2 first wave

	if (SDL_GetTicks() >= timestart + 46000 && secole1 == true){
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -15, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -30, 80);
		secole1 = false;
	}

	if (SDL_GetTicks() >= timestart + 46090 && secole1b == true){
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -45, 80);
		secole1b = false;
	}
	if (SDL_GetTicks() >= timestart + 46120 && secole1c == true){
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, 0, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::GREENCOWBOYMEDIUM, -60, 80);
		secole1c = false;
	}
	//////////////// cowboy from left house dist 3 

	if (SDL_GetTicks() >= timestart + 50000 && secole2 == true){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 58, 80);
		secole2 = false;
	}
	//////////////// cowboys from right house dist 2 

	if (SDL_GetTicks() >= timestart + 53750 && secole3 == true && App->building->yellowalive == true){
		App->front->AddEnemy(ENEMY_TYPES2::GREENLEAVINGCOWBOY, 215, 90);
		secole3 = false;
	}

	if (SDL_GetTicks() >= timestart + 54000 && secole4 == true && App->building->yellowalive == true){
		App->front->AddEnemy(ENEMY_TYPES2::GREENLEAVINGCOWBOY, 225, 90);
		secole4 = false;
	}

	//////////////// cowboy from right house dist 3 

	if (SDL_GetTicks() >= timestart + 56000 && secole4b == true && App->building->yellowalive == true){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENRIGHTCOWBOY, 164, 80);
		secole4b = false;
	}

	//////////////// JUMPing cowboys from windmill dist 2 and both pigs (and charriot)

	if (SDL_GetTicks() >= timestart + 58000 && secole5 == true){
		App->extra->AddExtra(App->extra->pig, -30, 140);
		App->extra->AddExtra(App->extra->blackpig, 270, 140);
		App->front->AddEnemy(ENEMY_TYPES2::JUMPER, 20, 100);

		secole5 = false;
	}
	if (SDL_GetTicks() >= timestart + 58500 && secole6 == true){

		App->front->AddEnemy(ENEMY_TYPES2::JUMPERSHOOT, 35, 100);

		secole6 = false;
	}
	if (SDL_GetTicks() >= timestart + 59000 && secole7 == true){
		App->extra->AddExtra(App->extra->cask, -80, 130);
		App->front->AddEnemy(ENEMY_TYPES2::JUMPER, 50, 100);
		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 67);

		secole7 = false;
	}
	if (SDL_GetTicks() >= timestart + 59500 && secole8 == true){

		App->front->AddEnemy(ENEMY_TYPES2::JUMPERSHOOT, 65, 100);
		App->extra->AddExtra(App->extra->zepe, 315, 28);

		secole8 = false;
	}


	//////////////// ROLLING BARREL FROM RIGHT TO LEFT
	if (SDL_GetTicks() >= timestart + 64500 && secole8b == true){

		App->extra->AddExtra(App->extra->cask2, 240, 130);

		secole8b = false;
	}


	//////////////// 5 indians from left dist 2 first wave

	if (SDL_GetTicks() >= timestart + 68000 && secole9 == true){
		App->mid->AddEnemy(ENEMY_TYPES3::INDIANMEDIUM, -15, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::INDIANMEDIUM, -30, 80);
		App->mid->AddEnemy(ENEMY_TYPES3::INDIANMEDIUM, -60, 80);
		secole9 = false;
	}
	if (SDL_GetTicks() >= timestart + 68090 && secole9b == true){
		App->mid->AddEnemy(ENEMY_TYPES3::INDIANMEDIUM, -45, 80);
		secole9b = false;
	}
	if (SDL_GetTicks() >= timestart + 68130 && secole9c == true){
		App->mid->AddEnemy(ENEMY_TYPES3::INDIANMEDIUM, 0, 80);
		secole9c = false;
	}

	//////////////// indian from left house dist 3 

	if (SDL_GetTicks() >= timestart + 70070 && secole10 == true){

		App->enemies->AddEnemy(ENEMY_TYPES::INDIANLAST, 58, 68);

		secole10 = false;
	}

	//////////////// PLANE
	if (SDL_GetTicks() >= timestart + 71040 && secplane == true){
		App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 70, -20);
		secplane = false;
	}

	//////////////// BLUE INDIANS dist 4(and right indian dist 3)
	if (SDL_GetTicks() >= timestart + 74000 && secbluecowboy == true){
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 50, 62);
		App->enemies->AddEnemy(ENEMY_TYPES::INDIANLAST2, 164, 68);
		secbluecowboy = false;
	}

	if (SDL_GetTicks() >= timestart + 74100 && secbluecowboyb == true){
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 60, 62);
		secbluecowboyb = false;
	}
	if (SDL_GetTicks() >= timestart + 74200 && secbluecowboyc == true){
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 70, 62);
		secbluecowboyc = false;
	}
	if (SDL_GetTicks() >= timestart + 74300 && secbluecowboyd == true){
		App->enemies->AddEnemy(ENEMY_TYPES::BLUECOWBOY, 80, 62);
		secbluecowboyd = false;
	}



	if (SDL_GetTicks() >= timestart + 78400 && secgreencowboy == true && App->building->purplealive == true){
		App->enemies->AddEnemy(ENEMY_TYPES::GREENCOWBOY, 58, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::CHARRIOT, 220, 67);
		App->enemies->AddEnemy(ENEMY_TYPES::PURPLEPLANE, 70, -20);
		secgreencowboy = false;
	}

	if (SDL_GetTicks() >= timestart + 78400){
		timestart = SDL_GetTicks();
		ole1 = true;
		ole1b = true;
		ole1c = true;
		ole2 = true;
		ole3 = true;
		ole4 = true;
		ole4b = true;
		ole5 = true;
		ole6 = true;
		ole7 = true;
		ole8 = true;
		ole8b = true;
		ole9 = true;
		ole9b = true;
		ole9c = true;
		ole10 = true;

		extra = true;
		plane = true;
		greencowboy = true;
		greencowboyb = true;
		bluecowboy = true;
		bluecowboyb = true;
		bluecowboyc = true;
		bluecowboyd = true;
		buildings = true;
		green2 = true;
		plane2 = true;
		jumper = true;


		greencowboymedium = true;
		IndianMedium = true;
		GreenCowBoyLeavingTheHouse = true;

		/////////////////// 2nd Wave

		 secole1 = true;
		 secole1b = true;
		 secole1c = true;
		 secole2 = true;
		 secole3 = true;
		 secole4 = true;
		 secole4b = true;
		 secole5 = true;
		 secole6 = true;
		 secole7 = true;
		 secole8 = true;
		 secole8b = true;
		 secole9 = true;
		secole9b = true;
		secole9c = true;
		secole10 = true;

		secextra = true;
		secplane = true;
		secgreencowboy = true;
		secbluecowboy = true;
		secbluecowboyb = true;
		secbluecowboyc = true;
		secbluecowboyd = true;
		secbuildings = true;
		 secgreen2 = true;
		secplane2 = true;
		secjumper = true;


		secgreencowboymedium = true;
		secIndianMedium = true;
		secGreenCowBoyLeavingTheHouse = true;
	}

	

	//////////////////////////////////////////////////////////////////////////////////////////////////

	if (App->player->hp <= 0){
		App->fade->FadeToBlack(App->level2, App->victoryscreen, 2);
	}
	//WIN CONDITION
	if (App->enemies->hits+App->front->hits+App->mid->hits == 48 && win==false){
		win = true;
		App->player->current_animation = &(App->player->dance);
		App->player->status = WIN;
		App->audio->Load("Music/victory.ogg");
	
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

	if (App->input->keyboard[SDL_SCANCODE_F9] == 1)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::INDIANLAST, 0, 80);
		App->enemies->AddEnemy(ENEMY_TYPES::INDIANLAST2, 170, 80);
	}


	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->level2, App->victoryscreen, 2);
	}
	return UPDATE_CONTINUE;
}