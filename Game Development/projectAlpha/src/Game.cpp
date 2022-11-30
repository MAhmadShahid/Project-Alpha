#include "Game.h"
#include "SDL.h"
#include "iostream"

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

	//texture loading
	const char* spritePath = "C:/Users/ahmad/source/repos/Game Development/Game Development/projectAlpha/src/ghostRight.bmp";
	SDL_Surface* tempSurface = SDL_LoadBMP("projectAlpha/Assets/ghostRightFace.bmp");

	if (tempSurface == NULL)
	{
		std::cout << "Surface returned = Null" << std::endl;
		printf("Image: %s\nError: %s", spritePath, SDL_GetError());		
	}

	texture = SDL_CreateTextureFromSurface(renderer	, tempSurface);
	SDL_FreeSurface(tempSurface);

	SDL_QueryTexture(texture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);

	destinationRectangle.x = sourceRectangle.x = 0;
	destinationRectangle.y = sourceRectangle.y = 0;
	destinationRectangle.w = sourceRectangle.w;
	destinationRectangle.h = sourceRectangle.h;

	std::cout << std::endl << "Length: " << sourceRectangle.w << std::endl << "Hieght: " << sourceRectangle.h;

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

void Game::update() {}

void Game::render()
{
	// everything succeeded lets draw the window
	// set to black // This function expects Red, Green, Blue and
	//Alpha as color values
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// clear the window to black
	SDL_RenderClear(renderer);// Clear the current rendering target with the drawing color.
	SDL_RenderCopy(renderer, texture, &sourceRectangle, &destinationRectangle);
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

