#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "gameObjectFactory.h"
#include "StateParser.h"


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
	GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator);

	StateParser *gameOverStateParser = new StateParser();
	gameOverStateParser->parseState("projectAlpha/src/test.xml",getStateID(), &m_gameObjects, &m_textureIDList);

	//populating callback functions
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	setCallBacks(m_callbacks);

	std::cout << "entering PauseState\n";
	return true;
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);

	std::cout << "exiting GameOverState" << std::endl;
	return true;
}

void GameOverState::setCallBacks(const std::vector<Callback>& callback)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* menuButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			menuButton->setCallBack(m_callbacks[menuButton->getCallBackID()]);
		}
	}
}