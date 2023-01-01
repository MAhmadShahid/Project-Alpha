#pragma once
#include <iostream>
#include <vector>
#include "Layer.h"
#include "TileSet.h"


class Level
{

private:
	std::vector<TileSet> m_tilesets;
	std::vector<Layer*> m_layers;
	Level();
	friend class LevelParser;
public:

	~Level();

	void update();
	void render();

	std::vector<TileSet>* getTileSets();
	std::vector<Layer*>* getLayers();
	void printLayerGrid(int layerID);
	void printTileSetStats(int tilesetID);
};
