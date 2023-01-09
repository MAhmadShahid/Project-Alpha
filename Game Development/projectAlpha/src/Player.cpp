#include "Player.h"
#include "InputHandler.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "GameOverState.h"


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

void Player::update(bool collisionOccurs)
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

	int windowWidth, windowHeight;

	SDL_GetWindowSize(Game::instance()->getWindow(), &windowWidth, &windowHeight);


	//the sprite stays in the window frame
	bool inValidWidthRange = ((int)m_position.getX() <= windowWidth - 39) && ((int)m_position.getX() >= 0);
	bool inValidHeightRange = ((int)m_position.getY() <= windowHeight - 39) && ((int)m_position.getY() >= 0);

	//std::cout << std::endl << "Checking for collision" << std::endl;
	//vector<Region2> collisionRegion;
	//collisionRegion.push_back(Region2(7, 224, 214, 62));
	//Vector2D futurePosition = m_position + m_velocity;
	//Region2 futureRegion (futurePosition, m_width, m_height);
	
	//std::cout << "Players Future Region: X = " << futureRegion.getRegionRectangle()->x << ", Y = " << futureRegion.getRegionRectangle()->y << std::endl;
	//collisionOccurs = false;
	


	if (inValidWidthRange && inValidHeightRange && ! collisionOccurs)
	{
		m_velocity += m_acceleration;
		m_position += m_velocity;
	}

	//keyboard input: wasd movement
	float speed = 3.0f;
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_W))
	{
		m_currentRow = 3;
		m_velocity.setY(-speed);
		m_velocity.setX(0);
	}
	else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_A))
	{
		m_currentRow = 1;
		m_velocity.setY(0);
		m_velocity.setX(-speed);
	}
	else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S))
	{
		m_currentRow = 2;
		m_velocity.setY(speed);
		m_velocity.setX(0);
	}
	else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_D))
	{
		m_currentRow = 1;
		m_velocity.setY(0);
		m_velocity.setX(speed);
	}
	else
	{
		m_currentRow = 1;
		m_velocity.setY(0);
		m_velocity.setX(0);
	}

	
	m_currentFrame = int(((SDL_GetTicks() / 150) % m_numFrames));

	SDLGameObject::update();
}


void Player::clean()
{

}