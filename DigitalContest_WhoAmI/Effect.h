#pragma once
#include "Entity.h"
#include "Animation.h"
class Effect :
	public Entity
{
public:
	Effect(int type);
	~Effect();

	void update(float dt);

	int type;

	Animation* ani;
};

