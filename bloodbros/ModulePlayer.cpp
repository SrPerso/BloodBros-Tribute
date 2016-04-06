#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	cowboy.x = 0;
	cowboy.y = 0;
	cowboy.w = 22;
	cowboy.y = 60;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("cowboyback.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	App->render->Blit(graphics, 230, 300, &cowboy, 0);
	return UPDATE_CONTINUE;

}