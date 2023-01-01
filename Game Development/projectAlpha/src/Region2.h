#pragma once
#include <SDL.h>
#include "Vector2D.h"
#include "Player.h"

class Region2
{
private:
	SDL_Rect rectangle;

public:
	Region2(int m_x, int m_y, int m_width, int m_height);
	Region2(Vector2D topLeftCorner, Vector2D bottomRightCorner);
	Region2(Vector2D position, int width, int height);

	~Region2() {}

	//static Region2 getPlayersRectangle(Player* playerObject);
	bool isColliding(const Region2& firstRegion, const Region2& secondRegion);
	bool isColliding(const Region2 * targetRegion);
	const SDL_Rect * getRegionRectangle() const;
};