#pragma once
#include <map>
#include <string>
#include <SDL.h>

#ifndef __TextureManager__
#define __TextureManager__

class TextureManager
{
private:
	// Attributes
	std::map<std::string, SDL_Texture*> textureMap;

public:
	//core functions
	bool load(std::string fileName, std::string id, SDL_Renderer* renderer);
	void draw(std::string id, int x, int y, int width, int hieght, SDL_Renderer * renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

};

#endif

