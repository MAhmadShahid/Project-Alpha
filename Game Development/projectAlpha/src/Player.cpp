#include "Player.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{

}


void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_acceleration.setX(0.1f);
	SDLGameObject::update();
}


void Player::clean()
{

}