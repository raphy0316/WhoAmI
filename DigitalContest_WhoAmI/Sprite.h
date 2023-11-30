#pragma once
#include "Define.h"
#include "Entity.h"
#include "Texture.h"

class Sprite :
	public Entity
{
public:
	Sprite();
	Sprite(string path);
	virtual ~Sprite(void);
	void render();
	void setPath(string path);

	Texture* texture;
	D3DXCOLOR color;
	bool blending;
};
