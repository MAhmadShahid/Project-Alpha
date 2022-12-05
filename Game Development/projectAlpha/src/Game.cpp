#include "Game.h"
#include "SDL.h"
#include "iostream"
#include "SDL_image.h"

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

	//getting the window's size
	int windowWidth = 0;
	int windowHieght = 0;

	SDL_GetWindowSize(window, &windowWidth, &windowHieght);

	//texture loading
	const char* spritePath = "C:/Users/ahmad/source/repos/Game Development/Game Development/projectAlpha/src/ghostRight.bmp";
	SDL_Surface* tempSurface = IMG_Load("projectAlpha/src/Assets/player.png");

	if (tempSurface == NULL)
	{
		std::cout << "Surface returned = Null" << std::endl;
		printf("Image: %s\nError: %s", spritePath, SDL_GetError());		
	}

	texture = SDL_CreateTextureFromSurface(renderer	, tempSurface);
	SDL_FreeSurface(tempSurface);

	int imageWidth = 0;
	int imageHieght = 0;

	SDL_QueryTexture(texture, NULL, NULL, &imageWidth, &imageHieght);

	sourceRectangle.x = 0;
	sourceRectangle.y = 0;
	sourceRectangle.w = imageWidth / 6;
	sourceRectangle.h = imageHieght / 10;
	
	destinationRectangle.x = 0;
	destinationRectangle.y = 0;
	
	destinationRectangle.w = 50; // 8000
	destinationRectangle.h = 50; // 2131

	std::cout << std::endl << "Image Length: " << imageWidth << std::endl << "Image Hieght: " << imageHieght;
	std::cout << std::endl << "X: " << destinationRectangle.x << std::endl << "Y: " << destinationRectangle.y;

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

