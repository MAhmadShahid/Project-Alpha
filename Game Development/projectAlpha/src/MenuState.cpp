#include "MenuState.h"

const std::string MenuState::menuID = "MENU";

void MenuState::update()
{

}

void MenuState::render()
{

}

bool MenuState::onEnter()
{
	std::cout << "Entering Menu" << std::endl;
	return true;

}

bool MenuState::onExit()
{
	std::cout << "Exiting Menu" << std::endl;
	return true;
}