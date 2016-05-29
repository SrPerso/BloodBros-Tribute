#ifndef __GREENCOWBOY2_FAR_H__
#define __GREENCOWBOY2_FAR_H__

#include "Enemy.h"

class FarGreenCowBoy2: public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	iPoint original_pos;
	Animation fly;
	Animation fly2;
	Animation dead;
	Animation idle;
	bool isdead = false;


public:


	FarGreenCowBoy2(int x, int y);

	void Move();
	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __GREENCOWBOY2_H__