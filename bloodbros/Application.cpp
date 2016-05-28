#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "Audio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel1.h"
#include"ModuleLevel2.h"
#include "ModuleTitleScreen.h"
#include "ModuleVictory.h"
#include "ModuleParticles.h"
#include "ModuleScope.h"
#include "Extras.h"
#include "ModuleEnemies.h"
#include "ModuleBuildings.h"
#include "ModuleFonts.h"
#include "ModuleUi.h"
#include "ModuleEnemiesFront.h"
#include "ModuleBuildings2.h"
#include "ModuleEnemiesMid.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = font = new ModuleFonts(); 
	modules[5] = audio = new ModuleAudio();
	modules[6] = level1 = new ModuleLevel1();
	modules[7] = level2 = new ModuleLevel2();
	modules[8] = victoryscreen = new ModuleVictory();
	modules[9] = titlescreen = new ModuleTitleScreen();
	modules[10] = extra = new ModuleExtra();
	modules[11] = enemies = new ModuleEnemies();
	modules[12] = building = new ModuleBuilding();
	modules[13] = mid = new ModuleEnemiesMid();
	modules[14] = building2 = new ModuleBuilding2();
	modules[15] = front = new ModuleEnemiesFront();
	modules[16] = player = new ModulePlayer();
	modules[17] = fade = new ModuleFadeToBlack();
	modules[18] = particles = new ModuleParticles();
	modules[19] = collision = new ModuleCollision();
	modules[20] = scope = new ModuleScope();
	modules[21] = ui = new ModuleUI();
	


	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;
	front->Disable();
	player->Disable();
	level1->Disable();
	level2->Disable();
	victoryscreen->Disable();
	scope->Disable();
	ui->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}