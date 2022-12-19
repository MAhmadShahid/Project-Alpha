#pragma once
#include <iostream>

class LoaderParams
{
	// private member variables
	std::string m_textureID;
	int x_Position;
	int y_Position;

	int m_currentFrame;
	int m_currentRow;

	int m_width;
	int m_height;

public:
	//constructor
	LoaderParams(int x, int y, int width, int height, int currentFrame, int currentRow, std::string textureID)
		: x_Position(x), y_Position(y), m_width(width), m_height(height), m_currentFrame(currentFrame), m_currentRow(currentRow), m_textureID(textureID)
	{

	}

	//getters and setters
	int getXPosition() const { return x_Position; }
	int getYPosition() const { return y_Position; }
	int getCurrentFrame() const { return m_currentFrame; }
	int getCurrentRow() const { return m_currentRow; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string getTextureID() const { return m_textureID; }
};