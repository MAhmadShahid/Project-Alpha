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
	void load(int x, int y, int width, int height, std::string textureID);
	void draw(SDL_Renderer * renderer);
	void update();
	void clean();
};

#endif // !__GameObject__

