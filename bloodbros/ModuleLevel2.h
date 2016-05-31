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
	bool win = false;

	bool ole1 = true;
	bool ole1b = true;
	bool ole1c = true;
	bool ole2 = true;
	bool ole3 = true;
	bool ole4 = true;
	bool ole4b = true;
	bool ole5 = true;
	bool ole6 = true;
	bool ole7 = true;
	bool ole8 = true;
	bool ole8b = true;
	bool ole9 = true;
	bool ole9b = true;
	bool ole9c = true;
	bool ole10 = true;
	bool ole11 = true;
	bool ole12 = true;
	bool ole12b = true;
	bool ole12c = true;
	bool ole12d = true;
	bool ole13 = true;
	bool ole14 = true;
	bool ole14b = true;
	bool ole14c = true;
	bool ole14d = true;

	bool extra = true;
	bool plane = true;
	bool greencowboy = true;
	bool greencowboyb = true;
	bool bluecowboy = true;
	bool bluecowboyb = true;
	bool bluecowboyc = true;
	bool bluecowboyd = true;
	bool buildings = true;
	bool green2 = true;
	bool plane2 = true;
	bool jumper = true;
	

	bool greencowboymedium = true;
	bool IndianMedium = true;
	bool GreenCowBoyLeavingTheHouse = true;

	/////////////////// 2nd Wave

	bool secole1 = true;
	bool secole1b = true;
	bool secole1c = true;
	bool secole2 = true;
	bool secole3 = true;
	bool secole4 = true;
	bool secole4b = true;
	bool secole5 = true;
	bool secole6 = true;
	bool secole7 = true;
	bool secole8 = true;
	bool secole8b = true;
	bool secole9 = true;
	bool secole9b = true;
	bool secole9c = true;
	bool secole10 = true;

	bool secextra = true;
	bool secplane = true;
	bool secgreencowboy = true;
	bool secbluecowboy = true;
	bool secbluecowboyb = true;
	bool secbluecowboyc = true;
	bool secbluecowboyd = true;
	bool secbuildings = true;
	bool secgreen2 = true;
	bool secplane2 = true;
	bool secjumper = true;


	bool secgreencowboymedium = true;
	bool secIndianMedium = true;
	bool secGreenCowBoyLeavingTheHouse = true;

public:

	SDL_Texture* graphics = nullptr;
	uint timestart;
	SDL_Rect background;
};

#endif // __MODULELEVEL2_H__