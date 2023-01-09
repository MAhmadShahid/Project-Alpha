#include "TileLayer.h"
#include "Game.h"
#include "Camera.h"


TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight,int scaleAmount, const std::vector<TileSet>& tilesets) : m_tileSize(tileSize), m_tilesets(tilesets), additiveScale(scaleAmount)
{
	m_numColumns = Game::instance()->getGameWidth() / (m_tileSize + additiveScale);
	m_numRows = Game::instance()->getGameHeight() / (m_tileSize + additiveScale);

	//m_numColumns = mapWidth;
	//m_numRows = mapHeight;

	m_mapWidth = mapWidth;
	
}

TileLayer::~TileLayer()
{

}

void TileLayer::setTileIDs(const std::vector<std::vector<int>>& data)
{
	m_tileIDs = data;
}

void TileLayer::setTileSize(int tileSize)
{
	m_tileSize = tileSize;
}

TileSet TileLayer::getTileSetByID(int tileID) 
{
	for (std::vector<TileSet>::size_type i = 0; i < m_tilesets.size(); i++)
	{
		//comparison for all possibilites that the tileSet is not at the end
		if (i + 1 <= m_tilesets.size() - 1)
		{
			if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
				return m_tilesets[i];
		}
		else
			return m_tilesets[i];
	}

	std::cout << std::endl <<"Didn't found the tile set, returning empty tileset" << std::endl;
	
	TileSet emptyTileset;
	return emptyTileset;
}

void TileLayer::update()
{
	m_position.setX( Camera::instance()->getPosition().getX());
}

void TileLayer::render()
{
	int x, y, x2, y2 = 0;
	x = (int)m_position.getX() / (m_tileSize + additiveScale);
	y = (int)m_position.getY() / (m_tileSize + additiveScale);
	x2 = int(m_position.getX()) % (m_tileSize + additiveScale);
	y2 = int(m_position.getY()) % (m_tileSize + additiveScale);

	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{
			int id = m_tileIDs[i][j + x];
			
			if (id == 0)
			{
				continue;
			}

			//// if tile outside the viewable area, skip it
			//if (((j * m_tileSize) - x2) - Camera::instance()->getPosition().getX() < -m_tileSize || ((j * m_tileSize) - x2)
			//	- Camera::instance()->getPosition().getX() > Game::instance()->getGameWidth())
			//{
			//	continue;
			//}
			
			TileSet tileset = getTileSetByID(id);
			id--;
			
			TextureManager::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing, (j * (m_tileSize + additiveScale)) - x2, 
				(i * (m_tileSize + additiveScale)) - y2, m_tileSize, m_tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, 
				(id - (tileset.firstGridID - 1)) % tileset.numColumns, additiveScale,Game::instance()->getRenderer());

			//// draw the tile into position while offsetting its x position by
			//// subtracting the camera position
			//TextureManager::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing, ((j * m_tileSize) - x2) - Camera::instance()->getPosition().getX(),
			//	((i * m_tileSize) - y2), m_tileSize, m_tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns,
			//	(id - (tileset.firstGridID - 1))% tileset.numColumns, additiveScale,Game::instance()->getRenderer());
		}
	}
}


void TileLayer::printTileIDs()
{
	std::cout << std::endl;
	for (int row = 0; row < m_numRows; row++)
	{
		std::cout << "{ ";
		for (int column = 0; column < m_numColumns; column++)
		{
			std::cout << m_tileIDs[row][column] << " ";
		}
		std::cout << "}" << std::endl;
	}
}

void TileLayer::setAdditiveScale(int scaleAmount)
{
	additiveScale = scaleAmount;
}