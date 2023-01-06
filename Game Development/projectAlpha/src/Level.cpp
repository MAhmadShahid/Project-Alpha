#pragma once
#include "Level.h"
using namespace std;

Level::Level()
{

}

Level::~Level()
{

}

std::vector<TileSet>* Level::getTileSets()
{
	return &m_tilesets;
}

std::vector<Layer*>* Level::getLayers()
{
	return &m_layers;
}

void Level::render()
{
	for (unsigned int i = 0; i < m_layers.size(); i++)
		m_layers[i]->render();
}

void Level::update()
{
	for (unsigned int i = 0; i < m_layers.size(); i++)
		m_layers[i]->update();
}

Player* Level::extractPlayerFromLayer()
{
	ObjectLayer* objectLayer;
	Player* player = nullptr;
	for (unsigned int i = 0; i < m_layers.size(); i++)
	{
		if (!dynamic_cast<ObjectLayer*>(m_layers[i]))
			continue;

		objectLayer = dynamic_cast<ObjectLayer*>(m_layers[i]);
		std::vector<GameObject*>* gameObjects = objectLayer->getGameObjects();
		vector<GameObject*>::iterator iter = gameObjects->begin();
		
		for (iter; iter != gameObjects->end(); iter++)
		{
			if (!dynamic_cast<Player*>(*iter))
				continue;
		
			player = dynamic_cast<Player*>(*iter);
			gameObjects->erase(iter);
			break;
		}

		break;
	}

	return player;
}

void Level::printLayerGrid(int layerID)
{
	if (layerID >= m_layers.size())
	{
		std::cout << "Invalid Layer ID";
	}

	m_layers[layerID]->printTileIDs();
}

void Level::printTileSetStats(int tilesetID)
{
	if (tilesetID >= m_tilesets.size())
	{
		std::cout << "Invalid Tileset ID";
	}


	cout << endl << endl << "Tile Status: " << m_tilesets[tilesetID].name << endl;
	cout << "firstGridID: " << m_tilesets[tilesetID].firstGridID << endl;
	cout << "Tile Width: " << m_tilesets[tilesetID].tileWidth << endl;
	cout << "Tile Height: " << m_tilesets[tilesetID].tileHeight << endl;
	cout << "Spacing: " << m_tilesets[tilesetID].spacing << endl;
	cout << "Margin: " << m_tilesets[tilesetID].margin << endl;
	cout << "Width: " << m_tilesets[tilesetID].width << endl;
	cout << "Height: " << m_tilesets[tilesetID].height << endl;
	cout << "Number of Columns: " << m_tilesets[tilesetID].numColumns << endl;
}