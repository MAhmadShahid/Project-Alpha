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

	int numFrames;

	int m_scale_x = 1;
	int m_scale_y = 1;

	int callback_ID = 0;
	int animSpeed = 0;

public:
	//constructor
	LoaderParams(int x, int y, int width, int height, int currentFrame, int currentRow, int pnumFrames,std::string textureID,int callback_ID = 0,int animSpeed = 0)
		: x_Position(x), y_Position(y), m_width(width), m_height(height), m_currentFrame(currentFrame), m_currentRow(currentRow), numFrames(pnumFrames), m_textureID(textureID), callback_ID(callback_ID), animSpeed(animSpeed)
	{

	}

	LoaderParams(int x, int y, int width, int height, int currentFrame, int currentRow, int scale_x, int scale_y,std::string textureID)
		: x_Position(x), y_Position(y), m_width(width), m_height(height), m_currentFrame(currentFrame), m_currentRow(currentRow), m_scale_x(scale_x), m_scale_y(scale_y), m_textureID(textureID)
	{

	}

	//getters and setters
	int getXPosition() const { return x_Position; }
	int getYPosition() const { return y_Position; }
	int getCurrentFrame() const { return m_currentFrame; }
	int getCurrentRow() const { return m_currentRow; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int getScaleX() const { return m_scale_x; }
	int getScaleY() const { return m_scale_y; }
	int getCallbackID() const { return callback_ID; }
	int getAnimSpeed() const { return animSpeed; }
	int getNumFrames() const { return numFrames; }
	std::string getTextureID() const { return m_textureID; }
};