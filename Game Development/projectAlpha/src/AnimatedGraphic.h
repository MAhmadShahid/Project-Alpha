#pragma once

#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "SDLGameObject.h"
#include "gameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
	int m_animSpeed;

public:
	AnimatedGraphic();

	virtual void load(const LoaderParams* pParams);

	void update();
	void draw();
	void clean();
};

class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new AnimatedGraphic;
	}
};

#endif