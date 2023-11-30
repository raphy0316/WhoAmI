#include "DXUT.h"
#include "UI.h"
#include "GameScene.h"
#include "World.h"
#include "GameManager.h"

UI::UI()
	
{
	hpFrame = new Sprite("image/UI/hpFrame.png");
	addChild(hpFrame);

	hpBar = new Sprite("image/UI/hpBar.png");
	addChild(hpBar);

	item = new Sprite("image/UI/item.png");
	addChild(item);

	item->pos = Vec2(1200, 0);

	potion = new Sprite("image/UI/0.png");
	addChild(potion);
	potion->setCenter(item->center());

	potionNum = new Text("0", 20, D3DXCOLOR(1, 1, 1, 1));
	addChild(potionNum);

	potionNum->pos = Vec2(1263, 72);
	
}


UI::~UI()
{
}

void UI::update(float dt)
{
	Entity::update(dt);

	hpBar->visibleRect.right = inGame->player->hp / inGame->player->maxHp * hpBar->rect.right;

	if (hpBar->visibleRect.right <= 0)
		hpBar->visibleRect.right = 0;

	if (manager.potion > 0)
	{
		potion->setPath("image/UI/1.png");
	}

	else
		potion->setPath("image/UI/0.png");

	potionNum->text = to_string(manager.potion);

}
