#include "Region2.h"

Region2::Region2(int x, int y, int width, int height)
{
	rectangle.x = x;
	rectangle.y = y;

	rectangle.w = width;
	rectangle.h = height;
}

Region2::Region2(Vector2D topLeftCorner, Vector2D bottomRightCorner)
{
	rectangle.x = topLeftCorner.getX();
	rectangle.y = topLeftCorner.getY();

	rectangle.w = bottomRightCorner.getX() - topLeftCorner.getX();
	rectangle.h = bottomRightCorner.getY() - bottomRightCorner.getY();
}

Region2::Region2(Vector2D position, int width, int height)
{
	rectangle.x = position.getX();
	rectangle.y = position.getY();

	rectangle.w = width;
	rectangle.h = height;
}

//Region2 Region2::getPlayersRectangle(Player* playerObject)
//{
//	return Region2(playerObject->getPosition(), playerObject->getWidth(), playerObject->getHieght());
//}

const SDL_Rect * Region2::getRegionRectangle() const
{
	return &rectangle;
}

bool Region2::isColliding(const Region2& firstRegion, const Region2& secondRegion)
{
	if (SDL_HasIntersection(firstRegion.getRegionRectangle(), secondRegion.getRegionRectangle()) == SDL_TRUE)
		return true;

	return false;
}

bool Region2::isColliding(const Region2 *targetRegion)
{
	if (SDL_HasIntersection(&rectangle, targetRegion->getRegionRectangle()) == SDL_TRUE)
		return true;

	return false;
}


