#pragma once
#include <map>
#include <string>
#include <SDL.h>



class TextureManager // Singleton Class
{
private:
	// Attributes
	std::map<std::string, SDL_Texture*> textureMap;
	static TextureManager* s_pInstance;

	//constructor (Singleton implementation)
	TextureManager() {};


public:
	//core functions
	static TextureManager* Instance();
	bool load(std::string fileName, std::string id, SDL_Renderer* renderer);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer * renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

};



