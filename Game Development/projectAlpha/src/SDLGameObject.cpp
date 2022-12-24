#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams), m_position(pParams -> getXPosition(), pParams -> getYPosition()), m_velocity(0,0), m_acceleration(0,0)
{
	m_textureID = pParams->getTextureID();

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	
	m_currentRow = 1;
	m_currentFrame = 0;
}

void SDLGameObject::draw()
{
	if (m_velocity.getX() < 0)
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			Game::instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			Game::instance()->getRenderer());
	}
}

void SDLGameObject::update()
{
	int windowWidth, windowHeight;

	SDL_GetWindowSize(Game::instance()->getWindow(), &windowWidth, &windowHeight);
	

	//the sprite stays in the window frame
	bool inValidWidthRange = ((int)m_position.getX() <= windowWidth - 39) && ((int)m_position.getX() >= 0);
	bool inValidHeightRange = ((int)m_position.getY() <= windowHeight - 39) && ((int)m_position.getY() >= 0);

	if (inValidWidthRange && inValidHeightRange)
	{
		m_velocity += m_acceleration;
		m_position += m_velocity;
	}
}

void SDLGameObject::clean()
{

}

void SDLGameObject::printStats()
{
	std::cout << "\nTexture ID = " << m_textureID << std::endl;
	std::cout << "X = " << m_position.getX() << ", Y = " << m_position.getY() << std::endl;
	std::cout << "Width = " << m_width << ", Height = " << m_height << std::endl;
	std::cout << "Current : Row = " << m_currentRow << ", Frame = " << m_currentFrame << std::endl;
}