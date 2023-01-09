#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "SDLGameObject.h"
#include "gameObjectFactory.h"

#include <iostream>
#include <vector>
#include "Region2.h"
#include "Vector2D.h"

using namespace std;


class Player : public SDLGameObject
{	
public:
	Player();
	virtual void draw();
	virtual void update(bool collisionOccurs);
	virtual void clean();

	virtual void load(const LoaderParams* pParams);
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};

#endif