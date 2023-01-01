#include "PlayState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "PauseState.h"
#include "gameObjectFactory.h"
#include "StateParser.h"
#include "GameOverState.h"
#include "LevelParser.h"
#include "Enemy.h"
#include "AnimatedTile.h"
const std::string PlayState::s_playID = "PLAY";


void PlayState::update()
{
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
		Game::instance()->getGameStateMachine()->pushState(new PauseState);


	//player check
	/*for (int i = 0; i < playStateObjects.size(); i++)
	{
		if (!dynamic_cast<Player*>(playStateObjects[i]))
		{
			continue;
		}

		Player* player = dynamic_cast<Player*>(playStateObjects[i]);
		Vector2D position = player->getPosition();

		if( position.getX() > 640)
			Game::instance()->getGameStateMachine()->pushState(new GameOverState);
	}*/


	pLevel->update();
}

void PlayState ::render()
{
	//TextureManager::Instance()->drawFrame("tileset1", 0, 0, 1536, 736, 1, 0, 1, 1, Game::instance()->getRenderer());
	pLevel->render();
}

bool PlayState::onEnter()
{
	GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	GameObjectFactory::Instance()->registerType("AnimatedTile", new AnimatedTileCreator());

	LevelParser levelParser;
	pLevel = levelParser.parseLevel("projectAlpha/Assets/mapPrototype.tmx");
	std::cout << "Printing Layer Grid";
	pLevel->printLayerGrid(6);
	//pLevel->printTileSetStats(0);


	std::cout << std::endl <<"entering playstate" << std::endl;
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