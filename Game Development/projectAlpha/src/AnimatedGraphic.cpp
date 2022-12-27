#include "AnimatedGraphic.h"
#include "SDL.h"

//constructor for AnimatedGraphic class
AnimatedGraphic::AnimatedGraphic() : SDLGameObject()
{

}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_animSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

//update function of animated graphic class
void AnimatedGraphic::update()
{
	SDLGameObject::update();
}

void AnimatedGraphic::clean()
{
	SDLGameObject::clean();
}