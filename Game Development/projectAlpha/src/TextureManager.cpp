#include "TextureManager.h"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <string>


bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());

	if (tempSurface == nullptr)
		return false;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (texture == nullptr)
		return false;

	textureMap[id] = texture;
	return true;

}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;

	sourceRectangle.x = sourceRectangle.y = 0;
	
	destinationRectangle.x = x;
	destinationRectangle.y = y;

	destinationRectangle.w = sourceRectangle.w = width;
	destinationRectangle.h = sourceRectangle.h = height;

	SDL_RenderCopyEx(renderer, textureMap[id], &sourceRectangle, &destinationRectangle, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Texture* texture = textureMap[id];
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;

	sourceRectangle.x = width * currentFrame;
	sourceRectangle.y = height * (currentRow - 1);

	destinationRectangle.w = sourceRectangle.w = width;
	destinationRectangle.h = sourceRectangle.h = height;

	SDL_RenderCopyEx(renderer, textureMap[id], &sourceRectangle, &destinationRectangle, 0, 0, flip);
}