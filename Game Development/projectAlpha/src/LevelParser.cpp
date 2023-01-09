#include "LevelParser.h"
#include "TextureManager.h"
#include "TileLayer.h"
#include "Game.h"
#include "base64.h"
#include "zlib.h"
#include "zconf.h"
#include "ObjectLayer.h"

using namespace std;

Level* LevelParser::parseLevel(const char* levelFile)
{
	//create TinyXML document and load the map 
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);

	//create the level object
	Level* pLevel = new Level();

	//get the root node
	TiXmlElement* pRoot = levelDocument.RootElement();

	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);

	//parse the tilesets
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTileSets(e, pLevel->getTileSets());
		}
	}

	// we must parse the textures needed for this level, which have been added to properties
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			parseTextures(e);
		}
	}

	//// parse any object layers
	//for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	//{
	//	if (e->Value() == std::string("layer"))
	//	{
	//		parseTileLayer(e, pLevel->getLayers(), pLevel->getTileSets());
	//	}
	//	else if (e->Value() == std::string("objectgroup"))
	//	{
	//		parseObjectLayer(e, pLevel->getLayers());
	//	}
	//}

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
		{
			if (e->FirstChildElement()->Value() == std::string("object"))
			{
				parseObjectLayer(e, pLevel->getLayers());
			}
			else if (e->FirstChildElement()->Value() == std::string("data"))
			{
				parseTileLayer(e, pLevel->getLayers(), pLevel->getTileSets());
			}
		}
	}

	return pLevel;
}

void LevelParser::parseTileSets(TiXmlElement* pTileSetRoot, std::vector<TileSet>* pTileSets)
{


	string source = pTileSetRoot->Attribute("source");
	cout << "Address returned by source attribute: " << source;
	string tilesetPath = "projectAlpha/Assets/" + source;
	cout << endl << "TileSetPath: " << tilesetPath;
	string tilesetID = "tileset" + (string)pTileSetRoot->Attribute("firstgid");
	cout << endl << "TileSetID: " << tilesetID;
	int firstGID = atoi(pTileSetRoot->Attribute("firstgid"));
	cout << " Int: " << firstGID;


	TileSet tileset;
	TiXmlDocument levelDocument;

	if (levelDocument.LoadFile(tilesetPath))
	{
		cout << endl << "Loaded State.tsx";
	}

	TiXmlElement* pTilesetRoot = levelDocument.RootElement();
	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
	tileset.firstGridID = firstGID;
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	
	if (!pTilesetRoot->Attribute("margin"))
		cout << endl << "Margin not a property" << endl;

	tileset.margin = 0;
	tileset.spacing = 0;
	tileset.name = tilesetID;
	//tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
	pTilesetRoot->Attribute("columns", &tileset.numColumns);//< tileset.numColumns;
	string imageName = pTilesetRoot->FirstChildElement()->Attribute("source");
	string imagePath = "projectAlpha/Assets/" + imageName;
	TextureManager::Instance()->load(imagePath, tilesetID, Game::instance()->getRenderer());
	

	pTileSets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<TileSet>* pTileSets)
{
	TileLayer* pTileLayer = new TileLayer(m_tileSize, m_width, m_height, 0,*pTileSets);
	// tile data
	std::vector<std::vector<int>> data;
	std::string decodedIDs;
	TiXmlElement* pDataNode = NULL;

	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}

	uLongf numGids = m_width * m_height * sizeof(int);
	std::vector<unsigned int> gids(numGids);
	std::vector<int> layerRow(m_width);

	unsigned int i = 0;
	for (TiXmlElement* e = pDataNode->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Attribute("gid") != nullptr)
		{
			gids[i] = atoi(e->Attribute("gid"));
		}
		else
		{
			gids[i] = 0;
		}
		i++;


		//gids[i++] = (unsigned int)();	

		/*
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
		*/
	}
	/*
	uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());
	*/


	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}

	//cout << endl;
	for (int rows = 0; rows < m_height; rows++)
	{
		//cout << "{ ";
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = gids[rows * m_width + cols];
			//cout << data[rows][cols] << " ";
		}
		//cout << "}" << endl;
	}
	pTileLayer->setTileIDs(data);
	pLayers->push_back(pTileLayer);

	//==================================================================================================================
	//compressed version

	//TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTileSets);
	//
	//// tile data
	//std::vector<std::vector<int>> data;
	//std::string decodedIDs;
	//TiXmlElement* pDataNode = nullptr;
	//
	//for (TiXmlElement* e = pTileElement->FirstChildElement(); e !=
	//	NULL; e = e->NextSiblingElement())
	//{
	//	if (e->Value() == std::string("data"))
	//	{
	//		pDataNode = e;
	//	}
	//}
	//
	//for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e =
	//	e->NextSibling())
	//{
	//	TiXmlText* text = e->ToText();
	//	std::string t = text->Value();
	//	decodedIDs = base64_decode(t);
	//}

	//// uncompress zlib compression
	//uLongf numGids = m_width * m_height * sizeof(int);
	//std::vector<unsigned> gids(numGids);
	//uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());
	//std::vector<int> layerRow(m_width);

	//
	//for (int j = 0; j < m_height; j++)
	//{
	//	data.push_back(layerRow);
	//}
	//
	//
	//for (int rows = 0; rows < m_height; rows++)
	//{
	//	for (int cols = 0; cols < m_width; cols++)
	//	{
	//		data[rows][cols] = gids[rows * m_width + cols];
	//	}
	//}
	//pTileLayer->setTileIDs(data);
	//pLayers->push_back(pTileLayer);

}

void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
	cout << endl << "In parse texture function" << endl;
	cout << pTextureRoot->Value();

	for (TiXmlElement* property = pTextureRoot->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
	{
		if (property->Value() == string("property"))
		{
			cout << endl << property->Value();
			string imagePath = "projectAlpha/Assets/" + (string)property->Attribute("value");
			//cout << endl << "Attribute: " <<  property->Attribute("name");
			if (TextureManager::Instance()->load(imagePath, property->Attribute("name"), Game::instance()->getRenderer()))
			{
				cout << endl << "Texture successfully loaded" << endl;
			}
			else
				cout << endl << "Texture Couldn't load; Name: " << property->Attribute("name") << endl;
		}
	}
	
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers)
{
	if (pObjectElement->Attribute("name") == string("Collision Zones"))
	{
		parseCollisionZoneLayer(pObjectElement, CollisionManager::instance(), pLayers);
		return;
	}
	cout << endl << "In parse object layer function" << endl;
	//create an ObjectLayer object
	ObjectLayer* pObjectLayer = new ObjectLayer();
	cout << pObjectElement->FirstChildElement()->Value();

	for (TiXmlElement *e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() != string("object"))
			continue;

		cout << endl << e->Value() << endl;

		//local attributes variable
		int x, y, width = 0, height = 0, numFrames = 0, textureHeight, textureWidth, callbackID = 0, animSpeed = 0, startingID = 0;
		string name, textureID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		GameObject* pGameObject = GameObjectFactory::Instance()->create(e->Attribute("class"));

		//get properties value
		for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
		{
			if (properties->Value() == string("properties"))
			{
				for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
				{
					if (property->Value() == string("property"))
					{
						if (property->Attribute("name") == std::string("numFrames"))
						{
							property->Attribute("value", &numFrames);
						}
						else if (property->Attribute("name") == std::string("textureHeight"))
						{
							property->Attribute("value", &height);
						}
						else if (property->Attribute("name") == std::string("textureID"))
						{
							textureID = property->Attribute("value");
						}
						else if (property->Attribute("name") == std::string("textureWidth"))
						{
							property->Attribute("value", &width);
						}
						else if (property->Attribute("name") == std::string("callbackID"))
						{
							property->Attribute("value", &callbackID);
						}
						else if (e->Attribute("name") == std::string("animSpeed"))
						{
							property->Attribute("value", &animSpeed);
						}
						else if (e->Attribute("name") == std::string("startingID"))
						{
							property->Attribute("value", &startingID);
						}
					}
				}
			}
		}

		if( e-> Attribute("class") == string("Player"))
			pGameObject->load(new LoaderParams(x, y, width, height, 0, 1, numFrames, textureID, callbackID, animSpeed, startingID));
		else if (e->Attribute("class") == string("AnimatedTile"))
		{
			int currentRow = 1040 / 48;
			int currentFrame = 1040 % 48;

			cout << endl << "StartingID: "<< startingID << "Current Row: " << currentRow << "Current Frame: " << currentFrame << endl;
			pGameObject->load(new LoaderParams(x, y, width, height, currentFrame, currentRow + 1 , numFrames, textureID, callbackID, animSpeed, 32));
			pGameObject->printStats();
		}
		pObjectLayer->getGameObjects()->push_back(pGameObject);
		
		//testing/debugging
		cout << endl;
		pGameObject->printStats();


	}

	pLayers->push_back(pObjectLayer);
}

void LevelParser::parseCollisionZoneLayer(TiXmlElement* collisionZoneNode, CollisionManager* collisionManager, std::vector<Layer*>* pLayers)
{
	cout << endl << "In parse collision zone layer" << endl;
	cout << endl << collisionZoneNode->FirstChildElement()->Value() << endl;

	//create an ObjectLayer object
	ObjectLayer* pObjectLayer = new ObjectLayer();
	int x, y, width = 0, height = 0, numFrames = 0, textureHeight, textureWidth, callbackID = 0, animSpeed = 0, startingID = 0;
	string name, textureID, island;

	for (TiXmlElement* e = collisionZoneNode->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() != string("object"))
			continue;

		cout << endl << e->Value() << endl;

		//local attributes variable


		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		cout << width << " " << height;
		//create Region2 Object
		GameObject* pGameObject = GameObjectFactory::Instance()->create(e->Attribute("class"));

		//get properties value
		for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
		{
			if (properties->Value() == string("properties"))
			{
				for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
				{
					if (property->Value() == string("property"))
					{
						if (property->Attribute("name") == std::string("numFrames"))
						{
							property->Attribute("value", &numFrames);
						}
						else if (property->Attribute("name") == std::string("island"))
						{
							island = property->Attribute("value");
							cout << endl << "Stored Island : " << island << endl;
						}
						else if (property->Attribute("name") == std::string("textureHeight"))
						{
							property->Attribute("value", &textureHeight);
						}
						else if (property->Attribute("name") == std::string("textureID"))
						{
							textureID = property->Attribute("value");
						}
						else if (property->Attribute("name") == std::string("textureWidth"))
						{
							property->Attribute("value", &textureWidth);
						}
						else if (property->Attribute("name") == std::string("callbackID"))
						{
							property->Attribute("value", &callbackID);
						}
						else if (e->Attribute("name") == std::string("animSpeed"))
						{
							property->Attribute("value", &animSpeed);
						}
						else if (e->Attribute("name") == std::string("startingID"))
						{
							property->Attribute("value", &startingID);
						}
						
					}
				}
			}
		}

		cout << " " << width << " " << height;
		cout << "Island Name: " << island;
		pGameObject->load(new LoaderParams(x, y, width, height, 0, 0, numFrames, textureID, callbackID, animSpeed, startingID));
		pGameObject->printStats();

		//add it to its respective island map
		collisionManager->pushGameObject(island, pGameObject);

		//add it to objectlayer
		pObjectLayer->getGameObjects()->push_back(pGameObject);


	}

	pLayers->push_back(pObjectLayer);
}

