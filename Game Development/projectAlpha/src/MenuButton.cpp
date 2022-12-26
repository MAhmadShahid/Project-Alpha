#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton() : SDLGameObject()
{

}

void MenuButton::draw()
{
	SDLGameObject::draw();
}

void MenuButton::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	callbackID = pParams->getCallbackID();
	m_currentRow = MOUSE_OUT;
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
		m_currentRow = MOUSE_OUT;
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::setCallBack(void(*callback)())
{
	m_callback = callback;
}

int MenuButton::getCallBackID()
{
	return callbackID;
}

void MenuButton::onMouseButtonDown()
{
	m_currentRow = CLICKED;
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
	m_currentRow = MOUSE_OVER;
	mouseButtonRelease = true;
}