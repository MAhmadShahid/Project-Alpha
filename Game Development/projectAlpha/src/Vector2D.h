#pragma once

#include <math.h>

class Vector2D
{
private:
	float m_x, m_y;

public:
	//constructor
	Vector2D() : m_x(0), m_y(0)
	{

	}

	Vector2D(float x, float y) : m_x(x), m_y(y)
	{

	}

	//getter and setter
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }

	float getX() const { return m_x; }
	float getY() const { return m_y; }

	//other functions
	float length() const { return sqrt(pow(m_x, 2) + pow(m_y, 2)); }

	//Vector Addition
	Vector2D operator+(const Vector2D& secondVector) const
	{
		return Vector2D(m_x + secondVector.m_x, m_y + secondVector.m_y);
	}

	friend Vector2D& operator+= (Vector2D& firstVector, Vector2D& secondVector)
	{
		firstVector.m_x += secondVector.m_x;
		firstVector.m_y += secondVector.m_y;

		return firstVector;
	}

	//Vector Multiplication
	Vector2D operator*(float scalar)
	{
		return Vector2D(m_x * scalar, m_y * scalar);
	}

	Vector2D& operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;
	}

	//Vector Subtraction
	Vector2D operator-(const Vector2D& secondVector) const
	{
		return Vector2D(m_x - secondVector.m_x, m_y - secondVector.m_y);
	}

	friend Vector2D& operator-=(Vector2D& firstVector, const Vector2D& secondVector)
	{
		firstVector.m_x -= secondVector.m_x;
		firstVector.m_y -= secondVector.m_y;
		return firstVector;
	}

	//Vector Division
	Vector2D operator/(float scalar)
	{
		return Vector2D(m_x / scalar, m_y / scalar);
	}

	Vector2D& operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;
		return *this;
	}

	void normalize()
	{
		float l = length();
		if (l > 0) // we never want to attempt to divide by 0
		{
			(*this) *= 1 / l;
		}
	}

};