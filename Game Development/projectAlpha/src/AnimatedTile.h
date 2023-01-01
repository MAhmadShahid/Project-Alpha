#pragma once
#include <iostream>
#include <vector>
#include "SDLGameObject.h"
#include "gameObjectFactory.h"
#include "TileSet.h"


class AnimatedTile : public SDLGameObject
{
private:
	int startingID;
public:
	AnimatedTile();

	virtual void draw();
	virtual void update();
	virtual void clean();


	virtual void load(const LoaderParams* pParams);

};

class AnimatedTileCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new AnimatedTile;
	}
};
