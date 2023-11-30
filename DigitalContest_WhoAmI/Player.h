#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Animation.h"

class Player :
	public Entity
{
public:
	Player();
	~Player();

	Animation* ani;
	Animation* dieAni;
	Animation* runAni;
	Animation* slidingAni;
	Animation* jumpAni;
	Animation* rebornAni;


	void update(float dt);
	void move(float dt);
	void render();
	void die(float dt);

	float jumpSpeed;
	float vy;
	float hp;
	float maxHp;
	float speed;
	float invincibleTimer;
	float gravity;
	float makeParticleTimer;
	float hpminus;
	float leftHp;
	float rebornTimer;
	float afterTimer;

	bool _move;
	bool _jump;
	bool onGround;
	bool invincible;
	bool reborn;
	bool dead;
	bool canJump;

	int rebornCount;

	int jumpCount;

};

