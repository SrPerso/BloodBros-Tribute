#ifndef __PURPLEPLANE_H__
#define __PURPLEPLANE_H__

#include "Enemy.h"

class PurplePlane : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint original_pos;
	Animation fly;
	Animation fly2;


public:

	PurplePlane(int x, int y);

	void Move();
};

#endif // __PURPLEPLANE_H__