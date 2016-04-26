#ifndef __CHARRIOT_H__
#define __CHARRIOT_H__

#include "Enemy.h"

class Enemy_Charriot : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_Charriot(int x, int y);

	void Move();
	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __ENEMY_CHARRIOT_H__