#pragma once
#include "Define.h"
#include "GameScene.h"
#include "ShopUI.h"
#include "Entity.h"

struct NickData
{
	string name;
	bool isEquip;
};
class GameManager
	:public Entity
{
public:
	GameManager();
	~GameManager();

	void init();
	
	int stage;
	int score;
	int potion;
	int damage;
	int alphabetNum[26];
	int currentStage;
	int persent;
	int havingNum;

	string name;

	GameScene* currentScene;
	NickData data[10];

};

extern GameManager manager;