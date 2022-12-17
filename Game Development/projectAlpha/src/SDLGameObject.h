#pragma once


#include "GameObject.h"	

class SDLGameObject : public GameObject
{
protected:
	int m_x;
	int m_y;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	std::string m_textureID;

public:
	SDLGameObject(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void printStats();

};