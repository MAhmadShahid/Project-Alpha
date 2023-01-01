#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "loaderParams.h"

SDLGameObject::SDLGameObject() : GameObject()
{

}

void SDLGameObject::load(const LoaderParams* pParams)
{
	m_textureID = pParams->getTextureID();

	m_position = Vector2D(pParams->getXPosition(), pParams->getYPosition());
	m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();

	m_currentRow = pParams->getCurrentRow();
	m_currentFrame = pParams->getCurrentFrame();

	m_numFrames = pParams->getNumFrames();

	scale_x = pParams->getScaleX();
	scale_y = pParams->getScaleY();
}



void SDLGameObject::draw()
{
	if (m_velocity.getX() < 0)
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame, scale_x, scale_y,
			Game::instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame, scale_x, scale_y,
			Game::instance()->getRenderer());
	}
}

void SDLGameObject::update()
{
	
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