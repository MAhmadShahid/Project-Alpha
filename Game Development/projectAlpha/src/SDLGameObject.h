#pragma once


#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
protected:
	
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	int m_numFrames;

	int scale_x = 1;
	int scale_y = 1;

	std::string m_textureID;

public:
	SDLGameObject();

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void printStats();

	virtual void load(const LoaderParams* pParams);

};