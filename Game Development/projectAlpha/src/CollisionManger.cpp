#include "CollisionManager.h"

CollisionManager* CollisionManager::s_pInstance = 0;

const std::string CollisionManager::ghostIsland = "ghostIsland";
const std::string CollisionManager::miniIsland = "miniIsland";
const std::string CollisionManager::villageIsland = "villageIsland";
const std::string CollisionManager::japaneseIsland = "japaneseIsland";
const std::string CollisionManager::storeIsland = "storeIsland";

std::vector<std::string> CollisionManager::islands{ghostIsland, miniIsland, villageIsland, japaneseIsland, storeIsland};

CollisionManager::CollisionManager()
{
	m_collisionRegions[ghostIsland] = std::vector<GameObject*>();
	m_collisionRegions[miniIsland] = std::vector<GameObject*>();
	m_collisionRegions[villageIsland] = std::vector<GameObject*>();
	m_collisionRegions[japaneseIsland] = std::vector<GameObject*>();
	m_collisionRegions[storeIsland] = std::vector<GameObject*>();
	m_collisionRegions["sea"] = std::vector<GameObject*>();


	//populate first vector value of each island with its bounded region
	Region2* ghostisland = new Region2;
	ghostisland->load(new LoaderParams(0, 0, 486, 486, 0, 0, 0, "nil", 0, 0, 0));
	m_collisionRegions[ghostIsland].push_back(ghostisland);


	Region2* miniisland = new Region2;
	miniisland->load(new LoaderParams(2, 685, 454, 177, 0, 0, 0, "nil", 0, 0, 0));
	m_collisionRegions[miniIsland].push_back(miniisland);

	Region2* villageisland = new Region2;
	villageisland->load(new LoaderParams(643, 0, 1050, 765, 0, 0, 0, "nil", 0, 0, 0));
	m_collisionRegions[villageIsland].push_back(villageisland);

	Region2* japaneseisland = new Region2;
	japaneseisland->load(new LoaderParams(1709, 0, 994, 694, 0, 0, 0, "nil", 0, 0, 0));
	m_collisionRegions[japaneseIsland].push_back(japaneseisland);

	Region2* storeisland = new Region2;
	storeisland->load(new LoaderParams(1830, 690, 885, 265, 0, 0, 0, "nil", 0, 0, 0));
	m_collisionRegions[storeIsland].push_back(storeisland);

}

CollisionManager* CollisionManager::instance()
{
	if (s_pInstance != 0)
		return s_pInstance;

	s_pInstance = new CollisionManager();
	return s_pInstance;
}



bool CollisionManager::pushGameObject(const std::string island, GameObject* pObject)
{
	if (m_collisionRegions.find(island) == m_collisionRegions.end())
	{
		std::cout << std::endl << "Island Specified Not Found" << std::endl;
		return false;
	}
	m_collisionRegions[island].push_back(pObject);
	return true;
}

void CollisionManager::printStats(const std::string islandName)
{
	std::vector<GameObject*>& collisionRegions = m_collisionRegions[islandName];
	for (unsigned int i = 0; i < collisionRegions.size(); i++)
	{
		collisionRegions[i]->printStats();
	}

}

const std::string CollisionManager::returnIsland(GameObject* p_gameObject)
{
	//load passed game objects rectangle
	SDL_Rect* pGameObjectRectangle = new SDL_Rect{0,0,0,0};
	//dynamic_cast<Region2*>(p_gameObject)->printStats();
	Region2::getGameObjectRectangle(p_gameObject, pGameObjectRectangle);

	
	for (int i = 0; i < 5; i++)
	{
		SDL_Rect islandRectangle;
		
		//std::cout << std::endl << "Current Island: " << islands[i];
		GameObject * currentIslandObject = m_collisionRegions[CollisionManager::islands[i]].front();
		//std::cout << std::endl << "Island Stats";
		//dynamic_cast<Region2*>(currentIslandObject)->printStats();
		Region2::getGameObjectRectangle(currentIslandObject, &islandRectangle);
		
		if (SDL_HasIntersection(pGameObjectRectangle, &islandRectangle) == SDL_TRUE)
		{
			delete pGameObjectRectangle;
			//delete islandRectangle;
			//std::cout << std::endl << "Current Island: " << islands[i];
			return islands[i];
		}
	}

	delete pGameObjectRectangle;
	//delete islandRectangle
	return std::string("sea");
}

bool CollisionManager::isObjectColliding(GameObject* p_gameObject)
{
	const std::string islandToCheck = returnIsland(p_gameObject);
	//std::cout << std::endl << "Current Island: " << islandToCheck;
	
	//create rectangle of the object to be checked
	SDL_Rect* pGameObjectRectange = new SDL_Rect{0,0,0,0};
	Region2::getGameObjectRectangle(p_gameObject, pGameObjectRectange);
	SDL_Rect* islandRectangle = new SDL_Rect;

	//std::vector<GameObject*>::iterator vectorIterator = m_collisionRegions[islandToCheck].begin();
	//vectorIterator++; // skip the island bound region

	//for (vectorIterator; vectorIterator != m_collisionRegions[islandToCheck].end(); vectorIterator++)
	for( int i = 1; i < m_collisionRegions[islandToCheck].size(); i++)
	{
		const GameObject* currentCollisionRegion = m_collisionRegions[islandToCheck][i];
		Region2::getGameObjectRectangle(currentCollisionRegion, islandRectangle);

		if (SDL_HasIntersection(pGameObjectRectange, islandRectangle) == SDL_TRUE)
		{
			delete pGameObjectRectange;
			delete islandRectangle;
			//std::cout << std::endl << "True";
			return true;
		}
	}

	delete pGameObjectRectange;
	delete islandRectangle;
	return false;
}

//SDL_bool SDL_IntersectRect(const SDL_Rect* A, const SDL_Rect* B, SDL_Rect* result)
//{
//    int Amin, Amax, Bmin, Bmax;
//
//    /* Horizontal intersection */
//    Amin = A->x;
//    Amax = Amin + A->w;
//    Bmin = B->x;
//    Bmax = Bmin + B->w;
//    if (Bmin > Amin)
//        Amin = Bmin;
//    result->x = Amin;
//    if (Bmax < Amax)
//        Amax = Bmax;
//    result->w = Amax - Amin > 0 ? Amax - Amin : 0;
//
//    /* Vertical intersection */
//    Amin = A->y;
//    Amax = Amin + A->h;
//    Bmin = B->y;
//    Bmax = Bmin + B->h;
//    if (Bmin > Amin)
//        Amin = Bmin;
//    result->y = Amin;
//    if (Bmax < Amax)
//        Amax = Bmax;
//    result->h = Amax - Amin > 0 ? Amax - Amin : 0;
//
//    return (result->w && result->h);
//}
