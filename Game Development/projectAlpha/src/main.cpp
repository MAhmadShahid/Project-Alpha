#include<SDL.h>
#include<iostream>
#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;


int main(int argc, char* args[])
{
	Uint32 frameStart, frameTime;
	Game* myGame = Game::instance();

	myGame->init("Class Setup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080,720, SDL_WINDOW_SHOWN);

	while (myGame->running())
	{
		frameStart = SDL_GetTicks(); // start time for the frame

		myGame->handleEvents();
		myGame->update();
		myGame->render();
		
		frameTime = SDL_GetTicks() - frameStart; // time in mili-seconds taken for the frame to load

		if (frameTime < DELAY_TIME)
		{
			SDL_Delay((int)DELAY_TIME - frameTime);
		}
	}

	myGame->clean();
	return 0;
}