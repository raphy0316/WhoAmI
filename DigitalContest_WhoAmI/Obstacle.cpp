#include "DXUT.h"
#include "Obstacle.h"
#include "GameManager.h"
#include "World.h"
#include "GameScene.h"
#include "Effect.h"
#include "Asset.h"

Obstacle::Obstacle(int type)
	:stage(manager.stage),type(type),already(false),stopTimer(0),timer(0),timerOn(false),re(false),moveStart(false)
{

	image = new Sprite("image/Map/ob/" + to_string(stage) + "/" + to_string(type) + ".png");
	addChild(image);
	rect = image->rect;

	speed = 400;
	gravity = 0;

	if (manager.stage == 2 && type == 2)
	{
		ani = new Animation("image/Map/ob/ani/trap", 6, 10, false, true);
		addChild(ani);
		ani->pos = Vec2(-10, 0);
		ani->isStop = true;
		image->visible = false;
	}

	if (manager.stage == 2 && type == 1)
	{
		image->visible = false;
	}

	if (manager.stage == 3 && type == 1) {

	}

	if (manager.stage == 3 && type == 0)
	{
		ani = new Animation("image/Map/ob/ani/meteor", 4, 10, true, true);
		addChild(ani);
		ani->pos.x -= 10;
		ani->pos.y -= 10;
		ani->color.a = 0.5f;
	}
}

Obstacle::~Obstacle()
{
}

void Obstacle::update(float dt)
{
	Entity::update(dt);

	if (dt > 0.2f)
	 return;

	if (type == 0) {

		if (circle(center(), inGame->player->center()) < 450 && center().x < inGame->player->pos.x)
		{
			if (!inGame->map->getGround(center().x, pos.y + rect.bottom)) {
				gravity += 500 * dt;
				pos.y += (speed + gravity) * dt;
			}
		}

		if (circle(center() + Vec2(0,rect.bottom), inGame->player->center()) < 80 && !re && !inGame->player->invincible)
		{
			inGame->shake(10, 10, 0.05);
			inGame->player->hp -= manager.damage;
			inGame->player->invincible = true;
			asset.sounds[L"sound/crash.wav"]->Reset();
			asset.sounds[L"sound/crash.wav"]->Play();
			re = true;
		}
	}

	if (type == 1 && manager.stage == 2)
	{
		image->visible = true;


		if (circle(center(), inGame->player->center()) < 250 && !already)
		{
			timerOn = true;
		}

		if (timerOn)
		{
			timer += dt;

			if (!already)
			{
				Effect* e = new Effect(0);
				e->setCenter(center() + Vec2(0,20));
				inGame->addChild(e);	
				inGame->effectList.push_back(e);
				already = true;
			}

			if (timer >= 0.1f)
				pos.y -= 100 * dt;

			if (timer >= 0.5f) {
				timerOn = false;
				asset.sounds[L"sound/skeleton_hand_up.wav"]->Reset();
				asset.sounds[L"sound/skeleton_hand_up.wav"]->Play();
				image->setPath("image/Map/ob/2/10.png");
			}
		}

		if (circle(center(), inGame->player->center()) < 80 && !re && !inGame->player->invincible)
		{
			inGame->shake(10, 10, 0.05);
			inGame->player->hp -= manager.damage;
			inGame->player->invincible = true;

			asset.sounds[L"sound/crash.wav"]->Reset();
			asset.sounds[L"sound/crash.wav"]->Play();
			re = true;
		}
	}

	if (type == 2 && manager.stage == 2)
	{
		if (circle(center(), inGame->player->center()) < 80 && !already && !inGame->player->invincible && !re)
		{

			ani->isStop = false;
			inGame->cantMove = true;
			inGame->shake(10, 10, 0.05);
			inGame->player->hp -= manager.damage;
			inGame->player->canJump = false;
			inGame->player->invincible = true;

			asset.sounds[L"sound/trap_close.wav"]->Reset();
			asset.sounds[L"sound/trap_close.wav"]->Play();
			re = true;
		}

		if (!ani->isStop)
		{
			if ((int)ani->currentFrame == 3)
			{
				stopTimer += dt;
				inGame->cantMove = true;

				inGame->plusSpeed = 400;
				ani->currentFrame = 3;
			}

			if (stopTimer >= 2) 
			{
				ani->currentFrame++;
				inGame->cantMove = false;
				inGame->player->canJump = true;

				stopTimer = 0;
			}

			if (ani->currentFrame >= 5)
			{
				already = true;
				inGame->cantMove = false;
			}

			if (already)
			{
				ani->color.a -= dt;
				if (ani->color.a <= 0)
					deleting = true;
			}
		}
	}

	if (type == 0 && manager.stage == 3)
	{
		if (circle(center(), inGame->player->center()) < 1600) {
		
			moveStart = true;
		}

		if (moveStart)
		{
			pos.x -= (550 + gravity) * dt;
			pos.y += (350 + gravity) * dt;
		}

		if (circle(center(), inGame->player->center()) < 100 && !already && !inGame->player->invincible && !re)
		{
			ani->isStop = false;
			asset.sounds[L"sound/crash.wav"]->Reset();
			asset.sounds[L"sound/crash.wav"]->Play();
			inGame->shake(10, 10, 0.05);
			inGame->player->hp -= manager.damage;
			inGame->player->invincible = true;
			re = true;
		}
	}

	if (type == 1 && manager.stage == 3)
	{
		if (circle(center(), inGame->player->center()) < 2800)
		{
			pos.x -= (500+ gravity) * dt;
		}

		Rect t;

		if (circle(center(), inGame->player->center()) < 100 && !re && !inGame->player->invincible)
		{
			asset.sounds[L"sound/crash.wav"]->Reset();
			asset.sounds[L"sound/crash.wav"]->Play();
			inGame->shake(10, 10, 0.05);
			inGame->player->hp -= manager.damage;
			inGame->player->invincible = true;

			re = true;
		}
	}

	if (pos.y >= 720)
		deleting = true;
}
