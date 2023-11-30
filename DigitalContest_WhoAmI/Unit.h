#pragma once
#include "Entity.h"
class Unit :
	public Entity
{
public:
	Unit();
	~Unit();

	void update(float dt);
	
	float hp;
	float speed;
	float damage;

};

