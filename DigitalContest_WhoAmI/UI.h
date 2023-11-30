#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Text.h"
class UI :
	public Entity
{
public:
	UI();
	~UI();

	void update(float dt);

	Sprite* hpBar;
	Sprite* hpFrame;
	Sprite* item;
	Sprite* potion;
	Text* potionNum;
};

