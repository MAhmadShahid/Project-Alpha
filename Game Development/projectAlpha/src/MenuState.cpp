#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "Vector2D.h"

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
	std::cout << "Entering Menu State";

	//variables
	SDL_Renderer* renderer = Game::instance()->getRenderer();

	Vector2D windowsDimensions = Game::instance()->getWindowSize();
	Vector2D windowsCentre = windowsDimensions / 2;
	Vector2D buttonDimensions (152.0f,52.0f);
	Vector2D buttonCentre = buttonDimensions/2.0f;
	Vector2D buttonStartingLocation = windowsCentre - buttonCentre;

	if (!(TextureManager::Instance()->load("projectAlpha/src/Assets/GUIItems/ExitButton.png", "ExitButton", renderer)))
	{
		std::cout << "\nFailed to load resources for menu state: ExitButton\n";
		std::cout << SDL_Error;
		return false;
	}
	if (!TextureManager::Instance()->load("projectAlpha/src/Assets/GUIItems/MenuButton.png", "PlayButton", renderer))
	{
		std::cout << "\nFailed to load resources for menu state: PlayButton\n";
		std::cout << SDL_Error;
		return false;
	}

	GameObject* playButton = new MenuButton(new LoaderParams(buttonStartingLocation.getX(), buttonStartingLocation.getY(), buttonDimensions.getX(), buttonDimensions.getY(), 0, 1, "PlayButton"), s_menuToPlay);
	GameObject* exitButton = new MenuButton(new LoaderParams(buttonStartingLocation.getX(), buttonStartingLocation.getY() + 70.0f, buttonDimensions.getX(), buttonDimensions.getY(), 0, 1, "ExitButton"), s_exitFromMenu);

	m_menuObjects.push_back(playButton);
	m_menuObjects.push_back(exitButton);


	m_menuObjects[0]->printStats();
	m_menuObjects[1]->printStats();


	return true;

}

bool MenuState::onExit()
{

	for (int i = 0; i < m_menuObjects.size(); i++)
		m_menuObjects[i]->clean();

	m_menuObjects.clear();
	TextureManager::Instance()->clearFromTextureManager("PlayButton");
	TextureManager::Instance()->clearFromTextureManager("ExitButton");


	std::cout << "Exiting MenuState" << std::endl;
	return true;
}

void MenuState::s_menuToPlay()
{
	Game::instance()->getGameStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu()
{
	Game::instance()->quit();
}