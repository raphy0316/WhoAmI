#pragma once
#include "Scene.h"
#include "Sprite.h"

class LoadingScene :
	public Scene
{
public:
	LoadingScene();
	~LoadingScene();

	void update(float dt);

	Sprite* back;
	Sprite* bar;
	Sprite* frame;

	float sum;
};

