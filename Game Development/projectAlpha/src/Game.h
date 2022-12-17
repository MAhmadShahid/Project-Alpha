#pragma once
#ifndef __Game__
#define __Game__

#include <SDL.h>
#include <vector>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"

class Game
{

private:
	bool gameRunning;
	SDL_Window * window;
	SDL_Renderer* renderer;
	std::vector<GameObject*> gameObjects;


public:
	//constructor and destructor
	Game();
	~Game();

	//core functions

	bool init(const char * title, int x_Position, int y_Position, int width, int hieght, Uint32 flags);
	void handleEvents();
	void update();
	void render();
	void clean();

	//helping functions
	bool running();

};

#endif // !'Game.h'

