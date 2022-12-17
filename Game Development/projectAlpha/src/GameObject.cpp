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
	currentFrame = 0;


}

void GameObject::load(int x, int y, int width, int height, int rowNumber, int frameNumber, std::string textureID)
{
	x_Position = x;
	y_Position = y;

	this->width = width;
	this->height = height;

	this->textureID = textureID;

	currentRow = rowNumber;
	currentFrame = frameNumber;
}

void GameObject::draw(SDL_Renderer* renderer)
{
	TextureManager::Instance()->drawFrame(textureID, x_Position, y_Position, width, height, currentRow, currentFrame, renderer);
}

void GameObject::setCurrentFrame(int frameNumber)
{
	currentFrame = frameNumber;
}

void GameObject::setCurrentRow(int rowNumber)
{
	currentRow = rowNumber;
}

void GameObject::printStats()
{
	std::cout << "Texture ID = " << textureID << std::endl;
	std::cout << "X = " << x_Position << ", Y = " << y_Position << std::endl;
	std::cout << "Width = " << width << ", Height = " << height << std::endl;
	std::cout << "Current : Row = " << currentRow << ", Frame = " << currentFrame << std::endl;
}