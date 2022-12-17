#pragma once

#include <iostream>
#include <SDL.h>
#include "TextureManager.h"

#ifndef __GameObject__
#define __GameObject__

class GameObject
{
protected:

	std::string textureID;
	int x_Position;
	int y_Position;

	int currentFrame;
	int currentRow;

	int width;
	int height;

public:
	virtual void load(int x, int y, int width, int height, std::string textureID);
	virtual void load(int x, int y, int width, int height, int rowNumber, int frameNumber, std::string textureID);
	virtual void draw(SDL_Renderer * renderer);
	void update();
	void clean();
	virtual void setCurrentFrame(int frameNumber);
	virtual void setCurrentRow(int rowNumber);
	virtual void printStats();
};

#endif // !__GameObject__

