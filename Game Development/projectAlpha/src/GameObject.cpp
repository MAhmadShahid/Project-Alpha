#include <iostream>
#include "GameObject.h"

void GameObject::load(int x, int y, int width, int height, std::string textureID)
{
	x_Position = x;
	y_Position = y;

	this->width = width;
	this->height = height;

	this->textureID = textureID;

	currentRow = 1;
	currentFrame = 1;

}

void GameObject::draw(SDL_Renderer* renderer)
{
	TextureManager::Instance()->drawFrame(textureID, x_Position, y_Position, width, height, currentRow, currentFrame, renderer);
}