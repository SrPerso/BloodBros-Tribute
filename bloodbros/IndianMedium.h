#ifndef __INDIAN_MEDIUM_H__
#define __INDIAN_MEDIUM_H__

#include "Enemy.h"

class IndianMedium : public Enemy
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


	IndianMedium(int x, int y);

	void Move();
	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __INDIAn_MEDIUM_H__