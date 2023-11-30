#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Animation.h"

class NickName
	:public Entity
{
public :
	NickName(string name);
	~NickName();

	void update(float dt);

	string name;
	Sprite* image;
	Sprite* equip;


	bool sample;
	int type;
	int num;
};

class AlphaBetBox
	:public Entity
{
public:
	AlphaBetBox(int type , int count);
	~AlphaBetBox();

	void update(float dt);

	Text* text;
	Text* num;

	Sprite* box;

	char alphabet;
	char english[1];

	int count;
};

class AlphaBet
	:public Entity
{
public:
	AlphaBet(string a ,int type, bool sample);
	~AlphaBet();

	void update(float dt);

	bool isDeployed;
	bool sample;
	int type;

	Sprite* image;
	Text* t;
};

class ShopUI :
	public Entity
{
public:
	ShopUI();
	~ShopUI();

	void update(float dt);
	bool check(string a);
	void createNick();
	void deleteData(int num);

	Sprite* create;
	Sprite* input;
	Sprite* backGround;
	Sprite* shopBack;
	Sprite* button[3];
	
	Sprite* createButton;
	Sprite* exchange;
	Sprite* craftButton;
	Sprite* alphaNum;
	Sprite* sbg;
	Sprite* profile;
	Sprite* x;
	Sprite* explain[8];
	Sprite* player;
	Sprite* view;


	Sprite* sellItem[3];
	Sprite* price[3];
	Sprite* rankBg;
	Sprite* board;

	AlphaBetBox* alphaBet[26];

	list<AlphaBet*>alphaList;
	list<NickName*>nickList;

	NickName* showing;
	NickName* equipNick;

	Animation* ani;

	int alphaCount;
	int extraNum;
	int haveCount;
	int deletingNum;

	bool alreadyCreate;
	bool isCreating;
	bool already;

	Text* extraText;


	string inputStr;
	string voca[14] = 
	{
		"CONTINUOUS","DEATHLESS","DURABLE","FORTUNATE","IMMORTAL","IMPERISHABLE","LUCKY","MIRACULOUS","PROPITIOUS","RICH","SOLID","STEADY","STABLE","STUBBURN"
	};

	Timer particleTimer;

};

