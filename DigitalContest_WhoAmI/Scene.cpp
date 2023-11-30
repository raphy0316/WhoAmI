#include "DXUT.h"
#include "Scene.h"


Scene::Scene(void)
	:followTarget(nullptr), offset(0, 0)
{
}


Scene::~Scene(void)
{
}

void Scene::follow(Entity* target, Vec2 offset)
{
	this->followTarget = target;
	this->offset = offset;
}

void Scene::unfollow()
{
	this->followTarget = nullptr;
	this->offset = Vec2(0, 0);
}

void Scene::shake(int n, float range, float duration)
{
	shakeTimer.reset(duration, n, true);
	shakeTimer.onTick = [=]()
	{
		pos = pos + Vec2(random(-range, range), random(-range, range));
	};
}

void Scene::update(float dt)
{
	Entity::update(dt);
	
	Vec2 targetPos = Vec2(0, 0);

	if(followTarget)
	{
		targetPos = -followTarget->center();
	}
	
	pos += (targetPos + offset - pos) * 0.15;
}