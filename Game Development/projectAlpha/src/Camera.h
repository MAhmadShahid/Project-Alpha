#pragma once

#include "Vector2D.h"
#include "GameObject.h"

class Camera
{
private:
	static Camera* s_pCamera;
	static const int mapWidth;
	static const int mapHeight;
	
	GameObject* m_pTarget;
	Vector2D m_position;

	Camera() {}
	~Camera() {}
public:

	static Camera* instance()
	{
		if (s_pCamera != 0)
			return s_pCamera;

		s_pCamera = new Camera;
		return s_pCamera;
	}

	void update(Vector2D velocity);
	void setTarget(GameObject* targetObject);
	void setPosition(const Vector2D& position);

	const Vector2D getPosition() const;
};