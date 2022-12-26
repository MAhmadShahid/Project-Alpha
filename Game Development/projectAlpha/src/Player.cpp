#include "Player.h"
#include "InputHandler.h"

Player::Player() : SDLGameObject()
{

}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}


void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	//Left and right click to move the player sprite in that direction
	/*if (InputHandler::instance()->getMouseButtonState(LEFT))
		m_velocity.setX(-1);
	else if (InputHandler::instance()->getMouseButtonState(RIGHT))
		m_velocity.setX(1);
	else
		m_velocity.setX(0);*/

	//player sprite follows your mouse
	/*Vector2D* mousePosition = InputHandler::instance()->getMousePosition();
	m_velocity = (*mousePosition - m_position) / 100;*/

	//keyboard input: wasd movement
	float speed = 5.0f;
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_W))
	{
		m_velocity.setY(-speed);
		m_velocity.setX(0);
	}
	else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_A))
	{
		m_velocity.setY(0);
		m_velocity.setX(-speed);
	}
	else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S))
	{
		m_velocity.setY(speed);
		m_velocity.setX(0);
	}
	else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_D))
	{
		m_velocity.setY(0);
		m_velocity.setX(speed);
	}
	else
	{
		m_velocity.setY(0);
		m_velocity.setX(0);
	}

	SDLGameObject::update();
}


void Player::clean()
{

}