#pragma once
#include <SDL.h>
#include "Vector2D.h"
#include "Player.h"
#include "gameObjectFactory.h"

class Region2 : public SDLGameObject
{

public:
	Region2();
	//Region2(int m_x, int m_y, int m_width, int m_height);
	//Region2(Vector2D topLeftCorner, Vector2D bottomRightCorner);
	//Region2(Vector2D playerPosition, int width, int height);

	~Region2() {}
	void load(const LoaderParams* pParams);
	SDL_Rect * getRegionRectangle() const;
	void printStats();

	static void getGameObjectRectangle(const GameObject* p_gameObject, SDL_Rect* destinationRectangle);
};

class Region2Creator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Region2();
	}
};