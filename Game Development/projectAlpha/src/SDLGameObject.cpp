#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams)
{
	m_textureID = pParams->getTextureID();

	m_x = pParams->getXPosition();
	m_y = pParams->getYPosition();
	
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	
	m_currentRow = 1;
	m_currentFrame = 0;
}

void SDLGameObject::draw()
{
	TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, Game::instance()->getRenderer());
}

void SDLGameObject::update()
{

}

void SDLGameObject::clean()
{

}

void SDLGameObject::printStats()
{
	std::cout << "Texture ID = " << m_textureID << std::endl;
	std::cout << "X = " << m_x << ", Y = " << m_y << std::endl;
	std::cout << "Width = " << m_width << ", Height = " << m_height << std::endl;
	std::cout << "Current : Row = " << m_currentRow << ", Frame = " << m_currentFrame << std::endl;
}