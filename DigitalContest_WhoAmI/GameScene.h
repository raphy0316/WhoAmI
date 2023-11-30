#pragma once
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Sprite.h"
#include "Text.h"
#include "Coin.h"
#include "UI.h"
#include "Particle.h"
#include <fstream>
#include "Timer.h"
#include "ShopUI.h"
#include "Obstacle.h"
#include "Effect.h"

struct Rank {
	string name;
	int stage;
	int percent;
};

class GameScene :
	public Scene
{
public:
	GameScene(bool isBreak,bool fail);
	~GameScene();

	list<Coin*>coinList;
	list<Particle*>particleList;
	list<Sprite*>afterList;


	Sprite* obstacleImage[8];
	Sprite* bgImage[12];
	Sprite* shop;
	Sprite* road;
	Sprite* stone;
	Sprite* rankBack;
	Sprite* board;
	Sprite* best;

	Map* map;
	Player* player;

	UI* ui;
	ShopUI* shopUI;

	ifstream ifs;
	ofstream ofs;

	Text* nameText;
	Text* stageText;
	Text* persentText;

	list<Rank>ranks;
	list<Obstacle*>obstacleList;
	list<Effect*>effectList;

	Timer fireWorkTimer;

	void update(float dt);
	void render();
	void removeList();
	void save();
	void makeFireWork(Vec2 pos);
	void createMeteor();

	int stage;
	int plusSpeed;
	int mapMoveSpeed;

	float startTimer;
	float mapParticleTimer;
	float fireworkdSoundTimer;

	bool gameStart;
	bool isBreak;
	bool makeFireWorkd;
	bool cantMove;
	bool fail;
};

