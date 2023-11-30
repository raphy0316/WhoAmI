#include "DXUT.h"
#include "MainScene.h"
#include "World.h"
#include "GameScene.h"
#include "GameManager.h"
#include "EndingScene.h"
#include "Asset.h"

MainScene::MainScene()
	:alpha(false)
{

	image = new Sprite("image/bg.png");
	addChild(image);


	image2 = new Sprite("image/touch.png");
	addChild(image2);
	image2->color.a = 0;
	manager.init();

	asset.sounds[L"sound/reststage.wav"]->Reset();

}


MainScene::~MainScene()
{
}

void MainScene::update(float dt)
{
	Scene::update(dt);

	if (!asset.sounds[L"sound/reststage.wav"]->IsSoundPlaying())
	{
		asset.sounds[L"sound/reststage.wav"]->Play();
	}


	if (!alpha)
	{
		image2->color.a += dt * 2;
	}

	if (image2->color.a >= 1)
	{
		alpha = true;
	}

	if (alpha)
	{
		image2->color.a -= dt * 2;
	}

	if (image2->color.a <= 0)
	{
		alpha = false;
	}

	if (world.getKeyState(VK_LBUTTON) == 1)
	{
		world.changeScene(new GameScene(false, false));
		return;
	}
}
