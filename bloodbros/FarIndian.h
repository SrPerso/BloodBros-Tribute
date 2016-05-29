#ifndef __INDIAN_FAR_H__
#define __INDIAN_FAR_H__

#include "Enemy.h"

class FarIndian : public Enemy
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


	FarIndian(int x, int y);

	void Move();
	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __FARINDIAn_H__