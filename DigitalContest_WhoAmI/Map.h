#pragma once
#include "Entity.h"
#include "Sprite.h"

class Map :
	public Entity
{
public:
	Map(int stage, bool isBreak);
	~Map();

	void init();
	bool getGround(int x, int y);
	void setGround(int x, int y, bool b);

	bool getUpObstacle(int x, int y);
	void setUpObstacle(int x, int y, bool b);

	bool getDownObstacle(int x, int y);
	void setDownObstacle(int x, int y, bool b);

	void createCoin(int x, int y);
	void createOb(int x, int y , int type);

	void mapSetting(D3DXCOLOR color, int x, int y);

	Sprite* map;
	Sprite* hitMap[8];

	int mapWidth;
	int* groundBit;
	int* upObstacleBit;
	int* downObstacleBit;

	int stage;

	bool isBreak;
	bool dontinit;

	
};

