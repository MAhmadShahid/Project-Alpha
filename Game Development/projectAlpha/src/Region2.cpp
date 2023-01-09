#include "Region2.h"

Region2::Region2() : SDLGameObject()
{

}

void Region2::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}

//Region2::Region2(int x, int y, int width, int height)
//{
//	rectangle.x = x;
//	rectangle.y = y;
//
//	rectangle.w = width;
//	rectangle.h = height;
//}
//
//Region2::Region2(Vector2D topLeftCorner, Vector2D bottomRightCorner)
//{
//	rectangle.x = topLeftCorner.getX();
//	rectangle.y = topLeftCorner.getY();
//
//	rectangle.w = bottomRightCorner.getX() - topLeftCorner.getX();
//	rectangle.h = bottomRightCorner.getY() - bottomRightCorner.getY();
//}
//
//Region2::Region2(Vector2D position, int width, int height)
//{
//	rectangle.x = position.getX();
//	rectangle.y = position.getY();
//
//	rectangle.w = width;
//	rectangle.h = height;
//}


SDL_Rect * Region2::getRegionRectangle() const
{
	SDL_Rect* rectangle = new SDL_Rect;
	rectangle->x = m_position.getX();
	rectangle->y = m_position.getY();
	
	rectangle->w = m_width;
	rectangle->h = m_height;

	return rectangle;
}

void Region2::getGameObjectRectangle(const GameObject* p_gameObject, SDL_Rect* destinationRectangle)
{
	const SDLGameObject* gameObject = dynamic_cast<const SDLGameObject*>(p_gameObject);
	destinationRectangle->x = gameObject->getPosition().getX();
	destinationRectangle->y = gameObject->getPosition().getY();

	destinationRectangle->w = gameObject->getWidth();
	destinationRectangle->h = gameObject->getHieght();
}

void Region2::printStats()
{
	std::cout << std::endl <<"Region Stats: ";
	std::cout << std::endl << "Position: ( X , Y ) = ( " << m_position.getX() << " , " << m_position.getY() << " )";
	std::cout << std::endl << "Width: " << getWidth() << " , Hieght: " << getHieght();
}





