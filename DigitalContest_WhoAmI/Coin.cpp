#include "DXUT.h"
#include "Coin.h"
#include "GameScene.h"
#include "World.h"
#include "GameManager.h"
#include "Asset.h"

Coin::Coin(int askii)
	:askii(askii),percent(0)
{
	english[0] = { char(askii) };
	
	string str = "";
	str += english[0];

	text = new Text(str, 100, D3DCOLOR_XRGB(255, 255, 255));
	addChild(text);

	if (manager.name.compare("fortunate") == 0 || manager.name.compare("propitious") == 0)
		percent = 3;
	if (manager.name.compare("lucky") == 0 || manager.name.compare("rich") == 0)
		percent = 5;
}


Coin::~Coin()
{
}

void Coin::update(float dt)
{
	Entity::update(dt);

	if (deleting) return;

	if (circle(pos , inGame->player->center()) < 100)
	{
		manager.alphabetNum[askii - 65]++;

		asset.sounds[L"sound/effect_sound.wav"]->Reset();
		asset.sounds[L"sound/effect_sound.wav"]->Play();

		if (percent > 0 && percent < random(1, 10))
			manager.alphabetNum[askii - 65]++;
		
		deleting = true;
		
	}
}
