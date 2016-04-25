#ifndef __GREENCOWBOY_H__
#define __GREENCOWBOY_H__

#include "Enemy.h"

class GreenCowboy : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	GreenCowboy(int x, int y);

	void Move();
};

#endif // __GREENCOWBOY_H__