#include "MainMenuState.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "StateParser.h"
#include "gameObjectFactory.h"
#include "Game.h"

const std::string MainMenuState::menuID = "MENU";

void MainMenuState::update()
{
	for (int i = 0; i < m_menuObjects.size(); i++)
	{
		m_menuObjects[i]->update();
	}
}

void MainMenuState::render()
{
	for (int i = 0; i < m_menuObjects.size(); i++)
	{
		m_menuObjects[i]->draw();
	}
}

bool MainMenuState::onEnter()
{
	std::cout << std::endl << "Entering MainMenu State" << std::endl;

	//initiating textures and sprites
	GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());

	StateParser *mainMenuStateParser = new StateParser();
	mainMenuStateParser->parseState("projectAlpha/src/test.xml", getStateID(), &m_menuObjects, &m_textureIDList);

	//populating callback functions
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	//set callbacks for menu items/objects
	setCallBacks(m_callbacks);
	
	return true;
}

bool MainMenuState::onExit()
{

	for (int i = 0; i < m_menuObjects.size(); i++)
		m_menuObjects[i]->clean();
	
	m_menuObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);


	std::cout << "Exiting MenuState" << std::endl;
	return true;
}

void MainMenuState::s_menuToPlay()
{
	Game::instance()->getGameStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	Game::instance()->quit();
}

 void MainMenuState::setCallBacks(const std::vector<Callback>& callback)
{
	 // go through the game objects
	 for (int i = 0; i < m_menuObjects.size(); i++)
	 {
			 // if they are of type MenuButton then assign a callback based on the id passed in from the file
			 if (dynamic_cast<MenuButton*>(m_menuObjects[i]))
			 {
				 MenuButton* pButton = dynamic_cast<MenuButton*>(m_menuObjects[i]);
				 pButton->setCallBack(callback[pButton->getCallBackID()]);
			 }
	 }
}