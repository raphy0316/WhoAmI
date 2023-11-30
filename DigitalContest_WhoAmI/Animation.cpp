#include "DXUT.h"
#include "Animation.h"
#include "Asset.h"

Animation::Animation(const string& path, int frameNum, float fps, bool loop, bool png)
	:loop(loop), currentFrame(0), fps(fps),isStop(false),isFinish(false)
{
	for(int i=0; i<frameNum; i++)
	{
		Texture* t = asset.getTexture(path+"/"+to_string(i) + (png?  ".png" : ".tga"));
		textures.push_back(t);
	}
	texture = textures[0];

	visibleRect = rect = Rect(0, 0, texture->info.Width, texture->info.Height);
}


Animation::~Animation(void)
{
}

void Animation::update(float dt)
{
	Sprite::update(dt);

	if (isStop) return;

	currentFrame += dt * fps;
	
	if((int)currentFrame >= textures.size())
	{
		if(loop)
			currentFrame = 0;

		else {
			currentFrame = textures.size() - 1;
			isFinish = true;
		}
	}



	texture = textures[int(currentFrame)];
}