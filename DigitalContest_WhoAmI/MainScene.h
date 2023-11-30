#pragma once
#include "Scene.h"
#include "Sprite.h"

class MainScene :
	public Scene
{
public:
	MainScene();
	~MainScene();

	Sprite* image;
	Sprite* image2;


	void update(float dt);

	bool alpha;
};


