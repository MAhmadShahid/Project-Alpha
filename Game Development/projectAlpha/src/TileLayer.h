#pragma once
#include <iostream>
#include "Layer.h"
#include "TileSet.h"
#include "Level.h"
#include "Vector2D.h"
#include <vector>

class TileLayer : public Layer
{
private:

	int m_numColumns;
	int m_numRows;
	int m_tileSize;

	int additiveScale = 0;

	Vector2D m_position;
	Vector2D m_velocity;

	const std::vector<TileSet>& m_tilesets;
	std::vector<std::vector<int>> m_tileIDs;

public:

	TileLayer(int tileSize, const std::vector<TileSet> &tilesets);
	TileLayer(int tileSize, int additiveScale,const std::vector<TileSet>& tilesets);
	~TileLayer();

	virtual void update();
	virtual void render();

	void setTileIDs(const std::vector<std::vector<int>>& data);
	void setTileSize(int tileSize);
	void setAdditiveScale(int scaleAmount);
	void printTileIDs();
	TileSet getTileSetByID(int tileID);

};