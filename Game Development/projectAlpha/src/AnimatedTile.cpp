#include "AnimatedTile.h"

AnimatedTile::AnimatedTile() : SDLGameObject()
{
	
}

void AnimatedTile::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	startingID = pParams->getStartingID();
}

void AnimatedTile::draw()
{
	SDLGameObject::draw();
}

void AnimatedTile::update()
{
	m_currentFrame = 32 + int(((SDL_GetTicks() / 150)) % m_numFrames);
}

void AnimatedTile::clean()
{

}