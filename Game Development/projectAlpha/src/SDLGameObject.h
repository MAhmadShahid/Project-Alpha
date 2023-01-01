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

	virtual Vector2D getPosition() const { return m_position; }
	virtual Vector2D getVelocity() const { return m_velocity; }
	virtual Vector2D getAcceleration() const { return m_acceleration; }
	virtual int getWidth() const { return m_width; }
	virtual int getHieght() const { return m_height; }
	virtual int getNumFrames() const { return m_numFrames; }
	virtual int getCurrentRow() const { return m_currentRow; }
	virtual int getCurrentFrame() const { return m_currentFrame; }
	virtual void setPosition(Vector2D newPosition) { m_position = newPosition; }
	virtual void setVelocity(Vector2D newVelocity) { m_velocity = newVelocity; }

	virtual void load(const LoaderParams* pParams);

};