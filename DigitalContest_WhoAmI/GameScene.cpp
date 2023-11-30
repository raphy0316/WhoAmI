#include "DXUT.h"
#include "GameScene.h"
#include "GameManager.h"
#include "World.h"
#include "MainScene.h"
#include "EndingScene.h"
#include "Asset.h"
GameScene::GameScene(bool isBreak,bool fail)
	:stage(1), mapMoveSpeed(0), plusSpeed(400), startTimer(0), gameStart(true), isBreak(isBreak),
	mapParticleTimer(0),cantMove(false),fail(fail),fireworkdSoundTimer(77)
{
	renderChildrenEnabled = false;

	ifs = ifstream("image/data.txt");
	ofs = ofstream("image/data.txt", ios::app | ios::end);

	stage = manager.stage;

	map = new Map(stage,isBreak);
	addChild(map);

	ui = new UI();

	if (!isBreak) 
	{

		for (int i = 0; i < 12; i++)
		{
			bgImage[i] = new Sprite("image/Map/BG/" + to_string(stage) + ".png");
			addChild(bgImage[i]);

			bgImage[i]->pos = Vec2(bgImage[i]->rect.right * i, 0);
		}

		for (int i = 0; i < 8; i++)
		{
			obstacleImage[i] = new Sprite("image/Map/Obstacle/" + to_string(stage) + "/" + to_string(i) + ".png");
			addChild(obstacleImage[i]);

			obstacleImage[i]->pos = Vec2(obstacleImage[i]->rect.right * i, 0);

		}
	}

	else
	{
		bgImage[0] = new Sprite("image/shop/bg.png");
		addChild(bgImage[0]);

		shop = new Sprite("image/shop/shop.png");
		addChild(shop);
		shop->pos = Vec2(450, 387);

		road = new Sprite("image/shop/road.png");
		addChild(road);

		stone = new Sprite("image/shop/stone.png");
		addChild(stone);
		stone->pos = Vec2(1000, 470);

		shopUI = new ShopUI();
		shopUI->visible = false;
	}

	player = new Player();
	addChild(player);
	follow(player);

	player->pos = Vec2(0, 0);

	rankBack = new Sprite("image/shop/ranking/bg.png");
	addChild(rankBack);
	rankBack->setCenter(Vec2(640, 360));
	rankBack->visible = false;

	best = new Sprite("image/shop/ranking/best.png");
	addChild(best);
	best->setCenter(Vec2(640, 280));

	board = new Sprite("image/shop/ranking/board.png");
	addChild(board);
	board->setCenter(Vec2(640, 360));

	nameText = new Text("asdasd", 40, D3DXCOLOR(1, 1, 1, 1));
	addChild(nameText);
	nameText->setCenter(Vec2(460, 320));
	//nameText->visible = false;

	stageText = new Text("1", 60, D3DXCOLOR(1, 1, 1, 1));
	addChild(stageText);
	stageText->setCenter(Vec2(700, 310));
	//stageText->visible = false;

	persentText = new Text("100", 60, D3DXCOLOR(1, 1, 1, 1));
	addChild(persentText);
	persentText->setCenter(Vec2(700, 360));

	//persentText->visible = false;

	asset.sounds[L"sound/reststage.wav"]->Reset();
	asset.sounds[L"sound/1stage.wav"]->Reset();
	asset.sounds[L"sound/2stage.wav"]->Reset();
	asset.sounds[L"sound/3stage.wav"]->Reset();



	if (isBreak)
	{
		if (!asset.sounds[L"sound/reststage.wav"]->IsSoundPlaying())
		{
			asset.sounds[L"sound/reststage.wav"]->Play();
		}

		if (asset.sounds[L"sound/1stage.wav"]->IsSoundPlaying())
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
	}

	else
	{
		if (asset.sounds[L"sound/reststage.wav"]->IsSoundPlaying())
		{
			asset.sounds[L"sound/reststage.wav"]->Stop();
		}

		if (manager.stage == 1)
		{
			if (!asset.sounds[L"sound/1stage.wav"]->IsSoundPlaying())
			{
				asset.sounds[L"sound/1stage.wav"]->Play();
			}

			if (asset.sounds[L"sound/2stage.wav"]->IsSoundPlaying())
			{
				asset.sounds[L"sound/2stage.wav"]->Stop();
			}

			if (asset.sounds[L"sound/3stage.wav"]->IsSoundPlaying())
			{
				asset.sounds[L"sound/3stage.wav"]->Stop();
			}
		}

		if (manager.stage == 2)
		{
			if (!asset.sounds[L"sound/2stage.wav"]->IsSoundPlaying())
			{
				asset.sounds[L"sound/2stage.wav"]->Play();
			}

			if (asset.sounds[L"sound/1stage.wav"]->IsSoundPlaying())
			{
				asset.sounds[L"sound/1stage.wav"]->Stop();
			}

			if (asset.sounds[L"sound/3stage.wav"]->IsSoundPlaying())
			{
				asset.sounds[L"sound/3stage.wav"]->Stop();
			}
		}

		if (manager.stage == 3)
		{
			if (!asset.sounds[L"sound/3stage.wav"]->IsSoundPlaying())
			{
				asset.sounds[L"sound/3stage.wav"]->Play();
			}

			if (asset.sounds[L"sound/1stage.wav"]->IsSoundPlaying())
			{
				asset.sounds[L"sound/1stage.wav"]->Stop();
			}

			if (asset.sounds[L"sound/2stage.wav"]->IsSoundPlaying())
			{
				asset.sounds[L"sound/2stage.wav"]->Stop();
			}
		}
	}
}


GameScene::~GameScene()
{
	delete ui;

	if (isBreak)
		delete shopUI;
}

void GameScene::update(float dt)
{
	Scene::update(dt);


	if (gameStart)
	{
		gameStart = false;
		map->init();
	}

	if (player->pos.y > 800)
	{
		world.changeScene(new GameScene(true,true));
		return;
	}

	if (isBreak && shopUI->visible)
		shopUI->update(dt);

	mapParticleTimer += dt;

	if (mapParticleTimer >= 0.8f)
	{
		for (int i = 0; i < 3; i++)
		{
			Particle* p = new Particle(2);
			addChild(p);
			particleList.push_back(p);
			if (startTimer <= 3)
				p->pos = Vec2(random(0, 1280), random(0, 720));
			else
				p->pos = Vec2(player->center().x + random(-360, 360), random(0, 720));
		}

		mapParticleTimer = 0;
	}

	ui->update(dt);

	//if (world.getKeyState(VK_LBUTTON) == 1)
	//{
	//	createMeteor();
	//}

	pos.y = -4;

	if (dt > 0.2f) return;

	removeList();

	startTimer += dt;

	if (!isBreak)
	{
		manager.currentStage = manager.stage;
		manager.persent = (float)player->pos.x / 20000.f * 100;

		if (pos.x >= 0)
			pos.x = 0;

		if (startTimer >= 3 && player->hp > 0 && !cantMove)
		{
			plusSpeed += 30 * dt;
			player->pos.x += plusSpeed * dt;
		}

		if (player->dead  && player->hp < 0)
		{
			world.changeScene(new GameScene(true,true));
			return;
		}
	}

	else {
		pos.x = 0;

		if (isBreak)
		{

			if (circle(player->center(), stone->center()) < 100 && world.getKeyState('Z') == 1)
			{
				save();
				cout << "Save" << endl;
				rankBack->visible = true;
				makeFireWork(Vec2(random(0, 1280), random(0, 720)));
			}

			if (world.getKeyState(VK_LBUTTON) == 1 && rankBack->visible) 
			{
				world.changeScene(new GameScene(false, false));
				return;
			}

			if (rankBack->visible)
			{

				if (asset.sounds[L"sound/reststage.wav"]->IsSoundPlaying())
				{
					asset.sounds[L"sound/reststage.wav"]->Stop();
				}

				fireworkdSoundTimer += dt;
				if (fireworkdSoundTimer >= 77)
				{
					asset.sounds[L"sound/firework.wav"]->Reset();
					asset.sounds[L"sound/firework.wav"]->Play();

					fireworkdSoundTimer = 0;
				}
			}

			if (circle(player->center(), shop->center()) < 200 && world.getKeyState('Z') == 1)
			{
				shopUI->visible = !shopUI->visible;
			}
		}
	}

	if (player->pos.x >= 19900)
	{
		if (manager.stage < 3) 
		{
			manager.stage++;

			world.changeScene(new GameScene(false, false));
			return;
		}

		else
		{
			world.changeScene(new EndingScene());
			return;
		}
	}

	for (auto a : afterList)
		a->color.a -= dt * 2;
}

void GameScene::render()
{
	Scene::render();

	

	if (!isBreak) {

		for (int i = 0; i < 12; i++)
		{
			bgImage[i]->render();
		}
		
		for (int i = 0; i < 8; i++)
		{
			obstacleImage[i]->render();
		}

		for (auto o : obstacleList)
			o->render();
		
	}

	else
	{
		bgImage[0]->render();
		road->render();
		shop->render();
		stone->render();
	}

	for (auto a : afterList)
		a->render();

	player->render();

	for (auto c : coinList)
		c->render();

	for (auto p : particleList) {
		p->render();
	}

	for (auto e : effectList)
		e->render();

	ui->render();

	if (isBreak && shopUI->visible)
		shopUI->render();

	for (auto p : particleList) {
		if (p->type == 1)
			p->render();
	}

	if (rankBack->visible) {

		rankBack->render();
		board->render();
		best->render();

		nameText->render();
		stageText->render();
		persentText->render();
	}

}

void GameScene::removeList()
{
	for (auto iter = begin(coinList); iter != end(coinList); ++iter)
	{
		if (!(*iter)->deleting) continue;

		removeChild(*iter);
		iter = coinList.erase(iter);
		if (iter == coinList.end())
			break;
	}

	for (auto iter = begin(particleList); iter != end(particleList); ++iter)
	{
		if (!(*iter)->deleting) continue;

		removeChild(*iter);
		iter = particleList.erase(iter);
		if (iter == particleList.end())
			break;
	}

	for (auto iter = begin(obstacleList); iter != end(obstacleList); ++iter)
	{
		if (!(*iter)->deleting) continue;

		removeChild(*iter);
		iter = obstacleList.erase(iter);
		if (iter == obstacleList.end())
			break;
	}

	for (auto iter = begin(effectList); iter != end(effectList); ++iter)
	{
		if (!(*iter)->deleting) continue;

		removeChild(*iter);
		iter = effectList.erase(iter);
		if (iter == effectList.end())
			break;
	}

	for (auto iter = begin(afterList); iter != end(afterList); ++iter)
	{
		if (!(*iter)->deleting) continue;

		removeChild(*iter);
		iter = afterList.erase(iter);
		if (iter == afterList.end())
			break;
	}
}

void GameScene::save()
{
	int stage2 = manager.stage;

	if (manager.persent >= 98)
		manager.persent = 100;

	if (manager.name != "") {
		ofs << manager.name << " " << stage2 << " " << manager.persent << endl;
	}
	ofs.close();

	Rank r;
	while (ifs >> r.name >> r.stage >> r.percent) {
		ranks.push_back(r);
	}

	ranks.sort([](Rank r1, Rank r2) {
		return r1.stage * 100 + r1.percent > r2.stage * 100 + r2.percent;
	});

	for (auto iter : ranks) {
		nameText->text = iter.name;
		stageText->text = to_string(iter.stage);
		persentText->text = to_string(iter.percent);

		break;
	}
}

void GameScene::makeFireWork(Vec2 pos)
{
	fireWorkTimer.reset(0.15f, 5, true);

	D3DXCOLOR color;
	color.r = random(0.f, 1.0f);
	color.g = random(0.f, 1.0f);
	color.b = random(0.f, 1.0f);

	fireWorkTimer.onTick = [=]()
	{

		int randomCount = random(20, 30);

		for (int i = 0; i < randomCount; i++)
		{
			Particle* p = new Particle(0);
			p->randomColor = color;
			addChild(p);
			particleList.push_back(p);
			p->pos = pos + Vec2(random(-5, 5), random(-5, 5));
			//p->pos = pos;
			p->moveAngle = D3DXToRadian(360 / randomCount * i);
		}
	};

	fireWorkTimer.onFinished = [=]()
	{
		makeFireWork(Vec2(random(0, 1280), random(0, 720)));
		
	};
}

void GameScene::createMeteor()
{
	Obstacle* o = new Obstacle(0);
	addChild(o);
	o->setCenter(player->center());
	obstacleList.push_back(o);
}
