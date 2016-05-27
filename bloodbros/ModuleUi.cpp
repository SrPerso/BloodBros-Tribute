#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "Audio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"
#include "ModuleText.h"
#include <stdio.h>

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
	font_score = App->font->Load("Images/fonts2.png", "0123456789abcdefghijklmnopqrstuvwxyz", 1);
	UserInterface = App->textures->Load("Images/fonts.png");
	insert_coins.PushBack({ 0, 8, 59, 10 });
	insert_coins.PushBack({ 0, 0, 0, 0 });
	insert_coins.speed = 0.03f;
	insert_coins.loop = true;
	Credit.PushBack({ 59, 8, 31, 10 });
	stage.PushBack({ 91, 8, 72, 8 });
	stage.PushBack({ 254, 9, 5, 5 });
	dynamite_image.PushBack({322,0, 16, 16});
	
	oneup.PushBack({ 163, 8, 17, 9 });
	top.PushBack({ 180, 8, 17, 9 });
	foe.PushBack({ 197, 8, 31, 8 });
	foe_bar.PushBack({ 229, 8,5, 8 });
	foe_bar_white.PushBack({ 234, 8, 5, 8 });
	ball.PushBack({ 240, 8, 9, 9 });
	
	

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

	if (App->input->keyboard[SDL_SCANCODE_5] == KEY_STATE::KEY_DOWN){
		coins++;
	}
	if (App->player->score > top_score){
		top_score = App->player->score;
	}
	
	App->render->Blit(UserInterface, 98,214, &(Credit.GetCurrentFrame()), 0.0);
	
	
	App->render->Blit(UserInterface, -1, -1, &(oneup.GetCurrentFrame()), 0.0);
	App->render->Blit(UserInterface, 88, -1, &(top.GetCurrentFrame()), 0.0);

	sprintf_s(score_text, 10, "%7d", top_score);
	App->font->Blit(108, 0, font_score, score_text);

	sprintf_s(coins_text, 10, "%7d", coins);
	App->font->Blit(136, 216, font_score, coins_text);

	if (coins == 0){
		App->render->Blit(UserInterface, 165, 214, &(insert_coins.GetCurrentFrame()), 0.0);
	}
	if (App->player->IsEnabled() == true){
		App->render->Blit(UserInterface, 30, 207, &(foe.GetCurrentFrame()), 0.0);
		App->render->Blit(UserInterface, 90, 15, &(stage.GetCurrentFrame()), 0.0);
		App->render->Blit(UserInterface, 0, 185, &(dynamite_image.GetCurrentFrame()), 0.0);
		if (App->player->hp == 3){
			App->render->Blit(UserInterface, 9, 209, &(ball.GetCurrentFrame()), 0.0);
		}
		if (App->player->hp >= 2){
			App->render->Blit(UserInterface, 0, 209, &(ball.GetCurrentFrame()), 0.0);
		}
	}
	return UPDATE_CONTINUE;
}