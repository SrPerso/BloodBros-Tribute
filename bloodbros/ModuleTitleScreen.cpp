#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
#include "ModuleTitleScreen.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Audio.h"
#include "ModuleUi.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleTitleScreen::ModuleTitleScreen()
{
	// Background
	titlescreen.x = 0;
	titlescreen.y = 0;
	titlescreen.w = 256;
	titlescreen.h = 224;

}

ModuleTitleScreen::~ModuleTitleScreen()
{}

// Load assets
bool ModuleTitleScreen::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Images/titlescreen.png");
	App->ui->Enable();
	App->audio->Enable();
	App->audio->Load("Music/titletheme.ogg");
	return ret;
}

// Load assets
bool ModuleTitleScreen::CleanUp()
{
	LOG("Unloading title screen");
	App->player->Disable();
	App->audio->Disable();
	App->input->Disable();
	App->ui->Disable();
	return true;
}

// Update: draw background
update_status ModuleTitleScreen::Update()
{
	// Draw everything --------------------------------------	

	App->render->Blit(graphics, 0, 0, &titlescreen, 0); // level 1
	App->player->Disable();
	App->level2->Disable();
	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_1] == 1 && App->ui->coins>=1)
	{
		App->ui->coins--;
		App->fade->FadeToBlack(App->titlescreen, App->level2, 2);
	}
	return UPDATE_CONTINUE;
}