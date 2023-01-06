#pragma once
#include "Level.h"
#include "tinyxml.h"
#include <iostream>
#include <string>
#include "CollisionManager.h"

class LevelParser
{
private:

	int m_tileSize;
	int m_width;
	int m_height;

	//for tile layers
	void parseTileSets(TiXmlElement* pTileSetRoot, std::vector<TileSet>* pTileSets);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<TileSet>* pTileSets);

	//for object layers
	void parseTextures(TiXmlElement* pTextureRoot);
	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers);
	
	//helping function
	void parseCollisionZoneLayer(TiXmlElement* collisionZoneNode, CollisionManager* collisionManager, std::vector<Layer*>* pLayers);

public:

	Level* parseLevel(const char* levelFile);

};