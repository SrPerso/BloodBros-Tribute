#ifndef __JUMPER2LEFT_H__
#define __JUMPER2LEFT_H__

#include "Enemy.h"

class Jumper2left : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	iPoint original_pos;
	Animation left;
	Animation right;
	Animation dead;
	Animation shot;
	Animation shotidle;
	Animation jump;
	bool isdead = false;


public:


	Jumper2left(int x, int y);

	void Move();
	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __JUMPER2LEFT_H__