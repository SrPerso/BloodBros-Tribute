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
#include "ModuleVictory.h"
#include "ModuleText.h"
#include "ModuleLevel2.h"
#include "ModuleEnemies.h"
#include "ModuleEnemiesFront.h"
#include "ModuleEnemiesMid.h"
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
	foe_bar.PushBack({ 229, 8,5, 10 });
	foe_bar_white.PushBack({ 234, 8, 5, 10 });
	ball.PushBack({ 240, 8, 9, 9 });
	
	for (uint i = 0; i < 19; i++){
		scorelist[i] = 0;
	}

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
		App->audio->Loadfx("Music/insertcoin.ogg");
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
	if (App->level2->IsEnabled() == true && stagedisplay==false){
		timestart = SDL_GetTicks() + 4000;
		stagedisplay = true;
		
	}
	if (timestart > SDL_GetTicks()){
		App->render->Blit(UserInterface, 90, 15, &(stage.GetCurrentFrame()), 0.0);
	}
	if (App->player->IsEnabled() == true){
		App->render->Blit(UserInterface, 30, 206, &(foe.GetCurrentFrame()), 0.0);
		App->render->Blit(UserInterface, 0, 185, &(dynamite_image.GetCurrentFrame()), 0.0);
		if (App->player->hp == 3){
			App->render->Blit(UserInterface, 9, 209, &(ball.GetCurrentFrame()), 0.0);
		}
		if (App->player->hp >= 2){
			App->render->Blit(UserInterface, 0, 209, &(ball.GetCurrentFrame()), 0.0);
		}
	}
	if (App->victoryscreen->IsEnabled() == true){
		uint j = 0;
		for (uint i = 0; i < 19; i++){
			sprintf_s(scorelist_tex, 10, "%7d", scorelist[i]);
			App->font->Blit(120, 31+j, font_score, scorelist_tex);
			j += 9;
		}
	}


	//FOE BAR
	if (App->level2->IsEnabled() == true){
		if (App->enemies->hits + App->front->hits + App->mid->hits < 48){
			App->render->Blit(UserInterface, 62, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 62, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 44){
			App->render->Blit(UserInterface, 66, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 66, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 40){
			App->render->Blit(UserInterface, 70, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 70, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 36){
			App->render->Blit(UserInterface, 74, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 74, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 32){
			App->render->Blit(UserInterface, 78, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 78, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 28){
			App->render->Blit(UserInterface, 82, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 82, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 24){
			App->render->Blit(UserInterface, 86, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 86, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 20){
			App->render->Blit(UserInterface, 90, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 90, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 16){
			App->render->Blit(UserInterface, 94, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 94, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 12){
			App->render->Blit(UserInterface, 98, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 98, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 8){
			App->render->Blit(UserInterface, 102, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 102, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 4){
			App->render->Blit(UserInterface, 106, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 106, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
		if (App->enemies->hits + App->front->hits + App->mid->hits <= 0){
			App->render->Blit(UserInterface, 110, 205, &(foe_bar.GetCurrentFrame()), 0.0);
		}
		else{
			App->render->Blit(UserInterface, 110, 205, &(foe_bar_white.GetCurrentFrame()), 0.0);
		}
	}
	
	return UPDATE_CONTINUE;
}

void ModuleUI::UpdateScore(){
	for (uint i = 0; i < 19; i++){
		if (App->player->score>scorelist[i]){
			for (uint j = 19; j > i; j--){
				scorelist[j] = scorelist[j-1];
			}
			scorelist[i] = App->player->score;
			stagedisplay = false;
			return;
		}
	}
}