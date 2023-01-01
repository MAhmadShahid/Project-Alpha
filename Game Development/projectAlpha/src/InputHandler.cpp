#include "InputHandler.h"
#include "Game.h"
#include <iostream>

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler()
{
	for (int i = 0; i < 3; i++)
		m_mouseButtonStates.push_back(false);

}

InputHandler* InputHandler:: instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new InputHandler();
		return s_pInstance;
	}

	return s_pInstance;
}

void InputHandler::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(event);
			break;
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;
		case SDL_QUIT:
			Game::instance()->quit();
			break;
		default:
			break;
		}
	}
}

bool InputHandler::getMouseButtonState(int buttonNumber)
{
	return m_mouseButtonStates[buttonNumber];
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystate == 0)
		return false;

	if (m_keystate[key] == 1)
		return true;
	//else
	return false;
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::onMouseMotion(SDL_Event& event)
{
	m_mousePosition->setX(event.motion.x);
	m_mousePosition->setY(event.motion.y);
}

void InputHandler::onKeyDown(SDL_Event& event)
{
	m_keystate = SDL_GetKeyboardState(0);
}
