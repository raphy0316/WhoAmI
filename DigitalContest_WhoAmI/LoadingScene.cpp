#include "DXUT.h"
#include "LoadingScene.h"
#include "Asset.h"
#include "World.h"
#include "MainScene.h"

LoadingScene::LoadingScene()
{
	asset.ready("image");

	back = new Sprite("image/loading/back.png");
	addChild(back);

	bar = new Sprite("image/loading/bar.png");
	addChild(bar);
	bar->pos = Vec2(212, 504);

	frame = new Sprite("image/loading/frame.png");
	addChild(frame);




	asset.getSound(L"sound/1stage.wav");
	asset.getSound(L"sound/2stage.wav");
	asset.getSound(L"sound/3stage.wav");
	asset.getSound(L"sound/reststage.wav");
	asset.getSound(L"sound/effect_sound.wav");
	asset.getSound(L"sound/click.wav");
	asset.getSound(L"sound/equip.wav");
	asset.getSound(L"sound/jump.wav");
	asset.getSound(L"sound/chest_open.wav");
	asset.getSound(L"sound/potion_drink.wav");
	asset.getSound(L"sound/scroll_open.wav");
	asset.getSound(L"sound/skeleton_hand_up.wav");
	asset.getSound(L"sound/trap_close.wav");

	asset.getSound(L"sound/crash.wav");
	asset.getSound(L"sound/firework.wav");
	asset.getSound(L"sound/makeword.wav");
	asset.getSound(L"sound/ending.wav");
	asset.getSound(L"sound/relive.wav");
	asset.getSound(L"sound/falling.wav");


}


LoadingScene::~LoadingScene()
{
}

void LoadingScene::update(float dt)
{
	Scene::update(dt);

	bar->visibleRect.right = (float)asset.filesLoaded / (float)asset.filesToLoad * bar->rect.right;

	for (int i = 0; i < 10; i++)
	{
		asset.loadNext();

		cout << asset.filesLoaded << " " << asset.filesToLoad << endl;

		if (asset.filesLoaded >= asset.filesToLoad)
		{
			world.changeScene(new MainScene());
			return;
		}
	}
}
