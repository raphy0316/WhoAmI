#include "DXUT.h"
#include "GameManager.h"
#include "World.h"

GameManager::GameManager()
{
	init();
}


GameManager::~GameManager()
{
}

void GameManager::init()
{
	for (int i = 0; i < 10; i++)
	{
		data[i].isEquip = false;
		data[i].name = "none";
	}
	stage = 1;
	score = 0;
	potion = 0;
	damage = 20;
	persent = 0;
	currentStage = 1;
	havingNum = 0;

	for (int i = 0; i < 26; i++)
	{
		alphabetNum[i] = 0;
	}

	name = "none";
}



GameManager manager;