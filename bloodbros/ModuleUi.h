#ifndef __MODULEUSERI_H__
#define __MODULEUSERI_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

#define ENEMY_GAUGE 20

struct Text;

class ModuleUI : public Module
{
public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	void UpdateScore();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* UserInterface = nullptr;
	
	Animation insert_coins;//
	Animation life_ball;
	Animation stage;
	Animation top;
	Animation oneup;
	Animation ball;
	Animation dynamite_image;
	Animation foe;
	Animation foe_bar;
	Animation foe_bar_white;
	Animation Credit;//
	Animation characterone;
	Uint32 hitpoints;
	Uint32 credit;
	Uint32 score;
	uint coins = 0;
	Uint32 dynamite = 10;
	Uint32 killcount;
	Text* credit_text;
	Text* credit_counter;
	Text* score_counter;
	Text* dynamite_counter;
	uint timestart;
	uint top_score = 20000;
	char score_text[10];
	char coins_text[10];
	char scorelist_tex[10];
	int font_score = 2;
	/*uint score2;
	uint score3;
	uint score4;
	uint score5;
	uint score6;
	uint score7;
	uint score8;
	uint score9;
	uint score10;
	uint score11;
	uint score12;
	uint score13;
	uint score14;
	uint score15;
	uint score16;
	uint score17;
	uint score18;
	uint score19;
	uint score20;*/
	uint scorelist[20];


};


#endif //__MODULEUSERI_H__