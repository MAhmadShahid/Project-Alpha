#include "PlayState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "PauseState.h"

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
	
	if (!TextureManager::Instance()->load("projectAlpha/src/Assets/ghostRightFace.bmp", "player", Game::instance()->getRenderer()))
	{
		std::cout << "Error in loading resources";
		return false;
	}

		
	GameObject* playerObject = new Player(new LoaderParams(0,0, 48,48, 0, 1, "player"));

	playStateObjects.push_back(playerObject);

	return true;

}

bool PlayState::onExit()
{
	for (int i = 0; i < playStateObjects.size(); i++)
		playStateObjects[i]->clean();

	playStateObjects.clear();
	TextureManager::Instance()->clearFromTextureManager("player");

	return true;
}