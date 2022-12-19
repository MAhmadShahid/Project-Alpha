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
	m_keystate = SDL_GetKeyboardState(0);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				std::cout << "Left Button Pressed";
				m_mouseButtonStates[LEFT] = true;
			}
			else if (event.button.button == SDL_BUTTON_MIDDLE)
				m_mouseButtonStates[MIDDLE] = true;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				m_mouseButtonStates[RIGHT] = true;

			break;
		
		case SDL_MOUSEBUTTONUP:
		
			if (event.button.button == SDL_BUTTON_LEFT)
				m_mouseButtonStates[LEFT] = false;
			else if (event.button.button == SDL_BUTTON_MIDDLE)
				m_mouseButtonStates[MIDDLE] = false;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				m_mouseButtonStates[RIGHT] = false;

			break;

		case SDL_MOUSEMOTION:

			m_mousePosition->setX((float)event.motion.x);
			m_mousePosition->setY((float)event.motion.y);
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
