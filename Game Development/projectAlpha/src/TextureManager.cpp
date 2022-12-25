#include "TextureManager.h"
#include <iostream>
#include <SDL_image.h>
#include <string>

TextureManager* TextureManager::s_pInstance = 0;

TextureManager* TextureManager::Instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new TextureManager();
		return s_pInstance;
	}
	return s_pInstance;
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());

	if (tempSurface == nullptr)
	{
		std::cout << "\nFailed to load image as a surface\n";
		std::cout << SDL_GetError();
		return false;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (texture == nullptr)
	{
		std::cout << "\nFailed to load image as a texture\n";
		std::cout << SDL_GetError();
		return false;
	}

	textureMap[id] = texture;
	return true;

}

//void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip)
//{
//	SDL_Rect sourceRectangle;
//	SDL_Rect destinationRectangle;
//
//	sourceRectangle.x = sourceRectangle.y = 0;
//	
//	destinationRectangle.x = x;
//	destinationRectangle.y = y;
//
//	destinationRectangle.w = sourceRectangle.w = width;
//	destinationRectangle.h = sourceRectangle.h = height;
//
//	SDL_RenderCopyEx(renderer, textureMap[id], &sourceRectangle, &destinationRectangle, 0, 0, flip);
//}

//this new function adds support for scaling
void TextureManager::draw(std::string id, int x, int y, int width, int height, int scale_x, int scale_y,SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;

	sourceRectangle.x = sourceRectangle.y = 0;
	sourceRectangle.w = width; sourceRectangle.h = height;

	destinationRectangle.x = x; destinationRectangle.y = y;
	
	destinationRectangle.w = scale_x * width;
	destinationRectangle.h = scale_y * height;

	SDL_RenderCopyEx(renderer, textureMap[id], &sourceRectangle, &destinationRectangle, 0, 0, flip);
}

//void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip)
//{
//	SDL_Rect sourceRectangle;
//	SDL_Rect destinationRectangle;
//
//
//	sourceRectangle.x = width * currentFrame; // frame starts from 0 to n - 1 
//	sourceRectangle.y = height * (currentRow - 1); // row starts from 1 to n
//
//	destinationRectangle.x = x;
//	destinationRectangle.y = y;
//
//	destinationRectangle.w = sourceRectangle.w = width;
//	destinationRectangle.h = sourceRectangle.h = height;
//
//	SDL_RenderCopyEx(renderer, textureMap[id], &sourceRectangle, &destinationRectangle, 0, 0, flip);
//}

//this new function adds support for scaling
void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, int scale_x, int scale_y,SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;

	//setting up source rectangle
	sourceRectangle.x = width * currentFrame; // frame starts from 0 to n - 1 
	sourceRectangle.y = height * (currentRow - 1); // row starts from 1 to n

	sourceRectangle.w = width; sourceRectangle.h = height;

	//setting up destination rectangle
	destinationRectangle.x = x; destinationRectangle.y = y;

	destinationRectangle.w = scale_x * width;
	destinationRectangle.h = scale_y * height;

	SDL_RenderCopyEx(renderer, textureMap[id], &sourceRectangle, &destinationRectangle, 0, 0, flip);
}

void TextureManager::clearFromTextureManager(std::string id)
{
	textureMap.erase(id);
}