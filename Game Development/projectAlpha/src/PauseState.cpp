#include "PauseState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "gameObjectFactory.h"
#include "StateParser.h"

std::string const PauseState::s_pauseID = "PAUSE";


void PauseState::update()
{
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
	GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());

	StateParser* pauseStateParser = new StateParser();
	pauseStateParser->parseState("projectAlpha/src/test.xml", getStateID(), &pauseStateObjects, &m_textureIDList);

	//populate callback functions

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_backToPlay);
	m_callbacks.push_back(s_pauseToMainMenu);

	setCallBacks(m_callbacks);
	
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < pauseStateObjects.size(); i++)
		pauseStateObjects[i]->clean();

	for (int i = 0; i < m_textureIDList.size(); i++)
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	
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
	Game::instance()->getGameStateMachine()->changeState(new MainMenuState());
}

void PauseState::setCallBacks(const std::vector<Callback>& callback)
{
	for (int i = 0; i < pauseStateObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(pauseStateObjects[i]))
		{
			MenuButton *menuButton = dynamic_cast<MenuButton*>(pauseStateObjects[i]);
			menuButton->setCallBack(m_callbacks[menuButton->getCallBackID()]);
		}
	}
}