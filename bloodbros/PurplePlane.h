#ifndef __PURPLEPLANE_H__
#define __PURPLEPLANE_H__

#include "Enemy.h"

class PurplePlane : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	PurplePlane(int x, int y);

	void Move();
};

#endif // __PURPLEPLANE_H__