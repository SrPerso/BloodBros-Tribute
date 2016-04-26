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

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = audio = new ModuleAudio();
	modules[5] = level1 = new ModuleLevel1();
	modules[6] = level2 = new ModuleLevel2();
	modules[7] = victoryscreen = new ModuleVictory();
	modules[8] = titlescreen = new ModuleTitleScreen();
	modules[9] = extra = new ModuleExtra();
	modules[10] = enemies = new ModuleEnemies();
	modules[11] = building = new ModuleBuilding();
	modules[12] = player = new ModulePlayer();
	modules[13] = fade = new ModuleFadeToBlack();
	modules[14] = particles = new ModuleParticles();
	modules[15] = collision = new ModuleCollision();
	modules[16] = scope = new ModuleScope();


	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;
	player->Disable();
	level1->Disable();
	level2->Disable();
	victoryscreen->Disable();
	scope->Disable();

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