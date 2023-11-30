#include "DXUT.h"
#include "Particle.h"
#include "GameScene.h"
#include "World.h"

Particle::Particle(int type)
	:type(type)
{
	image = new Sprite("image/Particle/" + to_string(type) + ".png");
	addChild(image);

	if (type == 0)
	{
		scale *= random(0.5f, 1.2f);

		randomSpeed = 130;
		decreaseAlpha = 1;
	}

	if (type == 1)
	{
		scale *= random(0.3f, 0.5f);

		randomSpeed = 100;
		decreaseAlpha = 3;
	}

	if (type == 2)
	{
		scale *= random(0.1f, 1.2f);

		randomSpeed = random(50, 200);
		decreaseAlpha = random(0.3f ,0.7f);
		image->color.a = random(0.2f, 1.0f);
		image->blending = true;

	}

	rect = image->rect;
	scaleCenter = rect.center();
	rotationCenter = rect.center();

}


Particle::~Particle()
{
}

void Particle::update(float dt)
{
	Entity::update(dt);

	if (type == 0)
	{
		pos += Vec2(cos(moveAngle), sin(moveAngle)) * randomSpeed * dt;
		if (image->color.a <= 0)
			deleting = true;

		image->color.a -= dt * decreaseAlpha;

		if (image->color.a <= 0.5f)
		{
			image->color.r = randomColor.r;
			image->color.g = randomColor.g;
			image->color.b = randomColor.b;

		}
	}

	if (type == 1)
	{
		pos += Vec2(cos(moveAngle), sin(moveAngle)) * randomSpeed * dt;
		if (image->color.a <= 0)
			deleting = true;

		image->color.a -= dt * decreaseAlpha;
	}

	if (type == 2) {

		image->color.a -= dt * decreaseAlpha;

		pos.y -= randomSpeed * dt;
		if (image->color.a <= 0)
			deleting = true;
	}

	
	
	

	
}
