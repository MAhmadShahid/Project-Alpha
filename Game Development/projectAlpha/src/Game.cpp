#include "Game.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "MainMenuState.h"

//#include <SDL.h>
typedef Game Game;

Game* Game::s_pInstance = 0;

Game* Game::instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new Game();
		return s_pInstance;
	}

	return s_pInstance;
}

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


bool Game::init(const char * title, int x_Position, int y_Position, int width, int height, Uint32 flags)
{

	//Initializing SDL and setting up window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{ 
		std::cout << "couldn't initialize subsystems" << std::endl; 
		return false; 
	}
	
	window = SDL_CreateWindow(title, x_Position, y_Position, width, height, flags);

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

	m_gameWidth = width;
	m_gameHeight = height;

	m_gameStateMachine = new GameStateMachine();
	m_gameStateMachine->pushState(new MainMenuState());


	//Setting up player object
	/*GameObject* playerSprite = new Player(new LoaderParams(0, 0, 48, 48, 0, 1, "player"));
	GameObject* enemySprite = new Player(new LoaderParams(50, 50, 48, 48, 2, 2, "player"))*/;
	//gameObjects.push_back(playerSprite);
	//gameObjects.push_back(enemySprite);

	//GameObject* ghostSprite = new Player(new LoaderParams(39, 150, 39, 39, 0, 1, "player"));
	//
	//gameObjects.push_back(ghostSprite);



	gameRunning = true;
	return true;

}

void Game::handleEvents()
{
	InputHandler::instance()->update();

	/*if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_RETURN))
		m_gameStateMachine->changeState(new PlayState());*/
}

void Game::update() 
{
	m_gameStateMachine->update();
	for (auto gameObject : gameObjects)
		gameObject->update();
	/*sourceRectangle.x = 100 + 1415 * ((SDL_GetTicks() / 100) % 5);*/	
}

void Game::render()
{
	// everything succeeded lets draw the window
	// set to black // This function expects Red, Green, Blue and Alpha as color values
	SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
	// clear the window to black
	SDL_RenderClear(renderer);// Clear the current rendering target with the drawing color.
	/*SDL_RenderCopy(renderer, texture, &sourceRectangle, &destinationRectangle);*/

	m_gameStateMachine->render();
	for (auto gameObject : gameObjects)
	{
		gameObject->draw();
	}


	// show the window
	SDL_RenderPresent(renderer); // Update the screen with any rendering performed since the previous call.
}

SDL_Renderer* Game::getRenderer() { return renderer; }
SDL_Window* Game::getWindow() { return window; }
GameStateMachine* Game::getGameStateMachine() { return m_gameStateMachine; }

Vector2D Game::getWindowSize() 
{ 
	int windowWidth = 0;
	int windowHeight = 0;

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	return Vector2D(windowWidth, windowHeight);
}


void Game::clean()
{
	std::cout << "cleaning up game";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::quit()
{
	gameRunning = false;
}

int Game::getGameWidth() const
{
	return m_gameWidth;
}

int Game::getGameHeight() const
{
	return m_gameHeight;
}

