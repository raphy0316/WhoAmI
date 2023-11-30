#pragma once
#include "Define.h"
#include "Texture.h"

class Asset
{
public:
	Asset(void);
	~Asset(void);
	void init();
	void dispose();
	void ready(string rootFolderPath);
	void loadNext();
	Texture* getTexture(string p);
	CSound* getSound(wstring p);
	LPD3DXEFFECT getShader(string path);
	
	map<string, Texture*> textures;
	map<wstring, CSound*> sounds;
	list<LPD3DXEFFECT> shaders;
	CSoundManager _s;

	vector<string> paths;
	vector<string>::iterator pathIter;

	int filesLoaded;
	int filesToLoad;
};

extern Asset asset;