#ifndef __JUMPERSHOOT_H__
#define __JUMPERSHOOT_H__

#include "Enemy.h"

class Jumpershoot : public Enemy
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


	Jumpershoot(int x, int y);

	void Move();
	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __JUMPERSHOOT_H__