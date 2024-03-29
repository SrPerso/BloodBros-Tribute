#ifndef __GREENCOWBOY_FAR_H__
#define __GREENCOWBOY_FAR_H__

#include "Enemy.h"

class FarGreenCowBoy : public Enemy
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


	FarGreenCowBoy(int x, int y);

	void Move();
	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __GREENCOWBOY_H__