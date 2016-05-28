#ifndef __INDIAN_LEAVING_H__
#define __INDIAN_LEAVING_H__

#include "Enemy.h"

class IndianLeavingTheHouse : public Enemy
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
	Animation appear;
	Animation jump;
	bool isdead = false;


public:


	IndianLeavingTheHouse(int x, int y);

	void Move();
	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __INDIAN_LEAVING_H__