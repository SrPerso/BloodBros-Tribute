#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
#include "ModuleTitleScreen.h"
#include "ModuleVictory.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Audio.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleVictory::ModuleVictory()
{
	// Background
	victoryscreen.x = 0;
	victoryscreen.y = 0;
	victoryscreen.w = 256;
	victoryscreen.h = 224;

}

ModuleVictory::~ModuleVictory()
{}

// Load assets
bool ModuleVictory::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("scorescreen.png");

	App->audio->Enable();
	App->audio->Load("titletheme.wav");
	return ret;
}

// Load assets
bool ModuleVictory::CleanUp()
{
	LOG("Unloading title screen");
	App->player->Disable();
	App->audio->Disable();
	return true;
}

// Update: draw background
update_status ModuleVictory::Update()
{
	// Draw everything --------------------------------------	

	App->render->Blit(graphics, 0, 0, &victoryscreen, 0); // level 1
	App->player->Disable();
	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->victoryscreen, App->titlescreen, 2);
	}
	return UPDATE_CONTINUE;
}