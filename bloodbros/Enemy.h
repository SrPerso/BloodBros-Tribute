#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Path.h"

#define MAX_ENEMIES 20

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation* animation;
	Collider* collider;


public:
	iPoint position;
	Path path;
	bool to_delete = false;
public:
	Enemy(int x, int y);
	virtual ~Enemy();
	
	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* c1, Collider* c2);
};

#endif // __ENEMY_H__