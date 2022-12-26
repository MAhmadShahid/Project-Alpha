#include "PlayState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "PauseState.h"
#include "gameObjectFactory.h"
#include "StateParser.h"

const std::string PlayState::s_playID = "PLAY";


void PlayState::update()
{
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
		Game::instance()->getGameStateMachine()->pushState(new PauseState);

	for (int i = 0; i < playStateObjects.size(); i++)
		playStateObjects[i]->update();
}

void PlayState ::render()
{
	for (int i = 0; i < playStateObjects.size(); i++)
		playStateObjects[i]->draw();
}

bool PlayState::onEnter()
{
	GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());

	StateParser *playStateParser = new StateParser();
	playStateParser->parseState("projectAlpha/src/test.xml", getStateID(), &playStateObjects, &m_textureIDList);

	return true;

}

bool PlayState::onExit()
{
	for (int i = 0; i < playStateObjects.size(); i++)
		playStateObjects[i]->clean();

	for (int i = 0; i < m_textureIDList.size(); i++)
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);

	playStateObjects.clear();

	return true;
}