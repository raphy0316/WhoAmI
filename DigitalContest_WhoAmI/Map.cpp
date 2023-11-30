#include "DXUT.h"
#include "Map.h"
#include "World.h"
#include "GameScene.h"
#include "GameManager.h"
#include "Obstacle.h"

Map::Map(int stage, bool isBreak)
	:stage(stage),isBreak(isBreak),dontinit(false)
{
	if (!isBreak) {

		for (int i = 0; i < 8; i++)
		{
			hitMap[i] = new Sprite("image/Map/Hitmap/" + to_string(stage) + "/" + to_string(i) + ".png");
		}
	}

	else
	{
		hitMap[0] = new Sprite("image/shop/hit.png");
	}
	

}


Map::~Map()
{
	if (!isBreak) {
		for (int i = 0; i < 8; i++)
			SAFE_DELETE(hitMap[i]);
	}
	else
		SAFE_DELETE(hitMap[0]);

}

void Map::init()
{
	DWORD* data;
	D3DLOCKED_RECT lockRect;

	dontinit = true;

	int x;
	if (!isBreak)
		x = hitMap[0]->rect.right * 8;
	else
		x = hitMap[0]->rect.right;

	int y = hitMap[0]->rect.bottom;
	int totalBit = x * y;
	mapWidth = x;
	cout << mapWidth << endl;

	groundBit = new int[totalBit / 32 + ((totalBit % 32 > 0) ? 1 : 0)];
	memset(groundBit, 0, sizeof(int)* (totalBit / 32 + ((totalBit % 32 > 0) ? 1 : 0)));

	downObstacleBit = new int[totalBit / 32 + ((totalBit % 32 > 0) ? 1 : 0)];
	memset(downObstacleBit, 0, sizeof(int)* (totalBit / 32 + ((totalBit % 32 > 0) ? 1 : 0)));

	upObstacleBit = new int[totalBit / 32 + ((totalBit % 32 > 0) ? 1 : 0)];
	memset(upObstacleBit, 0, sizeof(int)* (totalBit / 32 + ((totalBit % 32 > 0) ? 1 : 0)));

	int limit = (isBreak) ? 1 : 8;

	for (int i = 0; i < limit; i++) {
		LPDIRECT3DSURFACE9 surface;
		hitMap[i]->texture->d3dTexture->GetSurfaceLevel(0, &surface);
		surface->LockRect(&lockRect, 0, 0);
		data = (DWORD*)lockRect.pBits;
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < hitMap[i]->rect.right; k++) {
				int index = j * lockRect.Pitch / 4 + k;
				mapSetting(data[index], k + hitMap[0]->rect.right * i, j);
			}
		}
		surface->UnlockRect();
		SAFE_RELEASE(surface);
	}
}

void Map::setGround(int x, int y, bool b)
{
	if (getGround(x, y) == b) return;
	int Pitch = y * mapWidth + x;
	groundBit[Pitch / 32] ^= (1 << Pitch % 32);
}

bool Map::getGround(int x, int y)
{
	if (y >= 720 || x <= 0 || y <= 0) return false;
	int Pitch = y * mapWidth + x;
	return groundBit[Pitch / 32] & (1 << Pitch % 32);
}

void Map::setUpObstacle(int x, int y, bool b)
{
	if (getUpObstacle(x, y) == b) return;
	int Pitch = y * mapWidth + x;
	upObstacleBit[Pitch / 32] ^= (1 << Pitch % 32);
}

bool Map::getUpObstacle(int x, int y)
{
	if (y >= 720 || x <= 0 || y <= 0) return false;
	int Pitch = y * mapWidth + x;
	return upObstacleBit[Pitch / 32] & (1 << Pitch % 32);
}

void Map::setDownObstacle(int x, int y, bool b)
{
	if (getDownObstacle(x, y) == b) return;
	int Pitch = y * mapWidth + x;
	downObstacleBit[Pitch / 32] ^= (1 << Pitch % 32);
}

void Map::createCoin(int x, int y)
{
	Coin* c = new Coin(random(65,90));
	c->pos = Vec2(x, y) + Vec2(25, -25);
	inGame->addChild(c);
	inGame->coinList.push_back(c);
}

void Map::createOb(int x, int y, int type)
{
	Obstacle* c = new Obstacle(type);
	if (manager.stage == 2 && type == 1)
		c->pos = Vec2(x, y + 35);
	else
		c->pos = Vec2(x, y);
	inGame->addChild(c);
	inGame->obstacleList.push_back(c);
}

bool Map::getDownObstacle(int x, int y)
{
	if (y >= 720 || x <= 0 || y <= 0 || isBreak) return false;
	int Pitch = y * mapWidth + x;
 	return downObstacleBit[Pitch / 32] & (1 << Pitch % 32);
}


void Map::mapSetting(D3DXCOLOR color, int x, int y)
{
	if (color == D3DXCOLOR(0, 0, 0, 1))
	{
		setGround(x, y, true);
	}

	if (color == D3DXCOLOR(1, 1, 0, 1))
	{
		setUpObstacle(x, y, true);
	}

	if (color == D3DXCOLOR(1, 0, 0, 1))
	{
		setDownObstacle(x, y, true);
	}

	if (color == D3DXCOLOR(0, 1, 0, 1))
	{
		createOb(x, y,0);
	}

	if (color == D3DXCOLOR(0, 0, 1, 1))
	{
		createOb(x, y, 1);
	}

	if (color == D3DXCOLOR(0, 1, 1, 1))
	{
		createOb(x, y+20, 2);
	}

	if (color == D3DXCOLOR(1, 0, 1, 1))
	{
		createCoin(x, y);
	}

	if (manager.stage == 3) {

		switch (color)
		{
		case D3DCOLOR_XRGB(100, 100, 100):
				createOb(x, y, 1);
			break;

		case D3DCOLOR_XRGB(200, 200, 200):
			createOb(x, y, 0);
			break;

		case D3DCOLOR_XRGB(50, 50, 50):
			createOb(x, y, 0);
			break;
		}
	}
}
