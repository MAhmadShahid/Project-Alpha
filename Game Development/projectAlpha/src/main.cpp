#include<SDL.h>
#include<iostream>
#include "Game.h"




int main(int argc, char* args[])
{

	Game* myGame = Game::instance();

	myGame->init("Class Setup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 720, SDL_WINDOW_SHOWN);

	while (myGame->running())
	{
		myGame->handleEvents();
		myGame->update();
		myGame->render();
	}

	myGame->clean();
	return 0;
}