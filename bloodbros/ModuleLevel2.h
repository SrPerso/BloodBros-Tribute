#ifndef __MODULELEVEL2_H__
#define __MODULELEVEL2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleLevel2 : public Module
{
public:
	ModuleLevel2();
	~ModuleLevel2();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool extra = true;
	bool plane = true;
	bool greencowboy = true;
	bool bluecowboy = true;
	bool buildings = true;
	bool green2 = true;
	bool plane2 = true;
	bool jumper = true;
	bool greencowboymedium = true;
	bool IndianMedium = true;
	bool GreenCowBoyLeavingTheHouse = true;


public:

	SDL_Texture* graphics = nullptr;
	uint timestart;
	SDL_Rect background;
};

#endif // __MODULELEVEL2_H__