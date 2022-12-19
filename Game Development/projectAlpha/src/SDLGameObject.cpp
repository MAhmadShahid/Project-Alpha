#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams), m_position(pParams -> getXPosition(), pParams -> getXPosition()), m_velocity(0,0), m_acceleration(0,0)
{
	m_textureID = pParams->getTextureID();

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	
	m_currentRow = 1;
	m_currentFrame = 0;
}

void SDLGameObject::draw()
{
	TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::instance()->getRenderer());
}

void SDLGameObject::update()
{
	int windowWidth, windowHeight;

	SDL_GetWindowSize(Game::instance()->getWindow(), &windowWidth, &windowHeight);
	
	
	if ((int)m_position.getX() < windowWidth - 48)
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
	std::cout << "Texture ID = " << m_textureID << std::endl;
	std::cout << "X = " << m_position.getX() << ", Y = " << m_position.getY() << std::endl;
	std::cout << "Width = " << m_width << ", Height = " << m_height << std::endl;
	std::cout << "Current : Row = " << m_currentRow << ", Frame = " << m_currentFrame << std::endl;
}