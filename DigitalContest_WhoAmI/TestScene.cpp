#include "DXUT.h"
#include "TestScene.h"
#include "World.h"

TestScene::TestScene(void)
{
	sprite = new Sprite("image/win.png");
	addChild(sprite);

	sprite->pos.x = 0;
	sprite->color.a = 0;
	flag = 0;
}


TestScene::~TestScene(void)
{
}


void TestScene::update(float dt)
{
	Scene::update(dt);

	auto center = Vec2(1280, 720) / 2;
	float angleWithMouse = angle(sprite->pos, world.getMousePos());

	sprite->pos += (center - sprite->pos) * 0.2;

	if (world.getKeyState(VK_SPACE) == 2)
	{
		sprite->pos.x += cos(angleWithMouse) * 50;
		sprite->pos.y += sin(angleWithMouse) * 50;
	}

	if (flag == 0 && sprite->color.a < 1) {
		sprite->color.a += 0.015;
		if (sprite->color.a >= 1) {
			flag = 1;
		}
	}
	else if(flag == 1 && sprite->color.a >0){
		sprite->color.a -= 0.015;
		if (sprite->color.a <= 0) {
			flag = 0;
		}
	}
	cout << sprite->color.a << ' ' << flag << endl;
}