#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// Background / sky
	background.x = 15;
	background.y = 15;
	background.w = 513;
	background.h = 445;

	//CowBoy
	cowboy.x = 541;
	cowboy.y = 15;
	cowboy.w = 47;
	cowboy.h = 130;



}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("spritesheet_lvl1.png");
	
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0);
	App->render->Blit(graphics, 230, 300, &cowboy, 0);

	
	

	return UPDATE_CONTINUE;
}