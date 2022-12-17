#pragma once

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h" 



class Game
{

private:
	static Game* s_pInstance;
	
	bool gameRunning;
	SDL_Window * window;
	SDL_Renderer* renderer;
	std::vector<GameObject*> gameObjects;
	
	Game();

public:
	//destructor

	~Game();

	//core functions

	static Game* instance();

	bool init(const char * title, int x_Position, int y_Position, int width, int hieght, Uint32 flags);

	void handleEvents();
	void update();
	void render();
	void clean();

	SDL_Renderer* getRenderer();

	//helping functions
	bool running();

};


