#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "Game.h"
#include "StateParser.h"

const std::string MenuState::menuID = "MENU";

void MenuState::update()
{
	for (int i = 0; i < m_menuObjects.size(); i++)
	{
		m_menuObjects[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < m_menuObjects.size(); i++)
	{
		m_menuObjects[i]->draw();
	}
}

bool MenuState::onEnter()
{
	std::cout << "Entering MenuState";
	return true;
}

bool MenuState::onExit()
{
	return true;
}

