#pragma once
#include "Scene.h"
#include "Sprite.h"
class TestScene
	:public Scene
{
public:
	TestScene(void);
	~TestScene(void);

	void update(float dt);

	Sprite* sprite;

	int flag;
};

