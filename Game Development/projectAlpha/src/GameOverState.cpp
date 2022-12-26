#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "MainMenuState.h"


const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
	for (int i = 0; i < (int)m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for (int i = 0; i < (int)m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}


void GameOverState::s_gameOverToMain()
{
	Game::instance()->getGameStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
	Game::instance()->getGameStateMachine()->changeState(new PlayState());
}

bool GameOverState::onEnter()
{
	if (!TextureManager::Instance()->load("projectAlpha/src/Assets/GUIItems/gameover.png", "gameovertext", Game::instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("projectAlpha/src/Assets/GUIItems/main.png", "mainbutton", Game::instance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("projectAlpha/src/Assets/GUIItems/restartButton.png", "restartbutton", Game::instance()->getRenderer()))
	{
		return false;
	}

	/*GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, 0, 1, 0,"gameovertext",0,2));
	GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, 0, 1,"mainbutton",) );
	GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, 0, 1,"restartbutton"), s_restartPlay);

	m_gameObjects.push_back(gameOverText);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);*/
	std::cout << "entering PauseState\n";
	return true;
}

bool GameOverState::onExit()
{
	for (int i = 0; i < (int)m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	/*TextureManager::Instance()->clearFromTextureManager("resumebutton");
	TextureManager::Instance()->clearFromTextureManager("mainbutton");*/

	std::cout << "exiting GameOverState" << std::endl;
	return true;
}