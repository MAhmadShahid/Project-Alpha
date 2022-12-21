#pragma once
#include "GameState.h"
#include <iostream>
#include <vector> 

class GameStateMachine
{
private:
	std::vector<GameState*> m_gameStates;
public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	void update();
	void render();
};