#pragma once
#include <map>
#include <vector>
#include "SDLGameObject.h"


class CollisionManager
{
private:
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

	//map and vector to store collision zones
	std::map<std::string, std::vector<SDL_Rect>> collisionZones;

	bool init(const char* fileName) {}
	bool isObjectColliding(SDLGameObject& gameObject) {}
};
