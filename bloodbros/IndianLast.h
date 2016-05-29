#ifndef __INDIANLAST_H__
#define __INDIANLAST_H__

#include "Enemy.h"

class IndianLast : public Enemy
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


	IndianLast(int x, int y);

	void Move();
	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __INDIANLAST_H__