#include "DXUT.h"
#include "ShopUI.h"
#include "GameManager.h"
#include "World.h"
#include "Particle.h"
#include "GameScene.h"
#include "Asset.h"

ShopUI::ShopUI()
	:alphaCount(0), alphaNum(0), extraNum(0), haveCount(0), alreadyCreate(false), deletingNum(11), isCreating(false),showing(nullptr),already(false)
{
	equipNick = nullptr;

	backGround = new Sprite("image/shop/ui/bg.png");
	addChild(backGround);
	backGround->setCenter(Vec2(640, 360));

	shopBack = new Sprite("image/shop/ui/sbg.png");
	addChild(shopBack);
	shopBack->setCenter(Vec2(640, 280));
	shopBack->visible = false;

	profile = new Sprite("image/shop/ui/profile.png");
	addChild(profile);
	profile->pos = Vec2(450, 180);
	profile->visible = false;

	create = new Sprite("image/shop/ui/create.png");
	addChild(create);
	create->setCenter(Vec2(570, 300));

	for (int i = 0; i < 3; i++)
	{
		button[i] = new Sprite("image/shop/ui/up/"+to_string(i)+".png");
		addChild(button[i]);
		button[i]->setCenter(Vec2(440 + i * 76, 110));
	}

	input = new Sprite("image/shop/ui/input.png");
	addChild(input);
	input->setCenter(Vec2(570, 400));

	for (int i = 0; i < 26; i++)
	{
		alphaBet[i] = new  AlphaBetBox(i + 65, manager.alphabetNum[i]);
		addChild(alphaBet[i]);

		alphaBet[i]->pos = Vec2(740, 150 + 30 * i);

		if (i > 12)
		alphaBet[i]->pos = Vec2(810, 150 + 30 * (i - 13));
	}

	for (int i = 0; i < 3; i++)
	{
		sellItem[i] = new Sprite("image/shop/item/" +to_string(i)+ ".png");
		addChild(sellItem[i]);
		sellItem[i]->pos = Vec2(450 + i * 150, 250);
		if (i == 1)
			sellItem[i]->pos.y -= 20;
		sellItem[i]->visible = false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			price[i] = new Sprite("image/shop/ui/3.png");
		else if (i == 2)
			price[i] = new Sprite("image/shop/ui/5.png");
		else if (i == 1)
			price[i] = new Sprite("image/shop/ui/10.png");


		addChild(price[i]);
		price[i]->pos = Vec2(450 + i * 150, 330);
		price[i]->visible = false;
	}

	createButton = new Sprite("image/shop/ui/generate.png");
	addChild(createButton);
	createButton->pos = Vec2(520, 500);

	alphaNum = new Sprite("image/shop/ui/small.png");
	addChild(alphaNum);
	alphaNum->pos = Vec2(750, 100);

	exchange = new Sprite("image/shop/ui/exchange.png");
	addChild(exchange);
	exchange->pos = Vec2(540, 450);

	extraText = new Text("0", 25, D3DXCOLOR(1, 1, 1, 1));
	addChild(extraText);
	extraText->pos = Vec2(765, 104);

	inputStr = "";

	particleTimer.onTick = [=]()
	{
		int randomA = random(0, 3);
		Vec2 randomPos;
		float randomAngle;

		if (randomA == 0)
		{
			randomPos = Vec2(570 + random(-120, 120), 241);
			randomAngle = D3DXToRadian(-90);
		}

		if (randomA == 1)
		{
			randomPos = Vec2(450, 300 + random(-60, 60));
			randomAngle = D3DXToRadian(180);
		}

		if (randomA == 2)
		{
			randomPos = Vec2(690, 300 + random(-60, 60));
			randomAngle = D3DXToRadian(0);
		}

		if (randomA == 3)
		{
			randomPos = Vec2(570 + random(-120, 120), 360);
			randomAngle = D3DXToRadian(90);
		}

		Particle* p[3];
		for (int i = 0; i < 3; i++)
		{
			p[i] = new Particle(1);
			inGame->addChild(p[i]);
			inGame->particleList.push_back(p[i]);
			p[i]->pos = randomPos + Vec2(random(-20, 20), random(-20, 20));
			p[i]->moveAngle = randomAngle + D3DXToRadian(random(-20, 20));
			
			create->pos += Vec2(random(-1, 1), random(-1, 1));
		}			
	};

	particleTimer.onFinished = [=]()
	{
		NickName* n = new NickName(inputStr);
		addChild(n);
		nickList.push_back(n);
		n->setCenter(create->center());
		n->sample = true;
		create->setCenter(Vec2(570, 300));
		
		asset.sounds[L"sound/makeword.wav"]->Reset();
		asset.sounds[L"sound/makeword.wav"]->Play();

		NickName* n2 = new NickName(inputStr);
		addChild(n2);
		nickList.push_back(n2);
		n2->pos = Vec2(450, 180 + haveCount * 40);
		n2->visible = false;
		create->setCenter(Vec2(570, 300));
		n2->num = haveCount;
		manager.data[haveCount].name = inputStr;
		haveCount++;
		manager.havingNum++;
		isCreating = false;
		inputStr = "";

	};

	ani = new Animation("image/shop/item/boxAni", 12, 10, false, true);
	ani->setCenter(Vec2(640, 360));
	ani->isStop = true;
	addChild(ani);
	ani->visible = false;

	for (int i = 0; i < 8; i++)
	{
		explain[i] = new Sprite("image/shop/name_info/" + to_string(i) + ".png");
		addChild(explain[i]);
		explain[i]->setCenter(Vec2(320, 550));
		explain[i]->visible = false;
	}

	view = new Sprite("image/shop/ui/view.png");
	addChild(view);
	view->visible = false;
	view->pos = Vec2(650, 220);

	player = new Sprite("image/shop/ui/player.png");
	addChild(player);
	player->visible = false;
	player->setCenter(view->center());

	createNick();

}


ShopUI::~ShopUI()
{
}

void ShopUI::update(float dt)
{
	Entity::update(dt);


	for (int i = 0; i < 3; i++)
	{
		if (price[0]->visible&&world.getKeyState(VK_LBUTTON) == 1 && sellItem[i]->rectWithPos().contain(world.getMousePos()))
		{
			if (i == 1 && extraNum > 9 && manager.potion < 5) {
				extraNum -= 10;
				manager.potion++;
			}

			if (i == 0 && extraNum > 4) {
				extraNum -= 5;

				asset.sounds[L"sound/scroll_open.wav"]->Reset();
				asset.sounds[L"sound/scroll_open.wav"]->Play();

				int r = random(0, 13);
				NickName* n = new NickName(voca[r]);
				n->sample = true;
				addChild(n);
				nickList.push_back(n);
				n->setCenter(Vec2(640, 360));
			}

			if (i == 2 && extraNum > 2 && ani->isStop) {
				extraNum -= 3;
				ani->currentFrame = 0;
				ani->isFinish = false;
				ani->isStop = false;
				ani->visible = true;

				alreadyCreate = true;
			}
		}
	}

	if (create->visible) {

		for (int i = 0; i < 26; i++)
		{
			if (alphaBet[i]->count > 0 && alphaBet[i]->rectWithPos().contain(world.getMousePos()) && world.getKeyState(VK_LBUTTON) == 1 && alphaCount < 14 && !isCreating)
			{
				AlphaBet* a = new AlphaBet(alphaBet[i]->text->text, i + 65,false);
				addChild(a);
				alphaList.push_back(a);
				alphaCount++;
				a->pos = Vec2(460 + alphaCount * 14, 390);
				asset.sounds[L"sound/click.wav"]->Reset();
				asset.sounds[L"sound/click.wav"]->Play();
				alphaBet[i]->count--;

				inputStr += alphaBet[i]->text->text;
			}
		}


		if (check(inputStr) == true && world.getKeyState(VK_LBUTTON) == 1 && createButton->rectWithPos().contain(world.getMousePos()) && haveCount < 10)
		{
			particleTimer.reset(0.05, 20, true);
			isCreating = true;
			for (auto a : alphaList)
				a->deleting = true;

			alphaCount = 0;
		}

		if (world.getKeyState(VK_LBUTTON) == 1 && exchange->rectWithPos().contain(world.getMousePos()) && alphaCount > 0)
		{
			extraNum += alphaCount;

			for (auto a : alphaList)
				a->deleting = true;

			alphaCount = 0;
			inputStr = "";
		}

		if (world.getKeyState(VK_BACK) == 1)
		{
			int a = 0;

			for (auto iter = begin(alphaList); iter != end(alphaList); ++iter)
			{
				if (++a == alphaCount)
				{
					alphaCount--;
					alphaBet[(*iter)->type - 65]->count++;
					(*iter)->deleting = true;
					inputStr.pop_back();
				}
			}
		}


	}

	extraText->text = to_string(extraNum);

	if (world.getKeyState(VK_LBUTTON) == 1 && button[0]->rectWithPos().contain(world.getMousePos()))
	{
		create->visible = true;
		input->visible = true;
		createButton->visible = true;
		exchange->visible = true;

		for (int i = 0; i < 26; i++)
			alphaBet[i]->visible = true;

		shopBack->visible = false;

		for (int i = 0; i < 3; i++)
			sellItem[i]->visible = false;

		for (int i = 0; i < 3; i++)
			price[i]->visible = false;

		profile->visible = false;

		for (auto n : nickList)
		{
			if (n->sample)
				continue;

			n->visible = false;
		}

		for (auto a : alphaList)
		{
			a->visible = true;
		}

		view->visible = false;
		player->visible = false;
	}

	if (world.getKeyState(VK_LBUTTON) == 1 && button[1]->rectWithPos().contain(world.getMousePos()))
	{
		create->visible = false;
		input->visible = false;
		createButton->visible = false;
		exchange->visible = false;

		for (int i = 0; i < 26; i++)
			alphaBet[i]->visible = false;

		shopBack->visible = true;

		for (int i = 0; i < 3; i++)
			sellItem[i]->visible = true;

		for (int i = 0; i < 3; i++)
			price[i]->visible = true;

		profile->visible = false;

		for (auto n : nickList)
		{
			if (n->sample)
				continue;

			n->visible = false;
		}

		for (auto a : alphaList)
		{
			if (!a->sample)
				a->visible = false;
		}

		view->visible = false;
		player->visible = false;
	}

	if (world.getKeyState(VK_LBUTTON) == 1 && button[2]->rectWithPos().contain(world.getMousePos()))
	{
		create->visible = false;
		input->visible = false;
		createButton->visible = false;
		exchange->visible = false;

		for (int i = 0; i < 26; i++)
			alphaBet[i]->visible = false;

		shopBack->visible = false;

		for (int i = 0; i < 3; i++)
			sellItem[i]->visible = false;

		for (int i = 0; i < 3; i++)
			price[i]->visible = false;

		profile->visible = true;

		for (auto n : nickList)
		{
			if (n->sample)
				continue;

			n->visible = true;
			
		}

		for (auto a : alphaList)
		{
			a->visible = false;
		}

		view->visible = true;
		player->visible = true;

	}

	if (profile->visible)
	{
		int i = 0;

		for (auto n : nickList)
		{
			cout << n->name << " " << n->num << " " << deletingNum << endl;

			if (deletingNum < n->num) {
				n->pos.y -= 40;
				i++;
				n->num--;
			}

			if (n->rectWithPos().contain(world.getMousePos())) {

				if (!showing)
					explain[n->type]->visible = true;
				
				if (showing && n != showing && n->type != showing->type)
				{
					explain[n->type]->visible = true;
					explain[showing->type]->visible = false;
					showing = n;
				}
				showing = n;
			}

			if (showing && showing->deleting)
			{
				explain[showing->type]->visible = false;
				showing = nullptr;
			}

			if (showing && !showing->rectWithPos().contain(world.getMousePos())) {
				explain[showing->type]->visible = false;
				cout << "½Ê" << endl;
				showing = nullptr;
			}
		}	
		deletingNum = 11;

	
	}

	if (ani->isFinish && alreadyCreate)
	{
		int randomN = random(0, 26);
		alphaBet[randomN]->count++;
		string test = "";
		char c[1] = { char(65 + randomN)};
		test += c[0];

		AlphaBet* a = new AlphaBet(test, randomN + 65,true);
		addChild(a);
		alphaList.push_back(a);
		alphaCount++;
		a->pos = Vec2(600, 200);

		ani->isStop = true;
		ani->visible = false;
		ani->isFinish = false;

		asset.sounds[L"sound/chest_open.wav"]->Reset();
		asset.sounds[L"sound/chest_open.wav"]->Play();

		alreadyCreate = false;
	}

	for (auto iter = begin(alphaList); iter != end(alphaList); ++iter)
	{
		if (!(*iter)->deleting) continue;

		removeChild(*iter);
		iter = alphaList.erase(iter);
		if (iter == alphaList.end())
			break;
	}

	for (auto iter = begin(nickList); iter != end(nickList); ++iter)
	{
		if (!(*iter)->deleting) continue;

		removeChild(*iter);
		iter = nickList.erase(iter);
		if (iter == nickList.end())
			break;
	}

}

bool ShopUI::check(string a)
{
	if (a.compare("") == 0)
		return false;

	for (int i = 0; i < 14; i ++) {

		if (a.compare(voca[i]) == 0)
		{
			return true;
		}
	}
	
	return false;
}

void ShopUI::createNick()
{
	for (int i = 0; i < 10; i++)
	{
		if (manager.data[i].name.compare("none") != 0)
		{
			NickName* n2 = new NickName(manager.data[i].name);
			addChild(n2);
			nickList.push_back(n2);
			n2->pos = Vec2(450, 180 + haveCount * 40);
			n2->visible = false;
			n2->num = haveCount;
			haveCount++;

			if (manager.data[i].isEquip)
			{
				n2->equip->visible = true;
				equipNick = n2;
			}
		}
	}
}

void ShopUI::deleteData(int num)
{
	if (num == 0)
	{
		manager.data[num].name = "none";
		manager.data[num].isEquip = false;

		return;
	}

	for (int i = num; i < 10; i++)
	{
		if (i > 0)
		{
			manager.data[i - 1].name = manager.data[i].name;
			manager.data[i - 1].isEquip = manager.data[i].isEquip;
		}
	}
}

AlphaBetBox::AlphaBetBox(int type, int count)
	:count(count)
{
	box = new Sprite("image/shop/ui/box.png");
	addChild(box);

	english[0] = { char(type) };

	string str = "";
	str += english[0];

	text = new Text(str, 20, D3DCOLOR_XRGB(255, 255, 255));
	addChild(text);
	text->pos = Vec2(14, 6);


	num = new Text(to_string(count), 20, D3DCOLOR_XRGB(255, 255, 255));
	addChild(num);
	num->pos = Vec2(40, 6);

	rect = box->rect;
}

AlphaBetBox::~AlphaBetBox()
{
}

void AlphaBetBox::update(float dt)
{
	Entity::update(dt);

	num->text = to_string(count);
}

AlphaBet::AlphaBet(string a,int type, bool sample)
	:type(type),sample(sample)
{
	if (!sample)
		t = new Text(a,12,D3DXCOLOR(1,1,1,1));
	else
		t = new Text(a, 200, D3DXCOLOR(1, 1, 1, 1));
	t->pos = Vec2(5, -2);
	addChild(t);
}

AlphaBet::~AlphaBet()
{
}

void AlphaBet::update(float dt)
{
	Entity::update(dt);
	
	if (sample) {
		t->color.a -= dt * 0.5f;
	}

	if (t->color.a <= 0)
		deleting = true;
}

NickName::NickName(string name)
	:name(name), sample(false),type(-1)
{
	image = new Sprite("image/shop/Words/" + name + ".png");
	addChild(image);

	rect = image->rect;

	equip = new Sprite("image/shop/ui/equip.png");
	addChild(equip);
	equip->pos = Vec2(5, -10);
	equip->visible = false;
}

NickName::~NickName()
{
}

void NickName::update(float dt)
{
	Entity::update(dt);

	if (deleting) return;

	if (sample)
	{
		image->color.a -= dt;

		if (image->color.a <= 0)
			deleting = true;
	}

	else
	{
		if (rectWithPos().contain(world.getMousePos()) && world.getKeyState(VK_RBUTTON) == 1 && visible)
		{
			if (inGame->shopUI->equipNick && inGame->shopUI->equipNick == this)
			{
				equip->visible = false;
				inGame->shopUI->equipNick = nullptr;
				manager.name = "none";
				manager.data[num].isEquip = false;
			}

			inGame->shopUI->deleteData(num);

			inGame->shopUI->deletingNum = num;
			deleting = true;

			inGame->shopUI->explain[type]->visible = false;
			inGame->shopUI->showing = nullptr;
			manager.havingNum--;
			inGame->shopUI->haveCount--;
		}

		if (rectWithPos().contain(world.getMousePos()) && world.getKeyState(VK_LBUTTON) == 1 && visible)
		{
			if (inGame->shopUI->equipNick) {
				manager.data[inGame->shopUI->equipNick->num].isEquip = false;
				inGame->shopUI->equipNick->equip->visible = false;
			}

			asset.sounds[L"sound/equip.wav"]->Reset();
			asset.sounds[L"sound/equip.wav"]->Play();

			equip->visible = true;
			inGame->shopUI->equipNick = this;
			manager.data[num].isEquip = true;
			manager.name = name;
		}
	}

	if (name.compare("SOLID") == 0)
		type = 0;

	if (name.compare("STUBBURN") == 0)
		type = 1;

	if (name.compare("DURABLE") == 0 || name.compare("STEADY") == 0)
		type = 2;

	if (name.compare("STABLE") == 0 || name.compare("CONTINUOUS") == 0)
		type = 3;

	if (name.compare("DEATHLESS") == 0 || name.compare("IMPERISHABLE") == 0) 
		type = 4;

	if (name.compare("LUCKY") == 0 || name.compare("RICH") == 0)
		type = 5;

	if (name.compare("FORTUNATE") == 0 || name.compare("PROPITIOUS") == 0)
		type = 6;

	if (name.compare("IMMORTAL") == 0)
		type = 7;	
}
	
