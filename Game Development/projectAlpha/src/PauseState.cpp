#include "PauseState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "GameStateMachine.h"
#include "InputHandler.h"

std::string const PauseState::s_pauseID = "PAUSE";



void PauseState::update()
{
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
		s_backToPlay();

	for (int i = 0; i < pauseStateObjects.size(); i++)
		pauseStateObjects[i]->update();
}

void PauseState::render()
{
	for (int i = 0; i < pauseStateObjects.size(); i++)
		pauseStateObjects[i]->draw();
}

bool PauseState::onEnter()
{
	SDL_Renderer* renderer = Game::instance()->getRenderer();
	Vector2D windowSize = Game::instance()->getWindowSize();
	Vector2D windowsQuarter = windowSize / 4.0f;
	Vector2D buttonDimensions(152.0f, 52.0f);
	Vector2D buttonCentre = buttonDimensions / 2.0f;
	Vector2D mainMenuButtonStart = Vector2D((windowsQuarter*3.0f).getX(), (windowsQuarter * 1.0f).getY());
	Vector2D resumeButtonStart = Vector2D((windowsQuarter * 3.0f).getX(), (windowsQuarter * 2.0f).getY());

	if (!TextureManager::Instance()->load("projectAlpha/src/Assets/GUIItems/MainMenuButton.png", "MainMenuButton", renderer))
	{
		std::cout << std::endl <<"Failes to load asset:  'MainMenuButton.png'" << std::endl;
		return false;
	}

	if (!TextureManager::Instance()->load("projectAlpha/src/Assets/GUIItems/ResumeButton.png", "ResumeButton", renderer))
	{
		std::cout << std::endl << "Failed to load asset: 'ResumeButton.png'" << std::endl;
		return false;
	}

	GameObject* mainMenuButton = new MenuButton(new LoaderParams(mainMenuButtonStart.getX() - buttonCentre.getX(), mainMenuButtonStart.getY(), 152, 52, 0, 1, "MainMenuButton"), s_pauseToMainMenu);
	GameObject* resumeButton = new MenuButton(new LoaderParams(resumeButtonStart.getX() - buttonCentre.getX(), resumeButtonStart.getY(), 152, 52, 0, 1, "ResumeButton"), s_backToPlay);	

	pauseStateObjects.push_back(mainMenuButton);
	pauseStateObjects.push_back(resumeButton);
	
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < pauseStateObjects.size(); i++)
		pauseStateObjects[i]->clean();

	pauseStateObjects.clear();

	std::cout << "Exiting from Pause State";

	return true;

}

void PauseState::s_backToPlay()
{
	Game::instance()->getGameStateMachine()->popState();
}

void PauseState::s_pauseToMainMenu()
{
	Game::instance()->getGameStateMachine()->changeState(new MenuState());
}