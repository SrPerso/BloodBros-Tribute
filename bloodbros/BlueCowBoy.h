#ifndef __BLUECOWBOY_H__
#define __BLUECOWBOY_H__

#include "Enemy.h"

class BlueCowboy : public Enemy
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
	bool isdead = false;


public:


	BlueCowboy(int x, int y);

	void Move();
	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __BLUECOWBOY_H__