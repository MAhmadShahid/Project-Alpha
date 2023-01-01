#pragma once
#include <iostream>
#include <vector>
#include "Layer.h"
#include "GameObject.h"

class ObjectLayer : public Layer
{
private:
	std::vector<GameObject*> m_gameObjects;

public:
	virtual void update();
	virtual void render();
	virtual void printTileIDs();

	virtual ~ObjectLayer();

	std::vector<GameObject*>* getGameObjects()
	{
		return &m_gameObjects;
	}
};