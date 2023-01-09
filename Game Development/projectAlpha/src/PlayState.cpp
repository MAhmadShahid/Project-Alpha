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
#include "Region2.h"
#include "Camera.h"
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
	player->update(checkPlayerCollision());
}

void PlayState ::render()
{
	//TextureManager::Instance()->drawFrame("tileset1", 0, 0, 1536, 736, 1, 0, 1, 1, Game::instance()->getRenderer());
	pLevel->render();
	player->draw();
}

bool PlayState::onEnter()
{
	GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	GameObjectFactory::Instance()->registerType("AnimatedTile", new AnimatedTileCreator());
	GameObjectFactory::Instance()->registerType("Region2", new Region2Creator());

	LevelParser levelParser;
	pLevel = levelParser.parseLevel("projectAlpha/Assets/mapPrototype.tmx");
	player = pLevel->extractPlayerFromLayer();
	std::cout << "Printing Layer Grid";
	pLevel->printLayerGrid(6);
	//std:cout << std::endl << "Collision Regions Info: ";
	//CollisionManager::instance()->printStats("ghostIsland");
	//pLevel->printTileSetStats(0);

	SDL_Rect* ghostIsland = new SDL_Rect;
	ghostIsland->x = 0; ghostIsland->y = 0; ghostIsland->w = 510; ghostIsland->h = 510;

	SDL_Rect* playerRectangle = new SDL_Rect;
	playerRectangle->x = player->getPosition().getX(); playerRectangle->y = player->getPosition().getY();
	playerRectangle->w = player->getWidth(); playerRectangle->h = player->getHieght();

	std::cout << std::endl <<"Player Position: x = " << playerRectangle->x << ", y = " << playerRectangle->y;
	std::cout << std::endl << "Player Size: w = " << playerRectangle->w << ", h = " << playerRectangle->h;

	if (SDL_HasIntersection(ghostIsland, playerRectangle) == SDL_TRUE)
		std::cout << std::endl <<"They both intersect !";

	Camera::instance()->setTarget(player);

	//CollisionManager::instance()->printStats(CollisionManager::islands[0]);
	


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

bool PlayState::checkPlayerCollision()
{
	Region2* futurePosition = new Region2;
	futurePosition->setPosition(player->getPosition() + player->getVelocity());
	futurePosition->setWidth(player->getWidth());
	futurePosition->setHeight(player->getHieght());

	//std::cout << std::endl << "Future Position";
	//futurePosition->printStats();
	
	bool collision = CollisionManager::instance()->isObjectColliding(futurePosition);
	//std::cout << std::endl << collision;
	return collision;
	//return false;
}