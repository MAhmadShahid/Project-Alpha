#pragma once
#include <map>
#include <SDL.h>
#include <vector>
#include "GameObject.h"
#include "SDLGameObject.h"
#include "Region2.h"

class CollisionManager
{
private:
	
	std::map<const std::string, std::vector<GameObject*>> m_collisionRegions;
	static CollisionManager* s_pInstance;

	CollisionManager();
	~CollisionManager() {}

public:

	//island ids
	static const std::string ghostIsland;
	static const std::string miniIsland;
	static const std::string villageIsland;
	static const std::string japaneseIsland;
	static const std::string storeIsland;
	static std::vector<std::string> islands;

	static CollisionManager* instance();


	void update();

	bool isObjectColliding(GameObject* p_gameObject);
	bool pushGameObject(const std::string island, GameObject* pObject);	

	//helping function
	void printStats(const std::string islandName);
	const std::string returnIsland(GameObject* gameObject);
	const std::vector<SDL_Rect*> findIslandVector(SDL_Rect* gameObjectVector);
};
