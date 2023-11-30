#pragma once
#include "Entity.h"
#include "Sprite.h"
class Particle :
	public Entity
{
public:
	Particle(int type);
	~Particle();

	void update(float dt);

	int type;
	float randomSpeed;
	float radomAlpha;
	float decreaseAlpha;
	float moveAngle;
	
	Sprite* image;
	D3DXCOLOR randomColor;
};

