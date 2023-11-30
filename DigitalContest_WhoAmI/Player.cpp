#include "DXUT.h"
#include "Player.h"
#include "Obstacle.h"
#include "GameManager.h"
#include "GameScene.h"
#include "World.h"
#include "Asset.h"

Player::Player()
	:onGround(false), _jump(false), vy(0), speed(500), gravity(0), jumpCount(0), 
	invincible(false), invincibleTimer(0), hpminus(0), rebornCount(0), rebornTimer(0),
	reborn(false),dead(false),canJump(true),afterTimer(0)
{
	renderChildrenEnabled = false;

	runAni = new Animation("image/Player/run", 10, 10, true, true);
	addChild(runAni);
	ani = runAni;

	jumpAni = new Animation("image/Player/jump", 10, 20, false, true);
	addChild(jumpAni);
	jumpAni->isStop = true;

	dieAni = new Animation("image/Player/die", 11, 10, false, true);
	addChild(dieAni);
	dieAni->isStop = true;

	slidingAni = new Animation("image/Player/sliding", 10, 20, false, true);
	addChild(slidingAni);
	slidingAni->isStop = true;

	rebornAni = new Animation("image/Player/reborn", 11, 10, false, true);
	addChild(rebornAni);
	rebornAni->isStop = true;


	rect = ani->rect;

	hp = 100;
	maxHp = hp;

	if (manager.name.compare("SOLID") == 0)
		manager.damage = 15;

	if (manager.name.compare("STUBBURN") == 0)
		manager.damage = 10;

	if (manager.name.compare("DEATHLESS") == 0 || manager.name.compare("IMPERSHIABLE") == 0) {
		hp += 60;
		maxHp += 60;
	}

	if (manager.name.compare("STABLE") == 0 || manager.name.compare("CONTINUOUS ") == 0) {
		hp += 40;
		maxHp += 40;
	}

	if (manager.name.compare("DURABLE") == 0 || manager.name.compare("STEADY") == 0) {
		hp += 20;
		maxHp += 20;
	}

	if (manager.name.compare("IMMORTAL") == 0) {
		leftHp = 50;
		rebornCount = 1;
	}
}


Player::~Player()
{
}

void Player::update(float dt)
{
	Entity::update(dt);

	if (dt > 0.2) return;

	afterTimer += dt;

	hpminus += dt;

	if (hpminus >= 1 && !inGame->isBreak) 
	{
		hp -= 1;
		hpminus = 0;
	}

	if (afterTimer >= 0.1f)
	{
		if (hp > 0)
		{
			if (ani == runAni)
			{
				Sprite* a = new Sprite("image/Player/run/" + to_string((int)ani->currentFrame) + ".png");
				a->color = ani->color;
				inGame->addChild(a);
				inGame->afterList.push_back(a);
				a->setCenter(center());
			}

			if (ani == jumpAni)
			{
				Sprite* a = new Sprite("image/Player/jump/" + to_string((int)ani->currentFrame) + ".png");
				a->color = ani->color;
				inGame->addChild(a);
				inGame->afterList.push_back(a);
				a->setCenter(center());
			}

			if (ani == slidingAni)
			{
				Sprite* a = new Sprite("image/Player/sliding/" + to_string((int)ani->currentFrame) + ".png");
				a->color = ani->color;
				inGame->addChild(a);
				inGame->afterList.push_back(a);
				a->setCenter(center());
			}

			if (ani == rebornAni)
			{
				Sprite* a = new Sprite("image/Player/reborn/" + to_string((int)ani->currentFrame) + ".png");
				a->color = ani->color;
				inGame->addChild(a);
				inGame->afterList.push_back(a);
				a->setCenter(center());
			}

			if (ani == dieAni)
			{
				Sprite* a = new Sprite("image/Player/die/" + to_string((int)ani->currentFrame) + ".png");
				a->color = ani->color;
				inGame->addChild(a);
				inGame->afterList.push_back(a);
				a->setCenter(center());
			}
		}

		afterTimer = 0;
	}

	if (manager.potion > 0 && world.getKeyState('Q') == 1)
	{
		asset.sounds[L"sound/potion_drink.wav"]->Reset();
		asset.sounds[L"sound/potion_drink.wav"]->Play();

		hp += 30;
		if (hp >= maxHp)
			hp = maxHp;

		manager.potion--;
	}

	if (invincible)
	{
		invincibleTimer += dt;

		if (invincibleTimer >= 2)
		{
			invincibleTimer = 0;
			invincible = false;
		}

		ani->color.r = 0;
	}
	else
		ani->color.r = 1;

	if (hp > 0 && !inGame->gameStart)
		move(dt);
	if (hp <= 0)
		die(dt);

	if (dieAni->isFinish)
		dead = true;

	if (hp <= 0 && rebornCount > 0 && dieAni->isFinish)
	{
		rebornCount--;

		inGame->cantMove = true;

		reborn = true;
		rebornAni->currentFrame = 0;
		rebornAni->isStop = false;
		ani = rebornAni;

		invincible = true;

		hp = leftHp;
		dead = true;

	}

	if (reborn)
	{
		
		if (rebornAni->isFinish)
		{
			asset.sounds[L"sound/relive.wav"]->Reset();
			asset.sounds[L"sound/relive.wav"]->Play();

			inGame->cantMove = false;
			inGame->plusSpeed = 400;
		
			reborn = false;
			dieAni->currentFrame = 0;
			dieAni->isFinish = false;
			dieAni->isStop = true;
			dead = false;
		}
	}


}

void Player::move(float dt)
{
	cout << dieAni->currentFrame << " " << dieAni->isFinish <<  " " << dead << endl;

	if (!inGame->isBreak && inGame->map->getDownObstacle(center().x, pos.y + rect.bottom - 50) && !invincible)
	{
		asset.sounds[L"sound/crash.wav"]->Reset();
		asset.sounds[L"sound/crash.wav"]->Play();

		inGame->shake(10, 10, 0.05);
		hp -= manager.damage;
		invincible = true;
	}

	int addPosY = (ani == slidingAni && ani->currentFrame >= 4) ? 125 : 0;
	if (!inGame->isBreak &&inGame->map->getUpObstacle(center().x, pos.y + addPosY) && !invincible)
	{
		asset.sounds[L"sound/crash.wav"]->Reset();
		asset.sounds[L"sound/crash.wav"]->Play();

		inGame->shake(10, 10, 0.05);
		hp -= manager.damage;
		invincible = true;
	}

	if (_jump && canJump)
	{
		if (ani == slidingAni && vy <= jumpSpeed)
			vy = 1600;

		vy += jumpSpeed * dt * 3.5f;
		pos.y -= (jumpSpeed - vy) * dt ;

		if (inGame->map->getGround(pos.x, pos.y))
		{
			vy = jumpSpeed;
		}

		if (inGame->map->getGround(center().x, pos.y + rect.bottom))
		{
			vy = 0;
			jumpSpeed = 0;
			jumpCount = 0;
			_jump = false;

			if (ani->currentFrame >= 9)
			{
				ani->isFinish = false;
				ani->currentFrame = 0;
			}

			if (ani == jumpAni)
				ani = runAni;
		}

		while (inGame->map->getGround(center().x, pos.y + rect.bottom - 3))
			pos.y -= dt;
	}

	if (inGame->map->dontinit && inGame->map->getGround(center().x, pos.y + rect.bottom))
		onGround = true;
	else
		onGround = false;

	if (inGame->map->isBreak) {

		if (world.getKeyState('D') == 2) {
			pos.x += speed * dt;
			_move = true;
		}

		if (world.getKeyState('A') == 2) {
			pos.x -= speed * dt;
			_move = true;
		}
	}


	if (world.getKeyState(VK_DOWN) == 1)
	{
		ani = slidingAni;
		rect = ani->rect;
		ani->currentFrame = 0;
		ani->isStop = false;
	}

	if (world.getKeyState(VK_DOWN) == 2)
	{
		if ((int)ani->currentFrame >= 5)
		{
			ani->currentFrame = 5;
		}
	}
	
	if (ani == slidingAni && ani->currentFrame >= 9)
	{
		ani->isFinish = false;
		ani = runAni;
	}

	if (world.getKeyState(VK_SPACE) == 1 && jumpCount < 2 && pos.y < 500)
	{
		ani =jumpAni;
		ani->isStop = false;
		ani->currentFrame = 0;

		jumpSpeed = 1350;
		vy = 0;
		_jump = true;
		jumpCount++;

		asset.sounds[L"sound/jump.wav"]->Reset();
		asset.sounds[L"sound/jump.wav"]->Play();
	}

	if (!onGround && !_jump)
	{
		gravity += 100 * dt;
		pos.y += (400 + gravity) * dt;
	}
	else
		gravity = 0;

}

void Player::render()
{
	Entity::render();

	ani->render();
}

void Player::die(float dt)
{
	if (ani != dieAni)
	{
		dieAni->isFinish = false;
		dieAni->currentFrame = 0;
		
		ani = dieAni;
		ani->isStop = false;
		ani->currentFrame = 0;
	}
}

