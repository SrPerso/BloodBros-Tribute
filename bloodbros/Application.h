#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 22


class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class ModuleFonts;
class ModuleUI;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleLevel1;
class ModuleLevel2;
class ModuleTitleScreen;
class ModuleVictory;
class ModuleParticles;
class ModuleExtra;
class ModuleCollision;
class ModuleScope;
class ModuleEnemies;
class ModuleBuilding;
class ModuleBuilding2;
class ModuleEnemiesMid;
class ModuleEnemiesFront;
class Module;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleFonts* font;
	ModuleTitleScreen* titlescreen;
	ModuleLevel1* level1;
	ModuleLevel2* level2;
	ModuleVictory* victoryscreen;
	ModuleExtra* extra;

	ModuleEnemies* enemies;
	ModuleBuilding* building;
	ModuleEnemiesMid* mid;
	ModuleBuilding2* building2;

	ModulePlayer* player;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleScope* scope;
	ModuleUI* ui;

	ModuleEnemiesFront* front;
	



public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__