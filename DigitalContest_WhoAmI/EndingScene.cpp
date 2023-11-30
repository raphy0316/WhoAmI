#include "DXUT.h"
#include "EndingScene.h"
#include "MainScene.h"
#include "World.h"
#include "Asset.h"


EndingScene::EndingScene()
	:sound(false)
{
	ani = new Animation("image/ending", 56, 10, false, true);
	addChild(ani);

	if (!asset.sounds[L"sound/1stage.wav"]->IsSoundPlaying())
	{
		asset.sounds[L"sound/1stage.wav"]->Stop();
	}

	if (asset.sounds[L"sound/2stage.wav"]->IsSoundPlaying())
	{
		asset.sounds[L"sound/2stage.wav"]->Stop();
	}

	if (asset.sounds[L"sound/3stage.wav"]->IsSoundPlaying())
	{
		asset.sounds[L"sound/3stage.wav"]->Stop();
	}

	if (asset.sounds[L"sound/reststage.wav"]->IsSoundPlaying())
	{
		asset.sounds[L"sound/reststage.wav"]->Stop();
	}	
}


EndingScene::~EndingScene()
{
}

void EndingScene::update(float dt)
{
	Scene::update(dt);
	if (ani->currentFrame >= 40 && !sound)
	{
		asset.sounds[L"sound/ending.wav"]->Reset();
		asset.sounds[L"sound/ending.wav"]->Play();

		sound = true;
	}
	if (ani->isFinish)
	{
		world.changeScene(new MainScene());
		return;
	}
}
