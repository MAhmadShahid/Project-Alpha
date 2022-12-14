#pragma once
#include "GameObject.h"

#ifndef __Player__
#define __Player__

#include <SDL.h>
#include <iostream>

class Player : public GameObject
{
public:
	void load(int x, int y, int width, int height, std::string textureID);
	void draw(SDL_Renderer* renderer);
	void update();
	void clean();
};

#endif // !__Player__

