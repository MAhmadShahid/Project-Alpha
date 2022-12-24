#include "MenuButton.h"
#include "InputHandler.h"



void MenuButton::draw()
{
	SDLGameObject::draw();
}

MenuButton::MenuButton(const LoaderParams* pParams, void(*callback)()) : SDLGameObject(pParams), m_callback(callback)
{
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::update()
{
	Vector2D* pMousePosition = InputHandler::instance()->getMousePosition();

	if (pMousePosition->getX() < (m_position.getX() + m_width)
		&& pMousePosition->getX() > m_position.getX()
		&& pMousePosition->getY() < (m_position.getY() + m_height)
		&& pMousePosition->getY() > m_position.getY())
	{ 

		if (InputHandler::instance()->getMouseButtonState(LEFT) && mouseButtonRelease)
			onMouseButtonDown();

		else if (!InputHandler::instance()->getMouseButtonState(LEFT) && justClicked == true)
			onMouseButtonUp();

		else if (!InputHandler::instance()->getMouseButtonState(LEFT))
			onMouseHover();
	}
	else
		m_currentFrame = MOUSE_OUT;
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::onMouseButtonDown()
{
	m_currentFrame = CLICKED;
	justClicked = true;
	mouseButtonRelease = false;
	
}

void MenuButton::onMouseButtonUp()
{
	justClicked = false;
	m_callback();
}

void MenuButton::onMouseHover()
{
	m_currentFrame = MOUSE_OVER;
	mouseButtonRelease = true;
}