#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Animation.h"

class Obstacle :
	public Entity
{
public:
	Obstacle(int type);
	~Obstacle();

	void update(float dt);

	float speed;
	float gravity;
	float timer;

	int stage; int type;
	
	Sprite* image;
	Animation* ani;

	bool already;
	bool timerOn;
	bool moveStart;
	bool re;


	float stopTimer;
};

