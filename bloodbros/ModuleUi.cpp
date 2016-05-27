#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "Audio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"

#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"
#include "ModuleText.h"

ModuleUI::ModuleUI()
{
	
}
ModuleUI::~ModuleUI()
{
}
bool ModuleUI::Start()
{
	LOG("Loading intro");
	timestart = SDL_GetTicks();

	UserInterface = App->textures->Load("Images/fonts.png");
	insert_coins.PushBack({ 0, 8, 59, 8 });
	Credit.PushBack({ 59, 8, 31, 10 });
	stage.PushBack({ 91, 8, 72, 8 });
	stage.PushBack({ 254, 9, 5, 5 });
	dynamite_image.PushBack({322,0, 16, 16});
	
	oneup.PushBack({ 163, 8, 17, 8 });
	top.PushBack({ 180, 8, 17, 8 });
	foe.PushBack({ 197, 8, 31, 8 });
	foe_bar.PushBack({ 229, 8,5, 8 });
	foe_bar_white.PushBack({ 234, 8, 5, 8 });
	ball.PushBack({ 240, 8, 9, 8 });
	
	

	return true;
}
bool ModuleUI::CleanUp()
{
	LOG("Unloading intro");

	App->textures->Unload(UserInterface);
	
	return true;
}
update_status ModuleUI::Update()
{
	App->render->Blit(UserInterface, 90, 15, &(stage.GetCurrentFrame()), 0.0);
	App->render->Blit(UserInterface, 100,214, &(Credit.GetCurrentFrame()), 0.0);
	App->render->Blit(UserInterface, 90, 15, &(stage.GetCurrentFrame()), 0.0);
	App->render->Blit(UserInterface, 0, 185, &(dynamite_image.GetCurrentFrame()), 0.0);
	App->render->Blit(UserInterface, 30, 207, &(foe.GetCurrentFrame()), 0.0);
	return UPDATE_CONTINUE;
}