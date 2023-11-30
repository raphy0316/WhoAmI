#pragma once
#include "Entity.h"
#include "Text.h"

class Coin :
	public Entity
{
public:
	Coin(int askii);
	~Coin();

	int askii;
	int percent;
	char english[1];
	Text* text;

	void update(float dt);
};

