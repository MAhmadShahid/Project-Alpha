#include "Game.h"

//#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

Game::Game()
{
	gameRunning = false;
	window = NULL;
	renderer = NULL;
}

Game::~Game() {}

bool Game::running()
{
	return gameRunning;
}

bool Game::init(const char * title, int x_Position, int y_Position, int width, int hieght, Uint32 flags)
{

	//Initializing SDL and setting up window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{ 
		std::cout << "couldn't initialize subsystems" << std::endl; 
		return false; 
	}
	
	window = SDL_CreateWindow(title, x_Position, y_Position, width, hieght, flags);

	if (!window) 
	{ 
		std::cout << "window creation failed" << std::endl;
		return false; 
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) 
	{ 
		std::cout << "renderer creation failed" << std::endl; 
		return false; 
	}

	//Game Initialization Code Here

	//Loading Game Textures
	bool resourcesLoaded = TextureManager::Instance()->load("projectAlpha/src/Assets/player.png", "player", renderer);
	if (!resourcesLoaded)
		std::cout << "Error in loading resources";


	//Setting up player object
	playerSprite.load(0, 0, 48, 48, "player");

	gameRunning = true;
	return true;

}

void Game::handleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;

		default:
			break;

		}
	}
}

void Game::update() 
{
	/*sourceRectangle.x = 100 + 1415 * ((SDL_GetTicks() / 100) % 5);*/	
}

void Game::render()
{
	// everything succeeded lets draw the window
	// set to black // This function expects Red, Green, Blue and Alpha as color values
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// clear the window to black
	SDL_RenderClear(renderer);// Clear the current rendering target with the drawing color.
	//SDL_RenderCopy(renderer, texture, &sourceRectangle, &destinationRectangle);
	playerSprite.draw(renderer);
	// show the window
	SDL_RenderPresent(renderer); // Update the screen with any rendering performed since the previous call.
}



void Game::clean()
{
	std::cout << "cleaning up game";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

