#include "DXUT.h"
#include "Effect.h"


Effect::Effect(int type)
	:type(type)
{
	if (type == 0)
	{
		ani = new Animation("image/Map/ob/ani/stone", 8, 20, false, true);
		addChild(ani);

		rect = ani->rect;
	}
}

Effect::~Effect()
{
}

void Effect::update(float dt)
{
	Entity::update(dt);

	if (ani->isFinish)
		deleting = true;
}
