#include "Camera.h"
#include "Game.h"

Camera* Camera::s_pCamera = 0;
const int Camera::mapWidth = 1698;
const int Camera::mapHeight = 955;

void Camera::setTarget(GameObject* targetObject) 
{ 
	m_pTarget = targetObject; 
}

void Camera::setPosition(const Vector2D & position)
{ 
	m_position = position; 
}


const Vector2D Camera::getPosition() const
{
	if (m_pTarget == 0)
		return m_position;

	Vector2D position((dynamic_cast<SDLGameObject*>(m_pTarget))->getPosition().getX() - (Game::instance()->getGameWidth() / 2), (dynamic_cast<SDLGameObject*>(m_pTarget))->getPosition().getX() - (Game::instance()->getGameHeight() / 2));

	//validate x position
	if (position.getX() < 0)
		position.setX(0);
	else if (position.getX() + (Game::instance()->getGameWidth() / 2) >= mapWidth)
		position.setX(1430);

	//validate y position
	if (position.getY() < 0)
		position.setY(0);
	else if (position.getX() + (Game::instance()->getGameHeight() / 2) >= mapHeight)
		position.setY(251);

	
	return position;
}

void Camera::update(Vector2D velocity)
{

}
