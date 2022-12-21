#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* pParams) : SDLGameObject(pParams)
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
		m_currentFrame = MOUSE_OVER;

		if (InputHandler::instance()->getMouseButtonState(LEFT))
		{
			m_currentFrame = CLICKED;
		}
	}
	else
		m_currentFrame = MOUSE_OUT;
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}